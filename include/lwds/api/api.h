#ifndef LWDS_API_API_H_
#define LWDS_API_API_H_

#include "../databases/database.h"
#include "../databases/dblist.h"
#include "../http_request.h"
#include "../http_response.h"
#include "../json.h"
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

 protected:
  ApiData api_data_;
  Json json_;
};

#endif  // LWDS_API_API_H_