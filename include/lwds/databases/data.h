#pragma once

struct User {
  unsigned int id;
  char username[20];
  char password[20];
};

struct Inbox {
  unsigned int id;
  unsigned int user1_id;
  unsigned int user2_id;
};

struct Message {
  unsigned int id;
  unsigned int inbox_id;
  unsigned int author_id;
  char content[500];
};