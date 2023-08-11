#pragma once
#include <unordered_map>
#include <string>

class Element {
 public:
  Element(std::string tag);

  std::string Build();

  std::string tag_;
  std::string text_;
  std::unordered_map<std::string, std::string> attributes_;
  Element *inner_html_{};
};
