#pragma once
#include "../databases/database.h"
#include "../http_response.h"
#include "page.h"

class RegisterPage : public Page {
 public:
  RegisterPage(PageData page_data);
  HttpResponse HandlePost();
  HttpResponse Handle();
  std::string BuildPage();

  static const std::string file_location_;

 private:
  void CreateUser();
  HttpResponse DisplayError(std::string error);

  std::string error_message_;
};