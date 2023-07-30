#include <filesystem>
#include <iostream>

#include "../include/utils.h"
#include "../include/web_server.h"

static const std::filesystem::path relative_server_root = "../web/";
static const std::string absolute_server_root =
    std::filesystem::absolute(relative_server_root).generic_string();

static WebServer server(absolute_server_root, 80);
int main() {
  if (server.StartWebServer() != 0) {
    std::cout << "Failed to start a web server\n";
    return -1;
  }
  while (true) {
    HttpRequest request = server.WaitForConnection();
    std::cout << (request.method_ == HttpMethod::GET ? "GET: " : "POST: ")
              << request.path_ << " [" << request.ip_address_ << "]\n";
    server.HandleRequest(request);
  }

  return 0;
}