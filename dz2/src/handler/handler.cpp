#include "handler.h"
#include "http/http_constants.h"

#include <fstream>

Response Handler::handle(const Request& req) const {
    if (req.get_method() != http_constants::METHOD_GET ||
    req.get_method() != http_constants::METHOD_HEAD) {
        return Response(http_constants::method_not_allowed);
    }

    std::string path = req.get_url_without_queries();
    if (path.find_first_of("../") != std::string::npos) {
        return Response(http_constants::forbidden);
    }

    std::filesystem::path file_path = dir_path;
    file_path.append(path.substr(1));

    if (!file_path.has_filename()) {
        return Response(http_constants::not_found);
    }

    if (!std::filesystem::exists(file_path)) {
        return Response(http_constants::not_found);
    }

    if (std::filesystem::is_directory(file_path)) {
        return Response(http_constants::forbidden);
    }

    auto ext = file_path.extension();
    auto len_content = std::filesystem::file_size(file_path);

    if (req.get_method() == http_constants::METHOD_HEAD) {
        Response res = Response(http_constants::ok);
        res.create_header("Content-Type", ext);
        res.create_header("Content-Length", std::to_string(len_content));
        return res;
    }

    std::ifstream input( file_path.string(), std::ios::binary);
    return {http_constants::ok,
            {
                std::istreambuf_iterator<char>(input),
                std::istreambuf_iterator<char>()
                    },
            ext,
            file_path.string(),
            len_content};
}
