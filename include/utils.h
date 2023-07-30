#pragma once
#include <string>
#include <unordered_map>

std::string CharToString(char* c);

template <typename T1, typename T2, typename T3>
bool KeyIn(const std::unordered_map<T1, T2>& map, const T3& key) {
  return map.find(key) != map.end();
}