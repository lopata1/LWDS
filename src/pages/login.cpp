#include "../../include/pages/login.h"

#include <unordered_map>
#include <vector>

#include "../../include/html/preprocessor.h"
#include "../../include/utils.h"
#include "../../include/html/html.h"

const std::string LoginPage::file_location_ = "login.html";

LoginPage::LoginPage(PageData page_data) : Page(page_data) {}

HttpResponse LoginPage::HandlePost() {
  HttpResponse response;

  if (!KeyIn(page_data_.request.query_, "username") ||
      !KeyIn(page_data_.request.query_, "password")) {
    response.SetHttpStatus(HttpStatus::BAD_REQUEST);
    return response;
  }

  int user_id = page_data_.users_db->GetIdBySecondaryKey(
      page_data_.request.query_["username"]);
  if (user_id == -1) {
    login_failed_ = true;
    response.content_ = BuildPage();
    return response;
  }

  User user = page_data_.users_db->GetDataByID(user_id);

  if (user.password != page_data_.request.query_["password"]) {
    login_failed_ = true;
    response.content_ = BuildPage();
    return response;
  }

  response.SetHttpStatus(HttpStatus::FOUND);
  response.headers_["Location"] = "/";
  page_data_.session->data_["logged_in"] = "true";
  page_data_.session->data_["id"] = std::to_string(user_id);

  return response;
}

HttpResponse LoginPage::Handle() {
  if (page_data_.request.method_ == HttpMethod::POST) return HandlePost();

  HttpResponse response;

  if (page_data_.session->data_["logged_in"] == "true") {
    response.SetHttpStatus(HttpStatus::FOUND);
    response.headers_["Location"] = "/";
  }
  response.content_ = BuildPage();

  return response;
}

std::string LoginPage::BuildPage() {
  std::unordered_map<std::string, std::string> variables;

  if (login_failed_) {
    Element error_message("p");
    error_message.attributes_["id"] = "error-message";
    error_message.text_ = "Username or password is incorrect.";
    variables["error_message"] = error_message.Build();
  }
    

  return Preprocess(page_data_.html, variables);
}