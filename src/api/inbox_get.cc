#include <lwds/api/inbox_get.h>
#include <lwds/utils.h>

const std::string InboxGetApi::endpoint_ = "/inbox/get";

InboxGetApi::InboxGetApi(ApiData api_data) : Api(api_data) {}

HttpResponse InboxGetApi::Handle() { 
  if (api_data_.request.method_ != HttpMethod::GET ||
      !KeyIn(api_data_.request.query_, "inbox_id")) {
    SetInvalidRequest();
    response_.content_ = json_.Build();
    return response_;
  }

  int inbox_id = std::stoi(api_data_.request.query_["inbox_id"]);
  Inbox inbox = api_data_.db.inboxes->GetDataByID(inbox_id);

  json_.Set<int>("id", inbox.id);
  json_.Set<int>("user1_id", inbox.user1_id);
  json_.Set<int>("user2_id", inbox.user2_id);
  response_.content_ = json_.Build();
  return response_;
}