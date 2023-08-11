#include <lwds/html/element.h>

Element::Element(std::string tag) { tag_ = tag; }

std::string Element::Build() {
  std::string html;

  html = "<" + tag_;
  for (auto &attribute : attributes_) {
    html += " " + attribute.first + "=\"" + attribute.second + "\"";
  }
  html += ">";
  html += text_;
  if (inner_html_ != nullptr) {
    html += "\n" + inner_html_->Build() + "\n";
  }
  html += "</" + tag_ + ">";
  return html;
}