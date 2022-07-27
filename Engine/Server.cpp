#include "Server.h"

int CServer::idCounter = 0;

void CServer::Init(std::wstring ipAdress, uint32_t iPort, int maxClients)
{
	serverIsActive = false;
	if(maxClients<= MAX_CLIENTS)
		this->maxClients = maxClients;
	else
		this->maxClients = MAX_CLIENTS;

	sockaddr_in info;
	inet_pton(AF_INET, (const char*)ipAdress.c_str(), &info.sin_addr);
	info.sin_family = AF_INET;
	info.sin_port = htons(iPort);

	sock.Bind(info);
	sock.SetNonBlock();
}

void CServer::Start()
{
	serverIsActive = true;
}

void CServer::Stop()
{

}

void CServer::Send(CPacket& packet, int iClient)
{
	
	//sock.Send(packet);
}

void CServer::Receive(CPacket& packet, int iClient)
{
	//sock.Receive(packet);
}

void CServer::Update()
{

}

int CServer::GetPing()
{
	return 0;
}
