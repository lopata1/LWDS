#pragma once
#include "../databases/database.h"
#include "../http_request.h"
#include "../http_response.h"
#include "page.h"

class LoginPage : public Page {
 public:
  LoginPage(PageData data);
  HttpResponse HandlePost();
  HttpResponse Handle();
  std::string BuildPage();

  static const std::string file_location_;

 private:
  bool login_failed_ = false;
};