#ifndef LWDS_PAGES_PAGE_H_
#define LWDS_PAGES_PAGE_H_

#include <memory>

#include "../databases/database.h"
#include "../databases/dblist.h"
#include "../http_request.h"
#include "../http_response.h"
#include "../session.h"

struct PageData {
  HttpRequest request;
  Session* session;
  std::string html;
  //std::shared_ptr<Database<User>> users;
  Databases db;
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

#endif  // LWDS_PAGES_PAGE_H_