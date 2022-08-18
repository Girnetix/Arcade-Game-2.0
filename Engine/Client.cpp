#include "Client.h"

void CClient::Init()
{
	sock.Create();
	//sock.SetNonBlock();
}

void CClient::Start()
{

}

void CClient::Connect(std::string ipAdress, int iPort)
{
	serverInfo.sin_family = AF_INET;
	inet_pton(AF_INET, ipAdress.c_str(), &serverInfo.sin_addr);
	serverInfo.sin_port = htons(iPort);

	clientPacket << idMessage;
	nmType = NetworkMessageType::Connecting;
	clientPacket << nmType;

	clientPacket.clientSendingTime = pTimer->GetHighPrecisionTime();

	clientPacket << clientPacket.clientSendingTime;

	int bytesSent = sock.Send(clientPacket, serverInfo);

	int bytesReceived = sock.Receive(clientPacket, serverInfo);

	clientPacket.clientReceivingTime = pTimer->GetHighPrecisionTime();

	Point p(0, 0, 0);

	clientPacket >> clientPacket.serverReceivingTime
				 >> clientPacket.serverSendingTime
				 >> clientPacket.clientSendingTime
				 >> p;

	int systemPing = (clientPacket.clientReceivingTime - clientPacket.clientSendingTime).GetMilliseconds();
	int ping = ((clientPacket.clientReceivingTime - clientPacket.clientSendingTime) - (clientPacket.serverSendingTime - clientPacket.serverReceivingTime)).GetMilliseconds();

}

void CClient::Stop()
{

}

void CClient::Send()
{

}

void CClient::Receive()
{

}

void CClient::Update()
{

}

int CClient::GetPing()
{
	return 0;
}
