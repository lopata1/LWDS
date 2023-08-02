#include "gtest/gtest.h"

static void SetUpTestSuite() {
  remove("users_db_test.db");
  return;
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  SetUpTestSuite();
  return RUN_ALL_TESTS();
}