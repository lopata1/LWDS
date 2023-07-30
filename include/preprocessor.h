#pragma once
#include <string>
#include <unordered_map>

std::string Preprocess(std::string html,
                       std::unordered_map<std::string, std::string>& variables);