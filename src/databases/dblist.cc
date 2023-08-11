#include <lwds/databases/dblist.h>
#include <lwds/lwds.h>

void CreateDatabases() {
  DbData db_data = {"Users",
                    "Database used for storing website users.", 0};
  lwds::databases.users = std::make_shared<Database<User>>(
      "../databases/users.db", db_data);

  db_data = {"Inboxes", "Database used for storing website inboxes.", 0};
  lwds::databases.inboxes = std::make_shared<Database<Inbox>>(
      "../databases/inboxes.db", db_data);

  db_data = {"Messages", "Database used for storing inbox messages.",
             0};
  lwds::databases.messages = std::make_shared<Database<Message>>(
      "../databases/messages.db", db_data);
}

void CreateDatabasesSecondaryKey(const int kMaxData) {
  lwds::databases.users->MakeSecondaryKey("../databases/users_username.db", 20,
                                          kMaxData);
}