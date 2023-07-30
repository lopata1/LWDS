#pragma once
#include <WinSock2.h>

#include <iostream>
#include <unordered_map>

enum class HttpMethod { GET, POST };

class HttpRequest {
 public:
  HttpRequest(std::string& request_data);
  HttpRequest(){};

  void SetIpAddress(sockaddr_in& sock_address);
  int Parse(std::string& request_data);

  HttpMethod method_ = HttpMethod::GET;
  std::string path_;
  std::string ip_address_;
  sockaddr_in sock_address_{};
  SOCKET socket_{};
  std::unordered_map<std::string, std::string> headers_;
  std::unordered_map<std::string, std::string> cookies_;
  std::unordered_map<std::string, std::string> query_;
  bool new_session_;

 private:
  std::string ConvertNumberToIp(unsigned int ip_number);
  int ParseHeaders(const std::string& head_data);
  int ParsePath(const std::string& head_data);
  int ParseMethod(const std::string& head_data);
  int ParseCookies(const std::string& head_data);
  int ParseQuery(const std::string& body_data);
};