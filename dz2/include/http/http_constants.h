#ifndef DZ2_HTTP_CONSTANTS_H
#define DZ2_HTTP_CONSTANTS_H

#include <string_view>

namespace http_constants {
    const std::string_view METHOD_GET = "GET";
    const std::string_view METHOD_HEAD = "HEAD";

    const std::string_view protocol = "HTTP/1.1";

    enum {
        ok = 200,
        bad_request = 400,
        forbidden = 403,
        not_found = 404,
        method_not_allowed = 405,
    };

    static std::string_view get_correct_content_type(std::string_view ext) {
        if (ext == ".html") {
            return "text/html";
        } else if (ext == ".js") {
            return "application/javascript";
        } else if (ext == ".css") {
            return "text/css";
        } else if (ext == ".jpg" || ext == ".jpeg") {
            return "image/jpeg";
        } else if (ext == ".png") {
            return "image/png";
        } else if (ext == ".gif") {
            return "image/gif";
        } else if (ext == ".swf") {
            return "application/x-shockwave-flash";
        }
        return "text/plain";
    }
}

#endif //DZ2_HTTP_CONSTANTS_H
