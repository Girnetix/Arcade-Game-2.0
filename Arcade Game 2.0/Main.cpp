#include "Game.h"

#include <Engine/Server.h>
#include <Engine/Client.h>
#include <iostream>

int main()
{
	pTimer = new Timer();
	pNetwork = new Network();
	pNetwork->Initialize();
	int result = 0;
	std::cin >> result;

	if (result == 1)
	{
		CServer server;
		server.Init("127.0.0.1", 11111);
		server.Start();
		while (true)
		{
			server.Update();
		}
	}
	else
	{
		CClient client;
		client.Init();
		client.Connect("127.0.0.1", 11111);
	}


	CGame* pGame = new CGame();
	pGame->Start(120, 50, L"Аркадная игра");

	delete pGame;
	return 0;
}