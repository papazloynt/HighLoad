#include "request.h"
#include "http_exception.h"

Request::Request(const std::string& req) {
   auto p = req.find_first_of(' ');
   if (p == std::string::npos) {
        throw HttpException("bad style of request");
   }

   method = req.substr(0, p);
   while (req.at(p) == ' ') {
       ++p;
   }
   auto start_pos_of_url = p;
    while (p < req.size() and req.at(p) != ' ') {
        ++p;
    }
    std::string hard_url = req.substr(start_pos_of_url, p - start_pos_of_url);
    url = url_decode(hard_url);
}

std::string Request::get_method() {
    return method;
}

std::string Request::get_url() {
    return url;
}

std::string Request::get_url_without_queries() {
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