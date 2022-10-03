#ifndef DZ2_HTTP_EXCEPTION_H
#define DZ2_HTTP_EXCEPTION_H

#include <exception>
#include <string>

class HttpException : public std::exception {
public:
    HttpException(const std::string msg_what) : msg_what(std::move(msg_what)) {}

    const char* what() const noexcept override {
        return msg_what.c_str();
    }

private:
    std::string msg_what;
};

#endif //DZ2_HTTP_EXCEPTION_H
