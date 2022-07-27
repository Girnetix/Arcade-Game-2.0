#include "Socket.h"

bool Socket::Create()
{
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET)
	{
		//вывести информацию об ошибке
		CloseSocket();
		pNetwork->Shutdown();
		return false;
	}
	return true;
}

bool Socket::Bind(sockaddr_in& info)
{
	if (bind(sock, (sockaddr*)&info, sizeof(info)) != 0)
	{
		//вывести информацию об ошибке
		CloseSocket();
		pNetwork->Shutdown();
		return false;
	}
	return true;
}

bool Socket::SetNonBlock()
{
	DWORD nonBlock = 1;
	if (ioctlsocket(sock, FIONBIO, &nonBlock) != 0)
	{
		CloseSocket();
		pNetwork->Shutdown();
		return false;
	}
	return true;
}

bool Socket::CloseSocket()
{
	return closesocket(sock);
}

void Socket::Send(CPacket& packet, sockaddr_in& to)
{
	int totalBytes = packet.PacketSize();
	int bytesSent = sendto(sock, packet.GetData(), totalBytes, 0, (sockaddr*)&to, sizeof(to));
	if (bytesSent == INVALID_SOCKET)
	{
		//вывести ошибку об отправке данных
	}
}

void Socket::Receive(CPacket& packet, sockaddr_in& from)
{
	int fromLen = sizeof(from);
	int bytesReceived = recvfrom(sock, packet.GetData(), MAX_PACKET_SIZE, 0, (sockaddr*)&from, &fromLen);
	if (bytesReceived == INVALID_SOCKET)
	{
		//вывести ошибку об отправке данных
	}
}

Socket::~Socket()
{
	CloseSocket();
}
