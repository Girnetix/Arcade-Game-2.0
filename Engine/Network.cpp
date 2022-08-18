#include "Network.h"

Network* pNetwork = nullptr;

Point::Point(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Point& Point::operator=(Point& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

bool Network::Initialize()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0)
	{
		//вывести информацию об ошибке
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
