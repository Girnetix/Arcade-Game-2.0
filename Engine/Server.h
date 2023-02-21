#pragma once
#ifndef SERVER_H
#define SERVER_H

#include "Network.h"

#define MAX_CLIENTS 16

extern const double TimeoutConnection;
extern const double TroubleTimeout;

class CServer
{
private:
	class ConnectedClient
	{
	public:
		std::string ipAdress;
		int iPort;
		int id;
		sockaddr_in info;
		CTimerValue tmLastReceivedMessage;
	};
public:
	void Init(std::string ipAdress, uint32_t iPort, int maxClients = 8);
	void Start();
	void Stop();
	void SendMsg(CPacket &packet);
	void ReceiveMsg(CPacket& packet);
	void ProcessMsg(CPacket& packet, sockaddr_in& clientInfo);
	void Update();
	int GetPing();
	bool IsServer();
private:
	Socket sock;
	bool serverIsActive, serverInitialized;
	std::string ipAdress;
	int iPort;
	int maxClients;
	static int idCounter;
private:
	std::vector<sockaddr_in> connectedClients;
	std::vector<CPacket> clientPackets;
	CPacket serverPacket;
	NetworkMessageType nmType;
};

#endif
