#ifndef LWDS_PAGES_REGISTER_H_
#define LWDS_PAGES_REGISTER_H_

#include "../databases/database.h"
#include "../http_response.h"
#include "page.h"

class RegisterPage : public Page {
 public:
  RegisterPage(PageData page_data);
  virtual HttpResponse HandlePost();
  virtual HttpResponse HandleGet();
  virtual std::string BuildPage();

  static const std::string page_location_;

 private:
  void CreateUser();
  HttpResponse DisplayError(std::string error);

  std::string error_message_;
};

#endif  // LWDS_PAGES_REGISTER_H_