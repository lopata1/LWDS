#include <lwds/html/preprocessor.h>
#include <lwds/pages/index.h>

#include <iostream>
#include <unordered_map>

const std::string IndexPage::page_location_ = "index.html";

IndexPage::IndexPage(PageData page_data) : Page(page_data) {}

std::string IndexPage::BuildPage() {
  std::unordered_map<std::string, std::string> variables;

  User user = page_data_.db.users->GetDataByID(
      std::stoi(page_data_.session->data_["id"]));

  variables["username"] = user.username;

  return Preprocess(page_data_.html, variables);
}

HttpResponse IndexPage::HandleGet() {
  HttpResponse response;

  if (page_data_.session->data_["logged_in"] == "false") {
    response.SetHttpStatus(HttpStatus::FOUND);
    response.headers_["Location"] = "/login";
    return response;
  }

  response.content_ = BuildPage();

  return response;
}