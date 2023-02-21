#include "Server.h"
#include <iostream>

/*            Сервер
	- запуск сервера по указанному адресу и порту
	- остановка сервера
	- принудительное отключение клиентов (блокировка, исключение из игры и т.д.)
	- защита сервера паролем
*/

const double TimeoutConnection = 30.0;
const double TroubleTimeout = 5.0;

int CServer::idCounter = 0;

void CServer::Init(std::string ipAdress, uint32_t iPort, int maxClients)
{
	serverIsActive = false;
	if (maxClients <= MAX_CLIENTS && maxClients > 0)
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

void CServer::SendMsg(CPacket& packet)
{
	for (auto& client : connectedClients)
		sock.Send(packet, client);
}

void CServer::ReceiveMsg(CPacket& packet)
{
	//CPacket packet;
	sockaddr_in clientInfo;
	int result = sock.Receive(packet, clientInfo);
	if (result == WSAGetLastError())
		return;
	ProcessMsg(packet, clientInfo);
	//while (sock.Receive(packet, clientInfo) != WSAEWOULDBLOCK)
	//	clientPackets.emplace_back(packet);
}

void CServer::ProcessMsg(CPacket& packet, sockaddr_in& clientInfo)
{
	packet >> nmType;
	/**/
	switch (nmType)
	{
	case BroadcastRequest:
		break;
	case BroadcastResponse:
		break;
	case ConnectingRequest:
		connectedClients.push_back(clientInfo);
		std::cout << "Accepted new connection!" << std::endl;
		break;
	case ConnectingResponse:
		break;
	case Connected:
		break;
	case Disconnecting:
		break;
	default:
		break;
	}
}

void CServer::Update()
{
	if (!serverIsActive) return;

	//ReceiveMsg();



	SendMsg(serverPacket);
}

int CServer::GetPing()
{
	return 0;
}

bool CServer::IsServer()
{
	return serverIsActive;
}

