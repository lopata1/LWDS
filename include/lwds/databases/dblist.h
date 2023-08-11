#ifndef LWDS_DATABASES_DBLIST_H_
#define LWDS_DATABASES_DBLIST_H_

#include <lwds/databases/database.h>

#include <memory>

struct Databases {
  std::shared_ptr<Database<User>> users;
  std::shared_ptr<Database<Inbox>> inboxes;
  std::shared_ptr<Database<Message>> messages;
};

void CreateDatabases();

void CreateDatabasesSecondaryKey(const int kMaxData);

#endif  // LWDS_DATABASES_DBLIST_H_