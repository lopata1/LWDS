#pragma once
#include <iostream>

#include "../databases/database.h"
#include "../http_request.h"
#include "../http_response.h"
#include "page.h"

class IndexPage : public Page {
 public:
  IndexPage(PageData page_data);
  virtual HttpResponse HandleGet();
  virtual std::string BuildPage();

  static const std::string page_location_;

 private:
};