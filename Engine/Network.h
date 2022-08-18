#pragma once
#ifndef NETWORK_H
#define NETWORK_H

#include <WinSock2.h>
#include <WS2tcpip.h>

#include "Rendering.h"
#include "Log.h"
#include "Socket.h"
#include "NetworkMessage.h"

#pragma comment(lib, "ws2_32.lib")

class Point
{
public:
	Point(int x, int y, int z);
	Point& operator=(Point& other);
private:
	int x, y, z;
};

class Network
{
public:
	bool Initialize();
	bool Shutdown();
	~Network();
private:
	WSAData wsData;
};

extern Network* pNetwork;

#endif
