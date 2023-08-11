#pragma once
#include "../databases/database.h"
#include "../http_request.h"
#include "../http_response.h"
#include "api.h"

class InboxGetApi : public Api {
 public:
  InboxGetApi(ApiData api_data);
  virtual HttpResponse Handle();
  virtual std::string BuildJson();

  static const std::string page_location_;

 private:
  bool login_failed_ = false;
};