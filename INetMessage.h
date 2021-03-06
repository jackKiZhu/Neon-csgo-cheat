#pragma once
#include <Windows.h>

class bf_read;
class bf_write;
class INetMessage
{
public:
	virtual	~INetMessage() {};

	virtual void SetNetChannel(void* netchan) = 0;
	virtual void SetReliable(bool state) = 0;

	virtual bool Process(void) = 0;

	virtual	bool ReadFromBuffer(bf_read &buffer) = 0;
	virtual	bool WriteToBuffer(bf_write &buffer) = 0;

	virtual bool IsReliable(void) const = 0;

	virtual int GetType(void) const = 0;
	virtual int GetGroup(void) const = 0;
	virtual const char *GetName(void) const = 0;
	virtual void *GetNetChannel(void) const = 0;
	virtual const char *ToString(void) const = 0;
};

class cnetmsg_clientinfo {
private:
	char __PAD0[0x8];
public:
	uint32_t send_table_crc;
	uint32_t server_count;
	bool is_hltv;
	bool is_replay;
	uint32_t friends_id;
};

template<typename T>
class CNetMessagePB : public INetMessage, public T {};
using cclcmsg_clientinfo_t = CNetMessagePB<cnetmsg_clientinfo>;