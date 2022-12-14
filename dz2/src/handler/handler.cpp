#include "handler.h"
#include "http/http_constants.h"

#include <fstream>
#include <iostream>

static std::map<std::string, std::string> cached_data;

Response Handler::handle(const Request& req) const {
    if (req.get_method() != http_constants::METHOD_GET &&
    req.get_method() != http_constants::METHOD_HEAD) {
        return Response(http_constants::method_not_allowed);
    }

    std::string path = req.get_url_without_queries();
    if (path.find("../") != std::string::npos) {
        return Response(http_constants::forbidden);
    }

    std::filesystem::path file_path = dir_path;
    file_path.append(path.substr(1));

    if (!std::filesystem::exists(file_path)) {
        return Response(http_constants::not_found);
    }

    if (!file_path.has_filename()) {
        file_path.replace_filename("index.html");
    }

    if (std::filesystem::is_directory(file_path)) {
        return Response(http_constants::forbidden);
    }

    if (!std::filesystem::exists(file_path)) {
        return Response(http_constants::forbidden);
    }


    auto ext = http_constants::get_correct_content_type(file_path.extension());
    auto len_content = std::filesystem::file_size(file_path);

    if (req.get_method() == http_constants::METHOD_HEAD) {
        Response res = Response(http_constants::ok);
        res.create_header("Content-Type", ext);
        res.create_header("Content-Length", std::to_string(len_content));
        return res;
    }

    std::string read;

    auto search = cached_data.find(file_path.string());
    if (search != cached_data.end()) {
        read += cached_data[file_path.string()];
        return { http_constants::ok,
                 read,
                 ext,
                 file_path.string(),
                 len_content
        };
    }
        std::ifstream input( file_path.string(), std::ios::binary);
        std::string str{std::istreambuf_iterator<char>(input),
                        std::istreambuf_iterator<char>()
        };
        cached_data.insert({file_path.string(), str});
        return {http_constants::ok,
                str,
                ext,
                file_path.string(),
                len_content};
}
