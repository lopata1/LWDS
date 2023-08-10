#include <iostream>

#include "../include/utils.h"
#include "../include/lwds.h"
#include "../include/config_parser.h"

void CreateDatabases(LWDS& server, const int kMaxUsers);

int main() {
  std::unordered_map<std::string, std::string> config = ParseConfig("config.ini");
  const int kPort = std::stoi(config["port"]);
  const int kMaxUsers = std::stoi(config["database_max_users"]);

  LWDS server(config["root_directory_path"], kPort);
  
  CreateDatabases(server, kMaxUsers);

  if (server.StartLWDS() != 0) {
    std::cout << "Failed to start LWDS\n";
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

void CreateDatabases(LWDS& server, const int kMaxUsers) {
  DbData db_data = {"Users database",
                    "Database used for storing website users.", 0};
  server.databases_.users = std::make_shared<Database<User>>(
      "../databases/users_database.db", db_data);
  server.databases_.users->MakeSecondaryKey("../databases/users_username.db",
                                            20, kMaxUsers);
}