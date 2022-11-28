#ifndef DZ2_RESPONSE_H
#define DZ2_RESPONSE_H

#include <string>
#include <map>

class Response {
public:
    explicit Response(int status);

    [[maybe_unused]] Response(int status,
             std::string  data_body,
             const std::string& content_type,
             std::string  filepath,
             size_t filesize);

    ~Response() = default;

    void create_header(const std::string& name, const std::string& value);

private:
    int status;
    std::string body;
    std::string filepath;
    size_t filesize{};

    std::map<std::string, std::string> headers;
};

#endif //DZ2_RESPONSE_H
