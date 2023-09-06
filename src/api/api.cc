#include <lwds/api/api.h>

Api::Api(ApiData api_data) { 
  api_data_ = api_data;
  json_.Set<int>("status", 200);
  response_.headers_["Content-Type"] = "application/json";
}

void Api::SetInvalidRequest() {
  response_.SetHttpStatus(HttpStatus::BAD_REQUEST);
  json_.Set<int>("status", 400);
  json_.Set<std::string>("error_message", "Invalid request.");
}