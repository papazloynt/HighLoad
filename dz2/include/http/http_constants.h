#ifndef DZ2_HTTP_CONSTANTS_H
#define DZ2_HTTP_CONSTANTS_H

#include <string_view>

// basic constants
namespace http_constants {
    const std::string_view METHOD_GET = "GET";
    const std::string_view METHOD_HEAD = "HEAD";

    enum {
        ok = 200,
        bad_request = 400,
        forbidden = 403,
        not_found = 404,
        method_not_allowed = 405,
    };
}

#endif //DZ2_HTTP_CONSTANTS_H
