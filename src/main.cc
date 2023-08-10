#include <iostream>

#include "../include/utils.h"
#include "../include/lwds.h"
#include "../include/config_parser.h"

void CreateDatabases(const int kMaxUsers);

int main() {
  std::unordered_map<std::string, std::string> config = ParseConfig("config.ini");
  const int kPort = std::stoi(config["port"]);
  const int kMaxUsers = std::stoi(config["database_max_users"]);
  
  CreateDatabases(kMaxUsers);

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

void CreateDatabases(const int kMaxUsers) {
  DbData db_data = {"Users database",
                    "Database used for storing website users.", 0};
  lwds::databases.users = std::make_shared<Database<User>>(
      "../databases/users_database.db", db_data);
  lwds::databases.users->MakeSecondaryKey("../databases/users_username.db",
                                            20, kMaxUsers);
}