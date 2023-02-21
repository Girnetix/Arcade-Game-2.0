#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include "Network.h"

class CClient
{
public:
	void Init();
	void Start();
	void Connect(std::string ipAdress, int iPort);
	void Stop();
	int Send(CPacket& packet);
	int Receive(CPacket &packet);
	void Update();
	int GetPing();
private:
	Socket sock;
	CPacket clientPacket;
	CPacket serverPacket;
	sockaddr_in serverInfo;
	NetworkMessageType nmType;
};

#endif