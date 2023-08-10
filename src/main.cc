#include <iostream>

#include "../include/utils.h"
#include "../include/lwds.h"
#include "../include/config_parser.h"

int main() {
  std::unordered_map<std::string, std::string> config = ParseConfig("config.ini");
  const int kPort = std::stoi(config["port"]);
  const int kMaxData = std::stoi(config["database_max_data"]);
  
  CreateDatabases();
  CreateDatabasesSecondaryKey(kMaxData);

  if (lwds::Start(config["root_directory_path"], kPort) != 0) {
    std::cout << "Failed to start LWDS\n";
    return -1;
  }
  while (true) {
    HttpRequest request = lwds::WaitForConnection();
    std::cout << (request.method_ == HttpMethod::GET ? "GET: " : "POST: ")
              << request.path_ << " [" << request.ip_address_ << "]\n";
    lwds::HandleRequest(request);
  }

  return 0;
}