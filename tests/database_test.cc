#include "../include/databases/database.h"

#include "../include/databases/id_map.h"
#include "gtest/gtest.h"

struct DatabaseTest : public ::testing::Test {
  DatabaseTest() {
    DbData users_db_data = {"test database", "test", 0};
    users_database = new Database<User>("users_db_test.db", users_db_data);
  }

  virtual ~DatabaseTest() { delete users_database; }

  void SetUp() override {
    // remove("users_db_test.db");
  }

  void TearDown() override {
    // remove("users_db_test.db");
  }

  Database<User>* users_database;
};

static User CreateUser(const char* username, const char* password) {
  User user;
  user.id = 0;
  strncpy_s(user.username, username, 19);
  strncpy_s(user.password, password, 19);
  return user;
}

TEST_F(DatabaseTest, InsertionTest) {
  User user1 = {0, "testuser1", "pass123"};
  User user2 = {0, "testuser2", "asd123"};
  User user3 = {0, "testuser3", "123456"};

  int insertion1 = users_database->Insert(&user1);
  ASSERT_TRUE(insertion1 == 0);

  int insertion2 = users_database->Insert(&user2);
  ASSERT_TRUE(insertion1 == 0);

  int insertion3 = users_database->Insert(&user3);
  ASSERT_TRUE(insertion1 == 0);
}

TEST_F(DatabaseTest, ReadingByIdTest) {
  User user1 = users_database->GetDataByID(0);
  ASSERT_TRUE(user1.id == 0);
  ASSERT_TRUE(std::string(user1.username) == "testuser1");
  ASSERT_TRUE(std::string(user1.password) == "pass123");

  User user2 = users_database->GetDataByID(1);
  ASSERT_TRUE(user2.id == 1);
  ASSERT_TRUE(std::string(user2.username) == "testuser2");
  ASSERT_TRUE(std::string(user2.password) == "asd123");

  User user3 = users_database->GetDataByID(2);
  ASSERT_TRUE(user3.id == 2);
  ASSERT_TRUE(std::string(user3.username) == "testuser3");
  ASSERT_TRUE(std::string(user3.password) == "123456");
}