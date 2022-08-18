#pragma once
#ifndef SERVER_H
#define SERVER_H

#include "Network.h"

#define MAX_CLIENTS 16

extern const double TimeoutConnection;

class CServer
{
private:
	struct ConnectedClient
	{
	public:
		int iPort;
		int id;
		sockaddr_in info;
		CTimerValue lastReceivedMessage;
	};
public:
	void Init(std::string ipAdress, uint32_t iPort, int maxClients = 8);
	void Start();
	void Stop();
	void Send(CPacket &packet);
	void Receive(CPacket& packet);
	void Update();
	int GetPing();
private:
	Socket sock;
	bool serverIsActive, serverInitialized;
	std::string ipAdress;
	int iPort;
	int maxClients;
	static int idCounter;
private:
	std::vector<ConnectedClient*> connectedClients;
	std::vector<CPacket*> clientPackets;
	CPacket clientPacket;
	CPacket serverPacket;
	NetworkMessageType nmType;
};

#endif
