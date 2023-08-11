#ifndef LWDS_API_INBOX_GET_H_
#define LWDS_API_INBOX_GET_H_

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

#endif  // LWDS_API_INBOX_GET_H_