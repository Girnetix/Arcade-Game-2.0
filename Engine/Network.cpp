#include "Network.h"

Network* pNetwork = nullptr;

bool Network::Initialize()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0)
	{
		//������� ���������� �� ������
		return false;
	}
	return true;
}

bool Network::Shutdown()
{
	return WSACleanup();
}

Network::~Network()
{
	Shutdown();
}
