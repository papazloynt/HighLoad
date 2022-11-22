#ifndef DZ2_REQUEST_H
#define DZ2_REQUEST_H

#include <string>

class Request {
public:
    explicit Request(const std::string& req);

    std::string get_method();
    std::string get_url();
    std::string get_url_without_queries();

private:
    static std::string url_decode(const std::string& url);

    std::string method;
    std::string url;
};

#endif //DZ2_REQUEST_H
