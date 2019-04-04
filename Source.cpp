#include <iostream>
#include <string>
#include "Client.h"
#include "Server.h"


int main()
{
	setlocale(LC_ALL, "ru");
	int check;
	std::cout << "1 - Server | 2 - Client";
	std::cout << "\nYour choice: ";
	std::cin >> check;

	std::string line;
	char* message;

	if (check == 1)
	{
		Server server;
		server.start();

		do
		{
			//	std::cout << "\nServer: ";
			std::cin >> line;
			if (line == "#stop")
				server.shutdown();
			else
			{
				message = new char[line.length() + 1];
				strcpy(message, line.c_str());
				server.sendMessage(message);
			}
		} while (line != "#stop");
	}
	else
	{
		Client client;
		client.connectToServer();

		do
		{
			//	std::cout << "\nClient: ";
			std::cin >> line;
			if (line == "#exit")
				client.close();
			else
			{
				message = new char[line.length() + 1];
				strcpy(message, line.c_str());
				client.sendMessage(message);
			}
		} while (line != "#exit");
	}



	std::cout << std::endl;
	return 0;
}