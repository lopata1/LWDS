#include "../include/utils.h"

#include "../include/http_request.h"
#include "gtest/gtest.h"

static std::string raw_request =
    "\
POST /login HTTP/1.1\n\
Host: localhost\n\
Content-Length: 41\n\
Cache-Control: max-age=0\n\
sec-ch-ua: \n\
sec-ch-ua-mobile: ?0\n\
sec-ch-ua-platform: "
    "\n\
Upgrade-Insecure-Requests: 1\n\
Origin: http://localhost\n\
Content-Type: application/x-www-form-urlencoded\n\
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 \
(KHTML, like Gecko) Chrome/114.0.5735.199 Safari/537.36\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,\
image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\n\
Sec-Fetch-Site: same-origin\n\
Sec-Fetch-Mode: navigate\n\
Sec-Fetch-User: ?1\n\
Sec-Fetch-Dest: document\n\
Referer: http://localhost/login\n\
Accept-Encoding: gzip, deflate\n\
Accept-Language: sr-RS,sr;q=0.9,en-US;q=0.8,en;q=0.7\n\
Cookie: session_id=s3j32isTQg\n\
Connection: close\n\
\r\n\r\n\
username=username123&password=password123";

struct HttpRequestTest : public ::testing::Test {
  HttpRequest* request;
  HttpRequestTest() { request = new HttpRequest(raw_request); }
  virtual ~HttpRequestTest() { delete request; }
};

TEST_F(HttpRequestTest, MethodTest) {
  EXPECT_EQ(request->method_, HttpMethod::POST);
}

TEST_F(HttpRequestTest, PathTest) { ASSERT_TRUE(request->path_ == "/login"); }

TEST_F(HttpRequestTest, HeadersTest) {
  EXPECT_TRUE(request->headers_["Host"] == "localhost");
  EXPECT_TRUE(request->headers_["Content-Length"] == "41");
  EXPECT_TRUE(request->headers_["Cache-Control"] == "max-age=0");
  EXPECT_TRUE(request->headers_["sec-ch-ua"] == "");
  EXPECT_TRUE(request->headers_["sec-ch-ua-mobile"] == "?0");
  EXPECT_TRUE(request->headers_["sec-ch-ua-platform"] == "");
  EXPECT_TRUE(request->headers_["Upgrade-Insecure-Requests"] == "1");
  EXPECT_TRUE(request->headers_["Origin"] == "http://localhost");
  EXPECT_TRUE(request->headers_["Content-Type"] ==
              "application/x-www-form-urlencoded");
  EXPECT_TRUE(request->headers_["User-Agent"] ==
              "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
              "(KHTML, like Gecko) Chrome/114.0.5735.199 Safari/537.36");
  EXPECT_TRUE(
      request->headers_["Accept"] ==
      "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/"
      "webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7");
  EXPECT_TRUE(request->headers_["Sec-Fetch-Site"] == "same-origin");
  EXPECT_TRUE(request->headers_["Sec-Fetch-Mode"] == "navigate");
  EXPECT_TRUE(request->headers_["Sec-Fetch-User"] == "?1");
  EXPECT_TRUE(request->headers_["Sec-Fetch-Dest"] == "document");
  EXPECT_TRUE(request->headers_["Referer"] == "http://localhost/login");
  EXPECT_TRUE(request->headers_["Accept-Encoding"] == "gzip, deflate");
  EXPECT_TRUE(request->headers_["Accept-Language"] ==
              "sr-RS,sr;q=0.9,en-US;q=0.8,en;q=0.7");
  EXPECT_TRUE(request->headers_["Cookie"] == "session_id=s3j32isTQg");
  EXPECT_TRUE(request->headers_["Connection"] == "close");
}

TEST_F(HttpRequestTest, CookiesTest) {
  ASSERT_TRUE(request->cookies_["session_id"] == "s3j32isTQg");
}

TEST_F(HttpRequestTest, QueryTest) {
  EXPECT_TRUE(request->query_["username"] == "username123");
  EXPECT_TRUE(request->query_["password"] == "password123");
}