#include <lwds/http_response.h>
#include <lwds/network.h>

#include <string>

HttpResponse::HttpResponse(const HttpStatus s) { SetHttpStatus(s); }

std::string HttpResponse::BuildResponse() {
  std::string response;
  response +=
      "HTTP/1.1 " + std::to_string((int)status_) + " " + status_message_;

  for (const auto& header : headers_) {
    response += "\r\n" + header.first + ": " + header.second;
  }

  response += "\r\n\r\n" + content_;
  return response;
}

void HttpResponse::SetHttpStatus(const HttpStatus s) {
  switch (s) {
    case HttpStatus::OK:
      status_message_ = "OK";
      break;
    case HttpStatus::BAD_REQUEST:
      status_message_ = "Bad Request";
      break;
    case HttpStatus::NOT_FOUND:
      status_message_ = "Not Found";
      break;
    case HttpStatus::MOVED_PERMANENTLY:
      status_message_ = "Moved Permanently";
      break;
    case HttpStatus::REQUEST_TIMEOUT:
      status_message_ = "Request Timeout";
      break;
    case HttpStatus::PERMANENT_REDIRECT:
      status_message_ = "Permanent Redirect";
      break;
    case HttpStatus::TEMPORARY_REDIRECT:
      status_message_ = "Temporary Redirect";
      break;
    case HttpStatus::FOUND:
      status_message_ = "Found";
      break;
    default:
      std::cout << "Invalid status\n";
      break;
  }
  status_ = s;
  return;
}
