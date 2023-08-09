#include <iostream>

#include "../include/utils.h"
#include "../include/web_server.h"
#include "../include/config_parser.h"

int main() {
  auto config = ParseConfig("config.ini");
  const int port = std::stoi(config["port"]);
  WebServer server(config["root_directory_path"], port);

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
