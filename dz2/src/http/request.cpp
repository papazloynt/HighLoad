#include "request.h"
#include "http_exception.h"

// TODO: make better get params
Request::Request(const std::string& requset_) {
   auto p = requset_.find_first_of(' ');
   if (p == std::string::npos) {
       // TODO: return BAD_REQUSET
        throw HttpException("bad style of request");
   }

   // TODO: add check for BAD_REQUESTS
   method = requset_.substr(0, p);
   while (requset_.at(p) == ' ') {
       ++p;
   }
   auto start_pos_of_url = p;
    while (requset_.at(p) != ' ') {
        ++p;
    }
    std::string bad_url = requset_.substr(start_pos_of_url, p);
    url = url_decode(std::move(bad_url));
}

std::string Request::get_method() {
    return method;
}

std::string Request::get_url() {
    return url;
}

std::string Request::url_decode(std::string&& SRC) {
    std::string ret;
    char ch;
    int i, ii;
    for (i=0; i<SRC.length(); i++) {
        if (SRC[i]=='%') {
            sscanf(SRC.substr(i+1,2).c_str(), "%x", &ii);
            ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } else {
            ret+=SRC[i];
        }
    }
    return (ret);
}