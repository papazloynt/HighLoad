#ifndef DZ2_HTTP_CONSTANTS_H
#define DZ2_HTTP_CONSTANTS_H

#include <string_view>

// containers for RO strings
namespace http_constants {
    const std::string_view METHOD_GET = "GET";
    const std::string_view METHOD_HEAD = "HEAD";

    enum {
        ok = 200,
        not_found = 404,
        bad_request = 400,
    };
}

#endif //DZ2_HTTP_CONSTANTS_H
