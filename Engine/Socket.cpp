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

int Socket::Send(CPacket& packet, sockaddr_in& to)
{
	int totalBytes = packet.PacketSize();
	char buf = packet.buffer[0];
	int bytesSent = sendto(sock, (const char*)&packet.buffer[0], MAX_PACKET_SIZE, 0, (sockaddr*)&to, sizeof(to));
	if (bytesSent == INVALID_SOCKET)
	{
		//вывести ошибку об отправке данных
		return WSAGetLastError();
	}
	return bytesSent;
}

int Socket::Receive(CPacket& packet, sockaddr_in& from)
{
	int fromLen = sizeof(from);
	ZeroMemory(&from, fromLen);
	packet.buffer.resize(MAX_PACKET_SIZE);
	int bytesReceived = recvfrom(sock, (char*)&packet.buffer[0], MAX_PACKET_SIZE, 0, (sockaddr*)&from, &fromLen);
	if (bytesReceived == SOCKET_ERROR)
	{
		//вывести сообщение об ошибке
		return WSAGetLastError();
	}
	return bytesReceived;
}

Socket::~Socket()
{
	CloseSocket();
}
