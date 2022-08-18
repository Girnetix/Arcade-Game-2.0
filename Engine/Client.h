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
	void Send();
	void Receive();
	void Update();
	int GetPing();
private:
	Socket sock;
	CPacket clientPacket;
	sockaddr_in serverInfo;
	NetworkMessageType nmType;
};

#endif