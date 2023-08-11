#include <lwds/api/api.h>

Api::Api(ApiData api_data) { 
  api_data_ = api_data;
  json_.Set<int>("status", 200);
}