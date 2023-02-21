#pragma once
#ifndef PACKET_H
#define PACKET_H

#include "Rendering.h"
#include "Timer.h"
#include "NetworkMessage.h"
#include "Exception.h"

#define MAX_PACKET_SIZE 2048

extern uint32_t idMessage;

class CPacket
{
public:
	CPacket();
	~CPacket();
private:
	void Append(const void* data, uint32_t size);

	template<typename Type>
	void Get(Type& data);
public:
	void Reserve(int newSize);
	void Clear();
	int PacketSize();
	char* GetData();

	template<typename Type>
	CPacket& operator<<(const Type& data);

	template<typename Type>
	CPacket& operator>>(Type& data);

	CPacket& operator<<(const std::string& data);
	CPacket& operator>>(std::string& data);

	CPacket& operator=(CPacket& other);
	bool operator==(CPacket& other);
	bool operator!=(CPacket& other);
private:
	int extractionOffset;
	std::vector<char> buffer;
};

template<typename Type>
inline void CPacket::Get(Type& data)
{
	if (extractionOffset + sizeof(Type) <= buffer.size())
	{
		data = *reinterpret_cast<Type*>(&buffer[extractionOffset]);
		extractionOffset += sizeof(Type);
	}
	else
		throw Exception("[CPacket::Get(Type&)]: Extraction offset reached max packet size of " + std::to_string(buffer.size()) + " bytes!");
}

template<typename Type>
inline CPacket& CPacket::operator<<(const Type& data)
{
	try
	{
		Append(&data, sizeof(data));
	}
	catch (Exception& exception)
	{
		exception.what();
	}
	
	return *this;
}

template<typename Type>
inline CPacket& CPacket::operator>>(Type& data)
{
	try
	{
		Get(data);
	}
	catch (Exception& exception)
	{
		exception.what();
	}
	
	return *this;
}

#endif
