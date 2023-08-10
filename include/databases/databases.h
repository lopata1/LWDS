#pragma once
#include <memory>
#include "../../include/databases/database.h"

struct Databases {
  std::shared_ptr<Database<User>> users;
};

void CreateDatabases();

void CreateDatabasesSecondaryKey(const int kMaxData);