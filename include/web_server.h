#pragma once
#include <winsock2.h>

#include <cstdarg>
#include <iostream>
#include <unordered_map>

#include "databases/database.h"
#include "http_request.h"
#include "http_response.h"
#include "pages/page.h"
#include "session.h"

#pragma comment(lib, "ws2_32.lib")

struct Databases {
  std::shared_ptr<Database<User>> users;
};

class WebServer {
 public:
  WebServer(std::string root = ".", int port = 80);

  int StartWebServer();
  HttpRequest WaitForConnection();
  bool FileExists(const std::string& path);
  int GetFileContent(const std::string& path, std::string& content);
  void RespondToRequest(const HttpRequest& request, HttpResponse& response);
  int ProcessConnection(HttpRequest& request);
  Session* StartSession(HttpRequest& request);
  void HandleRequest(HttpRequest& request);
  void InitializeSessionData(const std::string& id);
  HttpResponse DefaultResponse(const HttpRequest& request);

  std::string root_directory_;
  int port_;
  Databases databases_;
  std::unordered_map<std::string, Session> sessions_;

 private:
  int StartWSA();
  std::string GenerateSessionId(int size);
  void SetDefaultHeaders(HttpResponse& response);
  std::string GetContentType(const std::string& file);
  void SetSessionCookie(const Session* session, HttpResponse& response);

  template <typename TPage>
  HttpResponse HandlePage(PageData& page_data) {
    GetFileContent(TPage::file_location_, page_data.html);
    return TPage(page_data).Handle();
  }

  SOCKET socket_;
  sockaddr_in sock_address_;
};