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

	nmType = NetworkMessageType::ConnectingRequest;
	clientPacket << nmType;

	int bytesSent = sock.Send(clientPacket, serverInfo);

	/*clientPacket.clientReceivingTime = pTimer->GetHighPrecisionTime();


	clientPacket >> clientPacket.serverReceivingTime
				 >> clientPacket.serverSendingTime
				 >> clientPacket.clientSendingTime;

	int systemPing = (clientPacket.clientReceivingTime - clientPacket.clientSendingTime).GetMilliseconds();
	int ping = ((clientPacket.clientReceivingTime - clientPacket.clientSendingTime) - (clientPacket.serverSendingTime - clientPacket.serverReceivingTime)).GetMilliseconds();*/

}

void CClient::Stop()
{

}

int CClient::Send(CPacket& packet)
{
	return sock.Send(packet, serverInfo);
}

int CClient::Receive(CPacket& packet)
{
	return sock.Receive(packet, serverInfo);
}

void CClient::Update()
{

}

int CClient::GetPing()
{
	return 0;
}
