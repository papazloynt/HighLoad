#ifndef DZ2_REQUEST_H
#define DZ2_REQUEST_H

#include <string>

class Request {
public:
    explicit Request(const std::string& req);

    [[nodiscard]] std::string get_method() const;
    [[nodiscard]] std::string get_url() const;
    [[nodiscard]] std::string get_url_without_queries() const;

private:
    static std::string url_decode(const std::string& url);

    std::string method;
    std::string url;
};

#endif //DZ2_REQUEST_H
