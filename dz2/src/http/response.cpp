#include "response.h"
#include "http_constants.h"

#include <utility>
#include <chrono>
#include <sstream>

Response::Response(int status) : status(status) {
    create_date();
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
    create_date();
    create_header("Content-Length", std::to_string(body.size()));
    create_header("Content-Type", content_type);
    create_header("Server", "cool.chastikov");
    create_header("Connection", "close");
}

void Response::create_header(const std::string& name, const std::string& value) {
    headers.insert({name, value});
}

std::string Response::to_str() const {
    std::stringstream res;

    res << http_constants::protocol <<
    " " << status << " " <<
    http_constants::status_to_str(status) << "\r\n";

    for (const auto &el: headers) {
        res << el.first + ": " + el.second + "\r\n";
    }
    res << "\r\n" << body;
    return res.str();
}

void Response::create_date() {
    char time[1000];
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm tm = *gmtime(&now);
    strftime(time, sizeof time, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    create_header("Date", std::string(time));
}
