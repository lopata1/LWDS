#include "../../include/api/inbox_get.h"

InboxGetApi::InboxGetApi(ApiData api_data) : Api(api_data) {}

HttpResponse InboxGetApi::Handle() { 
  HttpResponse response;
  if (api_data_.request.method_ != HttpMethod::GET) {
    response.SetHttpStatus(HttpStatus::BAD_REQUEST);
    return response;
  }
}