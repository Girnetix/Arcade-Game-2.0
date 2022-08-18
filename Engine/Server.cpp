#include "Server.h"

const double TimeoutConnection = 30.0;
int CServer::idCounter = 0;

void CServer::Init(std::string ipAdress, uint32_t iPort, int maxClients)
{
	serverIsActive = false;
	if(maxClients<= MAX_CLIENTS)
		this->maxClients = maxClients;
	else
		this->maxClients = MAX_CLIENTS;

	sock.Create();

	sockaddr_in info;
	inet_pton(AF_INET, ipAdress.c_str(), &info.sin_addr);
	info.sin_family = AF_INET;
	info.sin_port = htons(iPort);

	sock.Bind(info);
	//sock.SetNonBlock();

	serverInitialized = true;
}

void CServer::Start()
{
	if (serverInitialized)
		serverIsActive = true;
	else
		return;
}

void CServer::Stop()
{

}

void CServer::Send(CPacket& packet)
{
	
	//sock.Send(packet);
}

void CServer::Receive(CPacket& packet)
{
	//sock.Receive(packet);
}

void CServer::Update()
{
	if (serverIsActive)
	{
		clientPackets.clear();
		if (connectedClients.size() != 0)
		{

		}
		sockaddr_in clientInfo;
		int bytesReceived = sock.Receive(clientPacket, clientInfo);
		serverPacket.serverReceivingTime = pTimer->GetHighPrecisionTime();
		uint32_t testIDMessage;
		clientPacket >> testIDMessage;
		if (testIDMessage == idMessage)
			clientPackets.push_back(&clientPacket);
		else
			return;
		clientPacket >> nmType;
		clientPacket >> clientPacket.clientSendingTime;

		Point p(12, 8, 32);

		serverPacket.serverSendingTime = pTimer->GetHighPrecisionTime();
		serverPacket << serverPacket.serverReceivingTime << serverPacket.serverSendingTime;
		serverPacket << clientPacket.clientSendingTime << p;

		int bytesSent = sock.Send(serverPacket, clientInfo);

		switch (nmType)
		{
		case Connecting:
			break;
		case Connected:
			break;
		case Disconnecting:
			break;
		case Broadcast:
			break;
		}
	}
}

int CServer::GetPing()
{
	return 0;
}
