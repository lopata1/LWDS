#pragma once
#include <vector>

#include "element.h"

class Html {
 public:
  void AddElement(Element element);
  std::string Build();

 private:
  std::vector<Element> elements_;
};