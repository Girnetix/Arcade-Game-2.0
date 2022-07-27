#include "Packet.h"

CPacket::CPacket()
{
	extarctionOffset = 0;
	buffer.reserve(MAX_PACKET_SIZE);
	clientSendingTime = serverReceivingTime = serverSendingTime = clientReceivingTime = pTimer->GetHighPrecisionTime();
	*this << clientSendingTime << serverReceivingTime << serverSendingTime << clientReceivingTime;
}

CPacket::~CPacket()
{
	Clear();
}

void CPacket::Append(void* data, uint32_t size)
{
	if ((buffer.size() + size) > MAX_PACKET_SIZE)
	{
		//вывести сообщение о том, что превышен размер пакета
		//оставить часть данных в очереди и отправить отдельным пакетом
		return;
	}
	buffer.insert(buffer.end(), (char*)data, (char*)data + size);
}

char* CPacket::GetData()
{
	return buffer.data();
}

void CPacket::Clear()
{
	extarctionOffset = 0;
	buffer.reserve(MAX_PACKET_SIZE);
}

int CPacket::PacketSize()
{
	return buffer.size();
}

CPacket& CPacket::operator=(CPacket& other)
{
	return *this;
}

bool CPacket::operator==(CPacket& other)
{
	return false;
}
