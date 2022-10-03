#ifndef DZ2_REQUEST_H
#define DZ2_REQUEST_H

#include <string>
#include "http_constants.h"

// Check all work, of course
class Request {
public:
    explicit Request(const std::string& requset_);

    std::string get_method();
    std::string get_url();

private:
    static std::string url_decode(std::string&& SRC);

    std::string method;
    std::string url;
};

#endif //DZ2_REQUEST_H
