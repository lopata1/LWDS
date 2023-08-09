#include "../include/config_parser.h"
#include <fstream>
#include <iostream>
#include <regex>

std::unordered_map<std::string, std::string> ParseConfig(
  const std::string config_path) {
  std::ifstream config_file(config_path);
  if (!config_file.is_open()) {
    std::cout << "Failed to open config file\n";
    exit(-1);
  }
  std::string raw_config;
  std::getline(config_file, raw_config, '\0');

  std::unordered_map<std::string, std::string> config;

  std::regex config_regex("^(\\w*)\\s*=\\s*\\\"?(.*[^\"\\s])");
  std::smatch match;
  std::string::const_iterator search(raw_config.cbegin());
  while (std::regex_search(search, raw_config.cend(), match, config_regex)) {
    std::cout << match[1] << " = " << match[2] << "\n"; 
    config[match[1]] = match[2];
    search = match.suffix().first;
  }
  return config;
}
