#include "../include/preprocessor.h"

#include <regex>

std::string Preprocess(
    std::string html, std::unordered_map<std::string, std::string>& variables) {
  for (const auto& variable : variables) {
    std::regex variable_regex("(V\\(" + variable.first + "\\))");
    html = std::regex_replace(html, variable_regex, variable.second);
  }

  std::regex all_variables_regex("(V\\(\\w*\\))");
  html = std::regex_replace(html, all_variables_regex, "");

  return html;
}