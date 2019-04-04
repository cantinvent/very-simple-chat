#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include<WinSock2.h>
#include <WS2tcpip.h>
#include <thread>


class Client
{
	WSADATA WData;
	char* buff;
	int iResult;
	SOCKET clientSock = INVALID_SOCKET;
public:
	Client();
	~Client();
	int connectToServer();
	void close();
	int sendMessage(char* message);
	int dataRecv();
};