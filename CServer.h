#pragma once
#include <ostream>
#include "BinaryReader.h"
#include "BinaryWriter.h"

enum EClientType
{
	k_EClientTypeUnknown = 0,
	k_EClientTypeLoader,
	k_EClientTypeInjector,
	k_EClientTypeHack,
};

enum EGameMessages
{
	k_EGameMessagesInvalid = 0,
	k_EGameMessagesHello = 2000,
	k_EGameMessagesReportBotRequest = 2010,
	k_EGameMessagesReport = 2011,
	k_EGameMessagesReportBotResponse = 2012,
	k_EGameMessagesReportBotConfirm = 2013,
	k_EGameMessagesNotify = 2020,
};

class CServer
{
	SOCKET m_Socket = 0;
	bool m_bConnected = false;
	bool m_bReportBotting = false;

public:
	CServer() {};
	
	bool Connect()
	{
		//Start up Winsock…
		WSADATA wsadata;

		int error = WSAStartup(0x0202, &wsadata);

		//Did something happen?
		if (error)
		{
			DEVMSG("scerror1");
			return false;
		}

		//Did we get the right Winsock version?
		if (wsadata.wVersion != 0x0202)
		{
			DEVMSG("scerror2");
			WSACleanup(); //Clean up Winsock
			return false;
		}

		//Fill out the information needed to initialize a socket…
		SOCKADDR_IN target; //Socket address information
		target.sin_family = AF_INET; // address family Internet
		target.sin_port = htons(54002); //Port to connect on
#ifdef HACK_LOCAL_SERVER
		target.sin_addr.s_addr = inet_addr("127.0.0.1");
#else
		target.sin_addr.s_addr = inet_addr("195.88.208.158");
#endif

		m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
		if (m_Socket == INVALID_SOCKET)
		{
			DEVMSG("scerror3");
			Sequrity::ExitGame();
			return false; //Couldn't create the socket
		}

		//Try to connect...
		if (connect(m_Socket, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
		{
			DEVMSG("scerror4");
			Sequrity::ExitGame();
			return false; //Couldn't connect
		}
		else
		{
			unsigned long ul = 1;
			int nRet = ioctlsocket(m_Socket, FIONBIO, (unsigned long *)&ul);
			m_bConnected = true;
			return true; //Success
		}
	}

	void sendMessage(BinaryWriter msg)
	{
		send(m_Socket, msg.Bytes(), (int)msg.Size(), 0);
	}

	/*void HandleReportMessage(BinaryReader br)
	{
		auto account_id = br.ReadUInt32();
		auto match_id = br.ReadUInt64();

		m_bReportBotting = true;
		Protobuf::SendClientReport(account_id, match_id);
		MakeNotify("ReportBot: You are using for reporting " + to_string(account_id) + "...");
	}
*/
	void HandleReportBotConfirmMessage(BinaryReader br)
	{
		auto client_id = br.ReadInt32();
		auto confirmation_id = br.ReadUInt64();

		MakeNotify("ReportBot: Client #" + to_string(client_id) +  ": " + to_string(confirmation_id) + "!");
	}

	void HandleNotifyMessage(BinaryReader br)
	{
		string message = br.ReadString();
		MakeNotify(message);
	}

	//void HandleMessage(BYTE* BYTEs, int len)
	//{
	//	BinaryReader br = BinaryReader(BYTEs);
	//	auto packetID = br.ReadUInt16();
	//	switch (packetID)
	//	{
	//	case EGameMessages::k_EGameMessagesReport:
	//		HandleReportMessage(br);
	//		break;
	//	case EGameMessages::k_EGameMessagesReportBotConfirm:
	//		HandleReportBotConfirmMessage(br); // TODO: Notify message 
	//		break;
	//	case EGameMessages::k_EGameMessagesNotify:
	//		HandleNotifyMessage(br);
	//		break;
	//	default:
	//		DEVMSG("UNKOWN MESSAGE %d CAME FROM SERVER!", packetID);
	//		break;
	//	}
	//}

	//void ReceiveMessage()
	//{
	//	if (m_bConnected)
	//	{
	//		char buffer[256] = { 0 };
	//		int r = recv(m_Socket, buffer, 256, 0);
	//		if (r != -1)
	//		{
	//			HandleMessage((unsigned char*)buffer, r);
	//		}
	//		else //server down
	//		{
	//			if (WSAGetLastError() == WSAECONNRESET)
	//				Sequrity::ExitGame();
	//		}
	//	}
	//}

	/*void SendHelloMessage()
	{
		ConVar* pNameCvar = g_pCvar->FindVar("name");
		char szSteamID[128]; GetEnvironmentVariable("STEAMID", szSteamID, 128);
		string szHackVersion = HACK_VERSION;
		
		BinaryWriter msg;
		msg.WriteUInt16(EGameMessages::k_EGameMessagesHello);
		msg.WriteString(szHackVersion);
		msg.WriteString(pNameCvar->strString);
		msg.WriteString(szSteamID);
		sendMessage(msg);
	}

	void SendRequestReportBotMessage(uint32_t account_id, uint64_t match_id)
	{
		BinaryWriter msg;
		msg.WriteUInt16(EGameMessages::k_EGameMessagesReportBotRequest);
		msg.WriteUInt32(account_id);
		msg.WriteUInt64(match_id);
		sendMessage(msg);
	}

	void SendResponseReportBotMessage(uint32_t account_id, uint64_t confirmation_id)
	{
		m_bReportBotting = false;

		BinaryWriter msg;
		msg.WriteUInt16(EGameMessages::k_EGameMessagesReportBotResponse);
		msg.WriteUInt32(account_id);
		msg.WriteUInt64(confirmation_id);
		sendMessage(msg);
	}

	bool Connected() { return m_bConnected; };
	bool ReportBotting() { return m_bReportBotting; };*/
};

CServer* g_pServer = NULL;