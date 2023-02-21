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
	int bufferSize = packet.PacketSize();
	int bytesSent = sendto(sock, (const char*)&bufferSize, sizeof(int), 0, (sockaddr*)&to, sizeof(to));
	bytesSent = sendto(sock, (const char*)packet.GetData(), packet.PacketSize(), 0, (sockaddr*)&to, sizeof(to));
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
	int bufferSize;
	int bytesReceived = recvfrom(sock, (char*)&bufferSize, sizeof(int), 0, (sockaddr*)&from, &fromLen);
	if (bytesReceived == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
			return WSAEWOULDBLOCK;

		//вывести сообщение об ошибке
		return WSAGetLastError();
	}
	packet.Reserve(bufferSize);
	bytesReceived = recvfrom(sock, packet.GetData(), bufferSize, 0, (sockaddr*)&from, &fromLen);
	if (bytesReceived == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
			return WSAEWOULDBLOCK;

		//вывести сообщение об ошибке
		return WSAGetLastError();
	}
	return bytesReceived;
}

Socket::~Socket()
{
	CloseSocket();
}
