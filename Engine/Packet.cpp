#include "Packet.h"

uint32_t idMessage = 3860254197;

CPacket::CPacket()
{
	extractionOffset = 0;
	buffer.reserve(MAX_PACKET_SIZE);
}

CPacket::~CPacket()
{
	Clear();
}

void CPacket::Append(const void* data, uint32_t size)
{
	if (buffer.size() + size <= MAX_PACKET_SIZE)
		buffer.insert(buffer.end(), (char*)data, (char*)data + size);
	else
		throw Exception("[CPacket::Append(void*, uint32_t)]: maximum size of packet is " + std::to_string(MAX_PACKET_SIZE) + " bytes!(your packet size is " + std::to_string(buffer.size() + size) + " bytes)");
}

char* CPacket::GetData()
{
	return buffer.data();
}

void CPacket::Reserve(int newSize)
{
	buffer.resize(newSize);
}

void CPacket::Clear()
{
	extractionOffset = 0;
	buffer.clear();
}

int CPacket::PacketSize()
{
	return (int)buffer.size();
}

CPacket& CPacket::operator=(CPacket& other)
{
	extractionOffset = other.extractionOffset;
	buffer = other.buffer;
	return *this;
}

bool CPacket::operator==(CPacket& other)
{
	return extractionOffset == other.extractionOffset && buffer == other.buffer;
}

bool CPacket::operator!=(CPacket& other)
{
	return !((*this)==other);
}

CPacket& CPacket::operator<<(const std::string& data)
{
	*this << (uint32_t)data.size();
	Append(data.data(), (uint32_t)data.size());
	return *this;
}

CPacket& CPacket::operator>>(std::string& data)
{
	uint32_t stringSize;
	*this >> stringSize;
	data.resize(stringSize);
	data.assign(&buffer[extractionOffset], stringSize);
	return *this;
}

