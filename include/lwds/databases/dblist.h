#pragma once
#include <lwds/databases/database.h>

#include <memory>

struct Databases {
  std::shared_ptr<Database<User>> users;
  std::shared_ptr<Database<Inbox>> inboxes;
  std::shared_ptr<Database<Message>> messages;
};

void CreateDatabases();

void CreateDatabasesSecondaryKey(const int kMaxData);