#ifndef LWDS_SESSION_H_
#define LWDS_SESSION_H_

#include <string>
#include <unordered_map>

struct Session {
  std::string id_;
  std::unordered_map<std::string, std::string> data_;
};

#endif  // LWDS_SESSION_H_