#ifndef DZ2_SERVER_H
#define DZ2_SERVER_H

#include "handler/handler.h"
#include <evutil.h>
#include <event2/listener.h>

#include <vector>
#include <thread>

class Server {
public:
    explicit Server(int thread_count, const std::string& rootDir);
    ~Server();
    void run();
private:
    static void accept_connect(struct evconnlistener *listener, evutil_socket_t fd,
                              struct sockaddr *sa, int socklen, void *user_data);
    static void write_end_callback(struct bufferevent *bev, void *user_data);
    static void close_conn_callback(struct bufferevent *bev, short events, void *user_data);
    static void signal_callback(evutil_socket_t sig, short events, void *user_data);
    static void read_sock(struct bufferevent* bev , void *tmp);


    std::vector<std::thread> threads;
    unsigned short thread_count;
};

#endif //DZ2_SERVER_H
