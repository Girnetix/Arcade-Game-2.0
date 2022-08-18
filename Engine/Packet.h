#pragma once
#ifndef PACKET_H
#define PACKET_H

#include "Rendering.h"
#include "Timer.h"
#include "NetworkMessage.h"

#define MAX_PACKET_SIZE 2048

extern uint32_t idMessage;

class CPacket
{
public:
	CPacket();
	~CPacket();
private:
	void Append(void* data, uint32_t size);

	template<typename Type>
	void Get(Type& data);
public:
	void Clear();
	int PacketSize();
	char* GetData();

	template<typename Type>
	CPacket& operator<<(Type& data);

	template<typename Type>
	CPacket& operator>>(Type& data);

	CPacket& operator=(CPacket& other);
	bool operator==(CPacket& other);
private:
	int extarctionOffset;
public:
	//������ ��� �������� ��������(����)
	CTimerValue clientSendingTime;
	CTimerValue serverReceivingTime;
	CTimerValue serverSendingTime;
	CTimerValue clientReceivingTime;
	
	std::vector<char> buffer;
};

template<typename Type>
inline void CPacket::Get(Type& data)
{
	data = *reinterpret_cast<Type*>(&buffer[extarctionOffset]);
	extarctionOffset += sizeof(Type);
}

template<typename Type>
inline CPacket& CPacket::operator<<(Type& data)
{
	Append(&data, sizeof(data));
	return *this;
}

template<typename Type>
inline CPacket& CPacket::operator>>(Type& data)
{
	Get(data);
	return *this;
}


#endif
