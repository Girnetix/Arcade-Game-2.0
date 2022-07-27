#pragma once
#ifndef SERVER_H
#define SERVER_H

#include "Network.h"

#define MAX_CLIENTS 16

class CServer
{
private:
	struct ConnectedClient
	{
	public:
		int iPort;
		int id;
		sockaddr_in info;
	};
public:
	void Init(std::wstring ipAdress, uint32_t iPort, int maxClients = 8);
	void Start();
	void Stop();
	void Send(CPacket &packet, int iClient);
	void Receive(CPacket& packet, int iClient);
	void Update();
	int GetPing();
private:
	Socket sock;
	bool serverIsActive;
	std::wstring ipAdress;
	int iPort;
	int maxClients;
	static int idCounter;
private:
	std::vector<ConnectedClient*> connectedClients;
	std::vector<CPacket*> clientPackets;
	CPacket serverPacket;
};

#endif
