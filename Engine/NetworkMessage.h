#pragma once
#ifndef NET_MSG_H
#define NET_MSG_H

enum NetworkMessageType : uint8_t
{
	BroadcastRequest,
	BroadcastResponse,
	ConnectingRequest,
	ConnectingResponse,
	Connected,
	Disconnecting
};

#endif
