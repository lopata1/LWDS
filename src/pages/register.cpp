#include "../../include/pages/register.h"

#include "../../include/html/html.h"
#include "../../include/preprocessor.h"
#include "../../include/utils.h"

const std::string RegisterPage::file_location_ = "register.html";

RegisterPage::RegisterPage(PageData pdata) : Page(pdata) {}

HttpResponse RegisterPage::HandlePost() {
  HttpResponse response;
  if (!KeyIn(page_data_.request.query_, "username") ||
      !KeyIn(page_data_.request.query_, "password") ||
      !KeyIn(page_data_.request.query_, "retyped-password")) {
    response.SetHttpStatus(HttpStatus::BAD_REQUEST);
    return response;
  }

  if (page_data_.request.query_["username"].size() < 3)
    return DisplayError("Username must be atleast 3 characters long");

  std::vector<User> found =
      page_data_.users_db->GetAllDataWhere([=](User* user) {
        return user->username == page_data_.request.query_["username"];
      });

  if (found.size() > 0) return DisplayError(">Username already exists");

  if (page_data_.request.query_["password"].size() < 6)
    return DisplayError("Password must be atleast 6 characters long");

  if (page_data_.request.query_["password"] !=
      page_data_.request.query_["retyped-password"])
    return DisplayError("Passwords must match");

  CreateUser();

  response.SetHttpStatus(HttpStatus::FOUND);
  response.headers_["Location"] = "/login";

  return response;
}

void RegisterPage::CreateUser() {
  User user;
  strncpy_s(user.username, page_data_.request.query_["username"].c_str(),
            sizeof(user.username) - 1);
  strncpy_s(user.password, page_data_.request.query_["password"].c_str(),
            sizeof(user.password) - 1);

  page_data_.users_db->Insert(&user);
  page_data_.users_db->id_map_.Insert(user.username, user.id);
}

HttpResponse RegisterPage::DisplayError(std::string error) {
  HttpResponse response;
  Element error_message("p");
  error_message.attributes_["id"] = "error-message";
  error_message.text_ = error;

  error_message_ = error_message.Build();

  response.content_ = BuildPage();
  return response;
}

HttpResponse RegisterPage::Handle() {
  if (page_data_.request.method_ == HttpMethod::POST) return HandlePost();

  HttpResponse response;

  if (page_data_.session->data_["logged_in"] == "true") {
    response.SetHttpStatus(HttpStatus::FOUND);
    response.headers_["Location"] = "/";
  }

  response.content_ = BuildPage();

  return response;
}

std::string RegisterPage::BuildPage() {
  std::unordered_map<std::string, std::string> variables;

  variables["error_message"] = error_message_;

  return Preprocess(page_data_.html, variables);
}