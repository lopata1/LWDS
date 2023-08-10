#pragma once
#include <memory>

#include "../databases/database.h"
#include "../http_request.h"
#include "../http_response.h"
#include "../session.h"

struct PageData {
  HttpRequest request;
  Session *session;
  std::string html;
  std::shared_ptr<Database<User>> users_db;
};

class Page {
 public:
  Page(PageData page_data);
  virtual HttpResponse Handle();
  virtual HttpResponse HandlePost();
  virtual HttpResponse HandleGet() = 0;
  virtual std::string BuildPage() = 0;

 protected:
  PageData page_data_;
};
