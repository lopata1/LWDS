#ifndef LWDS_PAGES_LOGIN_H_
#define LWDS_PAGES_LOGIN_H_

#include "../databases/database.h"
#include "../http_request.h"
#include "../http_response.h"
#include "page.h"

class LoginPage : public Page {
 public:
  LoginPage(PageData data);
  virtual HttpResponse HandlePost();
  virtual HttpResponse HandleGet();
  virtual std::string BuildPage();

  static const std::string page_location_;

 private:
  bool login_failed_ = false;
};

#endif  // LWDS_PAGES_LOGIN_H_