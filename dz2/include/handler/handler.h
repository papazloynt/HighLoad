#ifndef DZ2_HANDLER_H
#define DZ2_HANDLER_H

#include "http/request.h"
#include "http/response.h"

#include <filesystem>

class Handler {
public:
    explicit Handler(const std::string& dir_path) : dir_path(dir_path) {}
    [[nodiscard]] Response handle(const Request& req) const;

private:
    std::filesystem::path dir_path;
};

#endif //DZ2_HANDLER_H
