#include "Packet.h"

uint32_t idMessage = 3860254197;

CPacket::CPacket()
{
	extarctionOffset = 0;
	buffer.reserve(MAX_PACKET_SIZE);
	clientSendingTime = serverReceivingTime = serverSendingTime = clientReceivingTime = pTimer->GetHighPrecisionTime();
	/**this << idMessage;*/
	/**this << nmType;
	*this << clientSendingTime << serverReceivingTime << serverSendingTime << clientReceivingTime;*/
}

CPacket::~CPacket()
{
	Clear();
}

void CPacket::Append(void* data, uint32_t size)
{
	buffer.insert(buffer.end(), (char*)data, (char*)data + size);
}

char* CPacket::GetData()
{
	return buffer.data();
}

void CPacket::Clear()
{
	extarctionOffset = 0;
	buffer.clear();
	buffer.reserve(MAX_PACKET_SIZE);
}

int CPacket::PacketSize()
{
	return buffer.size();
}

CPacket& CPacket::operator=(CPacket& other)
{
	extarctionOffset = other.extarctionOffset;
	buffer = other.buffer;
	clientSendingTime = other.clientSendingTime;
	serverReceivingTime = other.serverReceivingTime;
	serverSendingTime = other.serverSendingTime;
	clientReceivingTime = other.clientReceivingTime;
	return *this;
}

bool CPacket::operator==(CPacket& other)
{
	if (extarctionOffset == other.extarctionOffset
		&& buffer == other.buffer
		&& clientSendingTime == other.clientSendingTime
		&& serverReceivingTime == other.serverReceivingTime
		&& serverSendingTime == other.serverSendingTime
		&& clientReceivingTime == other.clientReceivingTime)
		return true;
	else return false;
}
