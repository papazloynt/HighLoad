#include "request.h"

#include <string>

#include "gtest/gtest.h"

TEST(http_request, easy_example) {
    Request req = Request(std::string("GET / HTTP/1.1\n"));

    EXPECT_EQ(req.get_method(), "GET");
    EXPECT_EQ(req.get_url(), "/");
    EXPECT_EQ(req.get_url_without_queries(), "/");
}

TEST(http_request, big_example) {
    Request req = Request(std::string("GET /httptest/dir1/dir12/dir123/deep.txt"));

    EXPECT_EQ(req.get_method(), "GET");
    EXPECT_EQ(req.get_url(), "/httptest/dir1/dir12/dir123/deep.txt");
    EXPECT_EQ(req.get_url_without_queries(), "/httptest/dir1/dir12/dir123/deep.txt");
}

TEST(http_request, queries_example) {
    Request req = Request(std::string("GET /httptest/dir2/page.html?arg1=value&arg2=value"));

    EXPECT_EQ(req.get_method(), "GET");
    EXPECT_EQ(req.get_url(), "/httptest/dir2/page.html?arg1=value&arg2=value");
    EXPECT_EQ(req.get_url_without_queries(), "/httptest/dir2/page.html");
}

TEST(http_request, url_code_example) {
    Request req = Request(std::string("GET /httptest/dir2/%70%61%67%65%2e%68%74%6d%6c"));

    EXPECT_EQ(req.get_method(), "GET");
    EXPECT_EQ(req.get_url(), "/httptest/dir2/page.html");
    EXPECT_EQ(req.get_url_without_queries(), "/httptest/dir2/page.html");
}

TEST(http_request, inet_example) {
    Request req = Request(std::string("GET /echo HTTP/1.1\n"
                        "Host: reqbin.com\n"
                        "Accept: */*"));

    EXPECT_EQ(req.get_method(), "GET");
    EXPECT_EQ(req.get_url(), "/echo");
    EXPECT_EQ(req.get_url_without_queries(), "/echo");
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}