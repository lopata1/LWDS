#pragma once

#include "../databases/database.h"
#include "../databases/dblist.h"
#include "../http_request.h"
#include "../http_response.h"
#include "../session.h"
#include "../json.h"

struct ApiData {
  HttpRequest request;
  Session* session;
  Databases db;
};

class Api {
 public:
  Api(ApiData api_data);
  virtual HttpResponse Handle() = 0;

 protected:
  ApiData api_data_;
  Json json_;
};
