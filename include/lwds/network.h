#ifndef LWDS_NETWORK_H_
#define LWDS_NETWORK_H_

#ifdef _WIN32

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#else

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

typedef int SOCKET;

#endif

#endif  // LWDS_NETWORK_H_