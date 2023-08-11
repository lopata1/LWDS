#include <lwds/api/inbox_get.h>

const std::string InboxGetApi::endpoint_ = "/inbox/get";

InboxGetApi::InboxGetApi(ApiData api_data) : Api(api_data) {}

HttpResponse InboxGetApi::Handle() { 
  HttpResponse response;
  response.headers_["Content-Type"] = "application/json";
  if (api_data_.request.method_ != HttpMethod::GET) {
    response.SetHttpStatus(HttpStatus::BAD_REQUEST);
    json_.Set<int>("status", 400);
    json_.Set<std::string>("error_message", "Invalid request.");
    response.content_ = json_.Build();
    return response;
  }

}