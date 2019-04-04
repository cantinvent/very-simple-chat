#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <thread>

class Server
{
	WSADATA WData;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	SOCKET listenSocket = INVALID_SOCKET;

	SOCKET ClientSocket;

	int iResult;

	//u_short port;
public:
	Server();
	Server(const u_short port);
	~Server();
	int start();
	void shutdown();
	int listening();
	int handleConn();
	int recvData();
	int sendMessage(char* message);
};