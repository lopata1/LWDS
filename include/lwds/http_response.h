#pragma once
#include <iostream>
#include <unordered_map>

enum class HttpStatus {
  OK = 200,
  MOVED_PERMANENTLY = 301,
  FOUND = 302,
  TEMPORARY_REDIRECT = 307,
  PERMANENT_REDIRECT = 308,
  BAD_REQUEST = 400,
  NOT_FOUND = 404,
  REQUEST_TIMEOUT = 408
};

class HttpResponse {
 public:
  HttpResponse(){};
  HttpResponse(const HttpStatus s);
  std::string BuildResponse();
  void SetHttpStatus(const HttpStatus s);

  HttpStatus status_ = HttpStatus::OK;
  std::unordered_map<std::string, std::string> headers_;
  std::string content_;
  std::string status_message_;
};