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
#include "databases/databases.h"

namespace lwds {
  int Start(std::string root = ".", int port = 80);
  HttpRequest WaitForConnection();
  bool FileExists(const std::string& kPath);
  int GetFileContent(const std::string& kPath, std::string& content);
  void RespondToRequest(const HttpRequest& kRequest, HttpResponse& response);
  int ProcessConnection(HttpRequest& request);
  Session* StartSession(HttpRequest& request);
  void HandleRequest(HttpRequest& request);
  void InitializeSessionData(const std::string& kId);
  HttpResponse DefaultResponse(const HttpRequest& kRequest);
  int StartWSA();
  std::string GenerateSessionId(int size);
  void SetDefaultHeaders(HttpResponse& response);
  std::string GetContentType(const std::string& kFile);
  void SetSessionCookie(const Session* kSession, HttpResponse& response);

  template <typename TPage>
  HttpResponse HandlePage(PageData& page_data) {
    GetFileContent(TPage::page_location_, page_data.html);
    return TPage(page_data).Handle();
  }

  extern std::string root_directory;
  extern int port;
  extern Databases databases;
  extern std::unordered_map<std::string, Session> sessions;
  extern SOCKET lwds_socket;
  extern sockaddr_in sock_address;
};
