#pragma once
#ifndef PACKET_H
#define PACKET_H

#include "Rendering.h"
#include "Timer.h"

#define MAX_PACKET_SIZE 2048

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
	std::vector<char> buffer;
public:
	//данные для подсчёта задержки(пинг)
	CTimerValue clientSendingTime;
	CTimerValue serverReceivingTime;
	CTimerValue serverSendingTime;
	CTimerValue clientReceivingTime;
	
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
