#include "../include/web_server.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include "../include/pages/page.h"
#include "../include/pages/pages.h"
#include "../include/utils.h"
#include "../include/network.h"

#ifndef _WIN32
static const auto closesocket = close;
#endif

WebServer::WebServer(std::string root, int port) {
  root_directory_ = root;
  port_ = port;

  DbData db_data = {"Users database",
                    "Database used for storing website users.", 0};

  static const int kMaxUsers = 1000000;
  databases_.users = std::make_shared<Database<User>>(
      "../databases/users_database.db", db_data);
  databases_.users->MakeSecondaryKey("../databases/users_username.db", 20,
                                     kMaxUsers);
}

int WebServer::StartWebServer() {
#ifdef _WIN32
  if (StartWSA() != 0) {
    std::cout << "Failed to start WSA\n";
    return -1;
  }
#endif

  socket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_ < 0) {
    std::cout << "Failed to create socket\n";
    return -2;
  }
#ifndef _WIN32
  int opt = 1;
  if(setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    std::cout << "Failed to setsockopt\n";
    return -5;
  }
#endif

  sock_address_.sin_addr.s_addr = INADDR_ANY;
  sock_address_.sin_port = htons(port_);
  sock_address_.sin_family = AF_INET;

  if (bind(socket_, (sockaddr*)&sock_address_, sizeof(sock_address_)) < 0) {
#ifdef _WIN32
    std::cout << "Failed to bind to port " << port_ << "\n";
#else
    std::cout << "Failed to bind to port " << port_ << (port_ < 1000 ? "! Try running as root\n" : "\n");  
#endif
    return -3;
  }

  if (listen(socket_, 5) < 0) {
    std::cout << "Failed to listen to port " << port_ << "\n";
    return -4;
  };
  return 0;
}
#include <errno.h>
HttpRequest WebServer::WaitForConnection() {
  HttpRequest request;

  sockaddr_in client_sock_address;
  int size = sizeof(client_sock_address);

  do {
#ifdef _WIN32
    request.socket_ = accept(socket_, (sockaddr*)&client_sock_address, &size);
#else
    request.socket_ = accept(socket_, (sockaddr*)&client_sock_address, (socklen_t*)&size);
#endif
   if (request.socket_ < 0) continue;
    request.sock_address_ = client_sock_address;
#ifdef _WIN32
    int timeout = 1000;
#else 
  static timeval timeout;
  timeout.tv_sec = 1;
  timeout.tv_usec = 0;
#endif
    if(setsockopt(request.socket_, SOL_SOCKET, SO_RCVTIMEO, &timeout,
               sizeof(timeout)) < 0) {
      std::cout << "Failed to set timeout for client socket!\n";
    }
  } while (ProcessConnection(request) != 0);

  return request;
}

int WebServer::ProcessConnection(HttpRequest& request) {
  static const int kBufferSize = 1024 * 4;

  char buffer[kBufferSize];
  const int request_size = recv(request.socket_, buffer, kBufferSize, 0);
  if (request_size < 0) {
    HttpResponse response(HttpStatus::REQUEST_TIMEOUT);
    RespondToRequest(request, response);
    return -1;
  }
  buffer[request_size] = '\0';
  std::string request_data = buffer;

  if (request.Parse(request_data) != 0) {
    HttpResponse response(HttpStatus::BAD_REQUEST);
    RespondToRequest(request, response);
    return -2;
  }

  request.SetIpAddress(request.sock_address_);

  return 0;
}

Session* WebServer::StartSession(HttpRequest& request) {
  if (KeyIn(request.cookies_, "session_id") &&
      KeyIn(sessions_, request.cookies_["session_id"])) {
    request.new_session_ = false;
    return &sessions_[request.cookies_["session_id"]];
  }

  std::string session_id = GenerateSessionId(10);
  sessions_[session_id] = Session();
  sessions_[session_id].id_ = session_id;
  request.new_session_ = true;
  return &sessions_[session_id];
}

