#pragma once
#include <iostream>

#include "../databases/database.h"
#include "../http_request.h"
#include "../http_response.h"
#include "page.h"

class IndexPage : public Page {
 public:
  IndexPage(PageData page_data);
  HttpResponse Handle();
  std::string BuildPage();

  static const std::string file_location_;

 private:
};