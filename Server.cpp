#pragma once
#include "Server.h"

void showMessageS(char* message, int lenght)
{
	std::cout << "\nClient: ";
	for (int i = 0; i < lenght; i++)
		std::cout << message[i];
	std::cout << "\n";
}

Server::Server()
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
}

Server::Server(const u_short port)
{
	//this->port = port;
}

Server::~Server()
{
	closesocket(listenSocket);
	WSACleanup();
}

int Server::start()
{
	iResult = WSAStartup(MAKEWORD(2, 2), &WData);
	if (iResult != 0)
	{
		std::cout << "\nError at WSAStartup!";
		return 1;
	}

	iResult = getaddrinfo(NULL, "27015", &hints, &result);
	if (iResult != 0)
	{
		std::cout << "\ngetaddrinfo error: " << iResult;
		WSACleanup();
		return 1;
	}

	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listenSocket == INVALID_SOCKET)
	{
		std::cout << "\nSocket creation error: " << WSAGetLastError();
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	iResult = bind(listenSocket, result->ai_addr, result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "\nBind failed: " << WSAGetLastError();
		freeaddrinfo(result);
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}
	freeaddrinfo(result);

	if (listening() == 1)
		return 1;

	return 0;
}
int Server::listening()
{
	std::cout << "\nWaiting for connections...";

	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cout << "\nListen failed with error: " << WSAGetLastError();
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	if (handleConn() == 1)
		return 1;

	/*std::thread th(&Server::handleConn, this);
	th.detach();*/

	return 0;
}

int Server::handleConn()
{
	ClientSocket = INVALID_SOCKET;
	ClientSocket = accept(listenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET)
	{
		std::cout << "\nAccept failed with error: " << WSAGetLastError();
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	std::thread th(&Server::recvData, this);
	th.detach();

	return 0;
}

int Server::recvData()
{
	char recvbuf[1024];
	do
	{
		iResult = recv(ClientSocket, recvbuf, 1024, 0);
		if (iResult > 0)
		{
			showMessageS(recvbuf, iResult);
		}
		else
		{
			std::cout << "\nÎøèáêà recv " << WSAGetLastError();
			closesocket(ClientSocket);
			WSACleanup();
			return -1;
		}
	} while (iResult > 0);

	return 0;
}

int Server::sendMessage(char* message)
{
	iResult = send(ClientSocket, message, strlen(message), 0);
	if (iResult < 0)
	{
		std::cout << "\nSend error:" << WSAGetLastError();
		return -1;
	}
	return 0;
}

void Server::shutdown()
{
	Server::~Server();
}