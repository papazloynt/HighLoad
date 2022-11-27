#include "response.h"

#include <utility>


// TODO: do we need set date?
Response::Response(int status) : status(status) {
    headers.insert({"Server", "cool.chastikov"});
    headers.insert({"Connection", "close"});
}

[[maybe_unused]] Response::Response(int status,
                   std::string data_body,
                   const std::string &content_type,
                   std::string filepath,
                   size_t filesize) : status(status),
                                 body(std::move(data_body)),
                                 filepath(std::move(filepath)),
                                 filesize(filesize) {
    headers.insert({"Content-Length", std::to_string(body.size())});
    headers.insert({"Content-Type", content_type});
    headers.insert({"Server", "cool.chastikov"});
    headers.insert({"Connection", "close"});
}