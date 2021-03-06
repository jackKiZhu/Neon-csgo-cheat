//#pragma once
//#include "Protobuf\protobufs\cstrike15_usermessages.pb.h"
//#include "Protobuf\protobufs\cstrike15_gcmessages.pb.h"
//#include "Protobuf\protobufs\gcsystemmsgs.pb.h"
//#include "Protobuf\protobufs\gcsdk_gcmessages.pb.h"
//#include "Protobuf\protobufs\econ_gcmessages.pb.h"
//#include "Protobuf\protobufs\base_gcmessages.pb.h"
//
//#ifdef _DEBUG
//#pragma comment(lib, "libprotobuf_debug.lib")
//#else
//#pragma comment(lib, "libprotobuf_release.lib")
//#endif
//
//namespace Protobuf
//{
//	bool SendClientHello()
//	{
//		CMsgClientHello Message;
//		Message.set_client_session_need(1);
//		Message.clear_socache_have_versions();
//
//		void* ptr = malloc(Message.ByteSize() + 8);
//		if (!ptr)
//			return false;
//
//		auto unMsgType = k_EMsgGCClientHello | ((DWORD)1 << 31);
//		((uint32_t*)ptr)[0] = unMsgType;
//		((uint32_t*)ptr)[1] = 0;
//		Message.SerializeToArray((void*)((DWORD)ptr + 8), Message.ByteSize());
//
//		bool result = g_pSteamGameCoordinator->sendMessage(unMsgType, ptr, Message.ByteSize() + 8) == k_EGCResultOK;
//		free(ptr);
//		return result;
//	}
//
//	bool SendClientReport(uint32_t account_id, uint64_t match_id)
//	{
//		CMsgGCCStrike15_v2_ClientReportPlayer Message;
//		Message.set_account_id(account_id);
//		Message.set_match_id(match_id);
//		Message.set_rpt_aimbot(1);
//		Message.set_rpt_speedhack(1);
//		Message.set_rpt_teamharm(1);
//		Message.set_rpt_textabuse(1);
//		Message.set_rpt_voiceabuse(1);
//		Message.set_rpt_wallhack(1);
//
//		void* ptr = malloc(Message.ByteSize() + 8);
//		if (!ptr)
//			return false;
//
//		auto unMsgType = k_EMsgGCCStrike15_v2_ClientReportPlayer | ((DWORD)1 << 31);
//		((uint32_t*)ptr)[0] = unMsgType;
//		((uint32_t*)ptr)[1] = 0;
//		Message.SerializeToArray((void*)((DWORD)ptr + 8), Message.ByteSize());
//
//		bool result = g_pSteamGameCoordinator->sendMessage(unMsgType, ptr, Message.ByteSize() + 8) == k_EGCResultOK;
//		free(ptr);
//		return result;
//	}
//
//	bool SendMatchmakingHello()
//	{
//		CMsgGCCStrike15_v2_MatchmakingClient2GCHello Message;
//
//		void* ptr = malloc(Message.ByteSize() + 8);
//		if (!ptr)
//			return false;
//
//		auto unMsgType = k_EMsgGCCStrike15_v2_MatchmakingClient2GCHello | ((DWORD)1 << 31);
//		((uint32_t*)ptr)[0] = unMsgType;
//		((uint32_t*)ptr)[1] = 0;
//		Message.SerializeToArray((void*)((DWORD)ptr + 8), Message.ByteSize());
//
//		bool result = g_pSteamGameCoordinator->sendMessage(unMsgType, ptr, Message.ByteSize() + 8) == k_EGCResultOK;
//		free(ptr);
//		return result;
//	}
//}
