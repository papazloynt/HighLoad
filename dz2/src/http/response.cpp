#include "response.h"

#include <utility>


// TODO: do we need set date?
Response::Response(int status) : status(status) {
    create_header("Server", "cool.chastikov");
    create_header("Connection", "close");
}

[[maybe_unused]] Response::Response(int status,
                   std::string data_body,
                   const std::string &content_type,
                   std::string filepath,
                   size_t filesize) : status(status),
                                 body(std::move(data_body)),
                                 filepath(std::move(filepath)),
                                 filesize(filesize) {
    create_header("Content-Length", std::to_string(body.size()));
    create_header("Content-Type", content_type);
    create_header("Server", "cool.chastikov");
    create_header("Connection", "close");
}

void Response::create_header(const std::string& name, const std::string& value) {
    headers.insert({name, value});
}
