#pragma once

#include "../databases/database.h"
#include "../databases/dblist.h"
#include "../http_request.h"
#include "../http_response.h"
#include "../session.h"

struct ApiData {
  HttpRequest request;
  Session* session;
  Databases db;
};

class Api {
 public:
  Api(ApiData api_data);
  virtual HttpResponse Handle() = 0;
  virtual std::string BuildJson() = 0;

 protected:
  ApiData api_data_;
};
