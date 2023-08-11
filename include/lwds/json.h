#ifndef LWDS_JSON_H_
#define LWDS_JSON_H_

#include <string>
#include <map>
#include <variant>

class Json {
 public:
  std::string Build();
  
  template <typename T>
  void Set(std::string key, T value) {
    json_data_[key] = value;
  }

  template <typename T>
  T Get(std::string key) {
    return std::get<T>(json_data_[key]);
  }
 private:
  std::map<std::string, std::variant<Json, std::string, int>> json_data_;
};

#endif  // LWDS_JSON_H_