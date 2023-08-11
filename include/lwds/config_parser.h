#ifndef LWDS_CONFIG_PARSER_H_
#define LWDS_CONFIG_PARSER_H_

#include <unordered_map>
#include <string>

std::unordered_map<std::string, std::string> ParseConfig(
    const std::string config_path);

#endif  // LWDS_CONFIG_PARSER_H_