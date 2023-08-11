#include "../include/json.h"

std::string Json::Build() {
  std::string result;
  result += "{";
  const size_t kDataSize = json_data_.size();
  int i = 0;
  for (auto &data : json_data_) {
    result += "\"" + data.first + "\": ";

    if (std::holds_alternative<Json>(data.second)) {
      result += std::get<Json>(data.second).Build();
    } else if (std::holds_alternative<std::string>(data.second)) {
      result += "\"" + std::get<std::string>(data.second) + "\"";
    } else {
      result += std::to_string(std::get<int>(data.second));
    }

    result += i != kDataSize - 1 ? ", " : "}";
    i++;
  }
  return result;
}