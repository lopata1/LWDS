#pragma once
#include "../databases/database.h"
#include "../http_request.h"
#include "../http_response.h"
#include "api.h"

class InboxGetApi : public Api {
 public:
  InboxGetApi(ApiData api_data);
  virtual HttpResponse Handle();

  static const std::string endpoint_;
};