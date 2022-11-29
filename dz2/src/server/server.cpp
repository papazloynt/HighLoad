#include "handler/handler.h"
#include "server.h"

#include <iostream>

#include <zconf.h>
#include <cstring>
#include <cerrno>
#include <csignal>

#include <sys/socket.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/event.h>
#include <http/request.h>

#include <coroutine>
#include <future>
#include <list>
#include <memory>

static const unsigned short PORT = 8080;

struct Task {
    struct promise_type {
        Task get_return_object() {return {};}
        std::suspend_never initial_suspend() {return {};}
        std::suspend_never final_suspend() noexcept {return {};}
        void unhandled_exception() {}
    };
};

struct Scheduler {
    Scheduler() = default;
    std::list<std::coroutine_handle<>> tasks{};

    void suspend(std::coroutine_handle<> coro) {
        tasks.push_back(coro);
    }

    bool schedule() {
        if (!tasks.empty()) {
            auto task = tasks.front();
            tasks.pop_front();
            if (not task.done()) { task.resume(); }
            return false;
        }
        return false;
    }
};


static Scheduler gScheduler =  Scheduler{};

struct suspend {
    auto operator co_await() {
        struct awaiter : std::suspend_always {
            void await_suspend(std::coroutine_handle<> coro) const noexcept {gScheduler.suspend(coro);}
        };
        return awaiter{};
    }
};

Handler* handler;

Server::Server(int thread_count, const std::string& rootDir) : thread_count(thread_count) {
    handler = new Handler(rootDir);
}

Server::~Server() {
    delete handler;
}

Task read(struct bufferevent* bev, std::string& result) {
    size_t read = 0;
    size_t before_read = 0;
    char* buffer = new char[150];
    while (read < 1000) {
        if (read > 0) {
            co_await suspend{};
        }
        auto received = bufferevent_read(bev, buffer, 150);
        result.append(buffer, received);
        read += received;
        if (result.find("\r\n\r\n") != std::string::npos) {
            break;
        } else if (before_read == read) {
            break;
        }
        before_read = read;
    }
    delete[] buffer;
}

void Server::read_sock(struct bufferevent* bev , void *tmp) {
    std::string result;
    read(bev, result);

    auto req = Request(result);

    auto response = handler->handle(req);

    auto resp = response.to_str();
    bufferevent_write(bev, resp.c_str(), resp.length());
}

void Server::accept_connect(struct evconnlistener *listener, evutil_socket_t fd,
                           struct sockaddr *sa, int socklen, void *user_data) {
    auto* base = static_cast<event_base *>(user_data);
    struct bufferevent *bev;

    printf("Received on (PID %d)\n", getpid());

    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if (!bev) {
        std::cerr << "Error constructing bufferevent!" << std::endl;
        event_base_loopbreak(base);
        return;
    }

    bufferevent_setcb(bev, read_sock, write_end_callback, close_conn_callback, base);
    bufferevent_enable(bev, EV_READ);
}

void Server::write_end_callback(struct bufferevent *bev, void *user_data) {
    struct evbuffer *output = bufferevent_get_output(bev);
    if (evbuffer_get_length(output) == 0) {
        bufferevent_free(bev);
    } else {
        std::cout << "Error" << std::endl;
    }
}

void Server::run() {
    std::thread scheduler([](){ while(gScheduler.schedule()) { }});
    scheduler.detach();

    for (int i = 1; i < thread_count; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            break;
        } else if (pid < 0) {
            std::cerr << "Error during fork" << std::endl;
            return;
        }
    }

    struct event_base *listenBase;
    struct event *signal_event;
    struct evconnlistener *listener;

    struct sockaddr_in sin = {0};

    listenBase = event_base_new();
    if (!listenBase) {
        std::cerr <<  "Could not initialize libevent!" << std::endl;
        return;
    }

    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);


    signal_event = evsignal_new(listenBase, SIGINT, signal_callback, (void *)listenBase);
    if (!signal_event || event_add(signal_event, nullptr)<0) {
        std::cerr << "Could not create/add a signal event!" << std::endl;
        return;
    }

    listener = evconnlistener_new_bind(listenBase, this->accept_connect, (void *)listenBase,
                                       LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE_PORT, -1,
                                       (struct sockaddr*)&sin,
                                       sizeof(sin));
    if (!listener) {
        std::cerr << "Could not create a listener!" << std::endl;
        return;
    }
    std::cout << event_reinit(listenBase) << std::endl;


    std::cout << "Server inited" << std::endl;
    event_base_dispatch(listenBase);

    std::cout << "Server stopped" << std::endl;

    evconnlistener_free(listener);
    event_free(signal_event);
    event_base_free(listenBase);
}

void Server::close_conn_callback(struct bufferevent *bev, short events, void *user_data) {
    if (events & BEV_EVENT_EOF) {
        std::cout << "Connection closed." << std::endl;
    } else if (events & BEV_EVENT_ERROR) {
        std::cout << "Got an error on the connection: " << strerror(errno) << std::endl;
    }
    bufferevent_free(bev);
}

void Server::signal_callback(evutil_socket_t sig, short events, void *user_data) {
    auto *callbackBase = static_cast<event_base *>(user_data);
    struct timeval delay = { 2, 0 };

    std::cout << "Caught an interrupt signal; exiting cleanly in two seconds." << std::endl;

    event_base_loopexit(callbackBase, &delay);
}
