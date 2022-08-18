#pragma once
#ifndef SOCKET_H
#define SOCKET_H
 
#include "Network.h"
#include "Packet.h"

class Socket
{
public:
	bool Create();
	bool Bind(sockaddr_in &info);
	bool SetNonBlock();
	bool CloseSocket();
	int Send(CPacket &packet, sockaddr_in &to);
	int Receive(CPacket& packet, sockaddr_in& from);
	~Socket();
private:
	SOCKET sock;
};


#endif