std::string WebServer::GenerateSessionId(int size) {
  srand((unsigned int)time(NULL));
  static const char alphanum[] =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";
  std::string id;

  id.reserve(size);

  for (int i = 0; i < size; ++i) {
    id += alphanum[rand() % (sizeof(alphanum) - 1)];
  }
  return id;
}

#ifdef _WIN32
int WebServer::StartWSA() {
  WSADATA wsa;
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return -1;
  return 0;
}
#endif

int WebServer::GetFileContent(const std::string& path, std::string& content) {
  std::ifstream page(root_directory_ + path);
  if (!page.is_open()) return -1;

  std::string line;
  while (std::getline(page, line)) {
    content += line + "\n";
  }
  page.close();
  return 0;
}

void WebServer::SetDefaultHeaders(HttpResponse& response) {
  if (!KeyIn(response.headers_, "Content-Length"))
    response.headers_["Content-Length"] =
        std::to_string(response.content_.size());
  if (!KeyIn(response.headers_, "Server"))
    response.headers_["Server"] = "Lopata Server 1.0";
  if (!KeyIn(response.headers_, "Connection"))
    response.headers_["Connection"] = "closed";
  if (!KeyIn(response.headers_, "Content-Type"))
    response.headers_["Content-Type"] = "text/html; charset=utf-8";
}

bool WebServer::FileExists(const std::string& path) {
  std::ifstream page(root_directory_ + path);
  if (page.is_open()) {
    page.close();
    return true;
  }
  return false;
}

void WebServer::RespondToRequest(const HttpRequest& request,
                                 HttpResponse& response) {
  SetDefaultHeaders(response);
  std::string message = response.BuildResponse();
  send(request.socket_, message.c_str(), message.size(), 0);
  closesocket(request.socket_);
  return;
}

void WebServer::HandleRequest(HttpRequest& request) {
  Session* session = StartSession(request);
  if (request.new_session_) InitializeSessionData(session->id_);

  PageData page_data;
  page_data.request = request;
  page_data.session = session;
  page_data.users_db = databases_.users;

  static std::unordered_map<std::string, std::function<HttpResponse()>>
      route_handler = {
          {"/", [&]() { return HandlePage<IndexPage>(page_data); }},
          {"/login", [&]() { return HandlePage<LoginPage>(page_data); }},
          {"/register", [&]() { return HandlePage<RegisterPage>(page_data); }},
      };

  HttpResponse response = KeyIn(route_handler, request.path_)
                              ? route_handler[request.path_]()
                              : DefaultResponse(request);

  if (request.new_session_) SetSessionCookie(session, response);

  RespondToRequest(request, response);
  return;
}

void WebServer::SetSessionCookie(const Session* session,
                                 HttpResponse& response) {
  std::string cookie = "session_id=" + session->id_;
  response.headers_["Set-Cookie"] = cookie;
}

void WebServer::InitializeSessionData(const std::string& id) {
  sessions_[id].data_["logged_in"] = "false";
}

HttpResponse WebServer::DefaultResponse(const HttpRequest& request) {
  HttpResponse response;
  if (!FileExists(request.path_)) {
    response.SetHttpStatus(HttpStatus::NOT_FOUND);
    GetFileContent("404.html", response.content_);
    return response;
  }
  response.headers_["Content-Type"] = GetContentType(request.path_);
  GetFileContent(request.path_, response.content_);
  return response;
}

std::string WebServer::GetContentType(const std::string& file) {
  static const std::regex extension_regex("\\/\\w*\\.(\\w*)");
  static std::unordered_map<std::string, std::string> content_types = {
      {"txt", "text/plain"},
      {"css", "text/css"},
      {"javascript", "text/javascript"},
      {"html", "text/html"},
      {"xml", "text/xml"},
      {"csv", "text/csv"},
      {"gif", "image/gif"},
      {"tiff", "image/tiff"},
      {"jpeg", "image/jpeg"},
      {"jpg", "image/jpeg"},
      {"png", "image/png"}};

  std::smatch match;

  if (!std::regex_search(file, match, extension_regex) ||
      !KeyIn(content_types, match[1]))
    return "text/plain";

  return content_types[match[1]];
}
