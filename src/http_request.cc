#include "../include/http_request.h"

#include <iostream>
#include <regex>

#include "../include/utils.h"

HttpRequest::HttpRequest(std::string& request_data) { Parse(request_data); }

int HttpRequest::Parse(std::string& request_data) {
  int head_body_separator = request_data.find("\r\n\r\n");
  if (head_body_separator == -1) return -1;
  std::string head_data = request_data.substr(0, head_body_separator);
  std::string body_data =
      request_data.substr(head_body_separator, request_data.size());

  ParseMethod(head_data);
  ParsePath(head_data);
  ParseHeaders(head_data);
  ParseCookies(head_data);
  ParseQuery(body_data);

  return 0;
}

int HttpRequest::ParseHeaders(const std::string& head_data) {
  std::smatch match;
  std::regex headers_regex("(.*): (.*)");
  std::string::const_iterator search_start(head_data.cbegin());
  while (
      std::regex_search(search_start, head_data.cend(), match, headers_regex)) {
    headers_[match[1]] = match[2];
    search_start = match.suffix().first;
  }
  return 0;
}

int HttpRequest::ParsePath(const std::string& head_data) {
  std::regex path_regex("^[A-Z]* (.*) ");
  std::smatch match;
  if (!std::regex_search(head_data, match, path_regex)) return -1;

  path_ = match[1];
  return 0;
}

int HttpRequest::ParseMethod(const std::string& head_data) {
  std::regex method_regex("^([A-Z]*) ");
  std::smatch match;
  if (!std::regex_search(head_data, match, method_regex)) return -1;
  method_ = match[1] == "GET" ? HttpMethod::GET : HttpMethod::POST;
  return 0;
}

int HttpRequest::ParseCookies(const std::string& head_data) {
  if (!KeyIn(headers_, "Cookie")) return -1;
  std::smatch match;
  std::regex cookies_regex("(\\w+)=(\\w+)");
  std::string::const_iterator search(headers_["Cookie"].cbegin());
  while (std::regex_search(search, headers_["Cookie"].cend(), match,
                           cookies_regex)) {
    cookies_[match[1]] = match[2];
    search = match.suffix().first;
  }
  return 0;
}

int HttpRequest::ParseQuery(const std::string& body_data) {
  std::regex query_regex("([\\w, -]+)=(\\w+)");
  std::smatch match;
  std::string::const_iterator search(body_data.cbegin());
  while (std::regex_search(search, body_data.cend(), match, query_regex)) {
    query_[match[1]] = match[2];
    search = match.suffix().first;
  }
  return 0;
}

std::string HttpRequest::ConvertNumberToIp(unsigned int ip_number) {
  std::string ip_address = std::to_string(ip_number & 0xFF) + "." +
                           std::to_string((ip_number & 0xFF00) >> 8) + "." +
                           std::to_string((ip_number & 0xFF0000) >> 16) + "." +
                           std::to_string((ip_number & 0xFF000000) >> 24);
  return ip_address;
}

void HttpRequest::SetIpAddress(sockaddr_in& sock_address) {
  ip_address_ =
      ConvertNumberToIp((unsigned int)sock_address.sin_addr.S_un.S_addr);
}
