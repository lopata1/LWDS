#pragma once

#include <cstdarg>
#include <iostream>
#include <unordered_map>
#include <memory>

#include "databases/database.h"
#include "http_request.h"
#include "http_response.h"
#include "pages/page.h"
#include "session.h"
#include "network.h"

struct Databases {
  std::shared_ptr<Database<User>> users;
};

class LWDS {
 public:
  LWDS(std::string root = ".", int port = 80);

  int StartLWDS();
  HttpRequest WaitForConnection();
  bool FileExists(const std::string& kPath);
  int GetFileContent(const std::string& kPath, std::string& content);
  void RespondToRequest(const HttpRequest& kRequest, HttpResponse& response);
  int ProcessConnection(HttpRequest& request);
  Session* StartSession(HttpRequest& request);
  void HandleRequest(HttpRequest& request);
  void InitializeSessionData(const std::string& kId);
  HttpResponse DefaultResponse(const HttpRequest& kRequest);

  std::string root_directory_;
  int port_;
  Databases databases_;
  std::unordered_map<std::string, Session> sessions_;

 private:
  int StartWSA();
  std::string GenerateSessionId(int size);
  void SetDefaultHeaders(HttpResponse& response);
  std::string GetContentType(const std::string& kFile);
  void SetSessionCookie(const Session* kSession, HttpResponse& response);

  template <typename TPage>
  HttpResponse HandlePage(PageData& page_data) {
    GetFileContent(TPage::file_location_, page_data.html);
    return TPage(page_data).Handle();
  }

  SOCKET socket_;
  sockaddr_in sock_address_;
};
