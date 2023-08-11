#pragma once
#include <string>
#include <unordered_map>

struct Session {
  std::string id_;
  std::unordered_map<std::string, std::string> data_;
};