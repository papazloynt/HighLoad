#include "request.h"
#include "http_exception.h"

#include <regex>

inline std::regex startLine(R"((PUT|GET|POST|HEAD|OPTIONS|PATCH)\s(/[^\n\s\r\t\0]*)\sHTTP/([\d.]+)\r\n)");

Request::Request(const std::string& req) {
    std::sregex_iterator match(req.begin(), req.end(), startLine);
    method = match->format("$1");
    url = url_decode(match->format("$2"));
}

std::string Request::get_method() const {
    return method;
}

std::string Request::get_url() const {
    return url;
}

std::string Request::get_url_without_queries() const {
    auto p = url.find_first_of('?');
    if (p == std::string::npos) {
        p = url.size();
    }
    return url.substr(0, p);
}

std::string Request::url_decode(const std::string& url) {
    std::string ret;
    char ch;
    int i, ii;
    for (i = 0; i < url.length(); i++) {
        if (url[i] == '%') {
            sscanf(url.substr(i + 1,2).c_str(), "%x", &ii);
            ch = static_cast<char>(ii);
            ret += ch;
            i = i + 2;
        } else {
            ret += url[i];
        }
    }
    return (ret);
}