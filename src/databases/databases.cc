#include "../../include/databases/databases.h"
#include "../../include/lwds.h"

void CreateDatabases() {
  DbData db_data = {"Users database",
                    "Database used for storing website users.", 0};
  lwds::databases.users = std::make_shared<Database<User>>(
      "../databases/users_database.db", db_data);
}

void CreateDatabasesSecondaryKey(const int kMaxData) {
  lwds::databases.users->MakeSecondaryKey("../databases/users_username.db", 20,
                                          kMaxData);
}