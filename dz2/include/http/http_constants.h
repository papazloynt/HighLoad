#ifndef DZ2_HTTP_CONSTANTS_H
#define DZ2_HTTP_CONSTANTS_H

#include <string>

namespace http_constants {
    const std::string METHOD_GET = "GET";
    const std::string METHOD_HEAD = "HEAD";

    const std::string protocol = "HTTP/1.1";

    enum {
        ok = 200,
        forbidden = 403,
        not_found = 404,
        method_not_allowed = 405,
    };

    static std::string status_to_str(int status) {
        switch (status) {
            case ok: return "OK";
            case forbidden: return "Forbidden";
            case not_found: return "NotFound";
            case method_not_allowed: return "Method Not Allowed";
            default: return "nothing";
        }
    }

    static std::string get_correct_content_type(const std::string& ext) {
        if (ext == ".html") {
            return "text/html";
        } else if (ext == ".css") {
            return "text/css";
        } else if (ext == ".js") {
            return "application/javascript";
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
