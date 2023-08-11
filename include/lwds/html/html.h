#ifndef LWDS_HTML_HTML_H_
#define LWDS_HTML_HTML_H_

#include <vector>

#include "element.h"

class Html {
 public:
  void AddElement(Element element);
  std::string Build();

 private:
  std::vector<Element> elements_;
};

#endif  // LWDS_HTML_HTML_H_