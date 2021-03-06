#pragma once

class ISteamGameServer;
class ISteamFriends;
class ISteamUtils;
class ISteamMatchmaking;
class ISteamContentServer;
class ISteamMatchmakingServers;
class ISteamUserStats;
class ISteamApps;
class ISteamNetworking;
class ISteamRemoteStorage;
class ISteamScreenshots;
class ISteamMusic;
class ISteamMusicRemote;
class ISteamGameServerStats;
class ISteamHTTP;
class ISteamUnifiedMessages;
class ISteamController;
class ISteamUGC;
class ISteamAppList;
class ISteamHTMLSurface;
class ISteamInventory;
class ISteamVideo;
typedef INT32 HSteamPipe;
typedef INT32 HSteamUser;
#include "CSteamID.h"
typedef uint32_t AppId_t;
typedef uint64_t SteamAPICall_t;

enum ELobbyType
{
	k_ELobbyTypePrivate = 0,		// only way to join the lobby is to invite to someone else
	k_ELobbyTypeFriendsOnly = 1,	// shows for friends or invitees, but not in lobby list
	k_ELobbyTypePublic = 2,			// visible for friends and in lobby list
	k_ELobbyTypeInvisible = 3,		// returned by search, but not visible to other friends 
									//    useful if you want a user in two lobbies, for example matching groups together
									//	  a user can be in only one regular lobby, and up to two invisible lobbies
};

enum ELobbyComparison
{
	k_ELobbyComparisonEqualToOrLessThan = -2,
	k_ELobbyComparisonLessThan = -1,
	k_ELobbyComparisonEqual = 0,
	k_ELobbyComparisonGreaterThan = 1,
	k_ELobbyComparisonEqualToOrGreaterThan = 2,
	k_ELobbyComparisonNotEqual = 3,
};

enum ELobbyDistanceFilter
{
	k_ELobbyDistanceFilterClose,		// only lobbies in the same immediate region will be returned
	k_ELobbyDistanceFilterDefault,		// only lobbies in the same region or near by regions
	k_ELobbyDistanceFilterFar,			// for games that don't have many latency requirements, will return lobbies about half-way around the globe
	k_ELobbyDistanceFilterWorldwide,	// no filtering, will match lobbies as far as India to NY (not recommended, expect multiple seconds of latency between the clients)
};

class ISteamMatchmaking
{
public:
	// SendLobbyChatMsg (26)


	/*
	// game server favorites storage
	// saves basic details about a multiplayer game server locally

	// returns the number of favorites servers the user has stored
	virtual int GetFavoriteGameCount() = 0;

	// returns the details of the game server
	// iGame is of range [0,GetFavoriteGameCount())
	// *pnIP, *pnConnPort are filled in the with IP:port of the game server
	// *punFlags specify whether the game server was stored as an explicit favorite or in the history of connections
	// *pRTime32LastPlayedOnServer is filled in the with the Unix time the favorite was added
	virtual bool GetFavoriteGame(int iGame, AppId_t *pnAppID, uint32_t *pnIP, uint16_t *pnConnPort, uint16_t *pnQueryPort, uint32_t *punFlags, uint32_t *pRTime32LastPlayedOnServer) = 0;

	// adds the game server to the local list; updates the time played of the server if it already exists in the list
	virtual int AddFavoriteGame(AppId_t nAppID, uint32_t nIP, uint16_t nConnPort, uint16_t nQueryPort, uint32_t unFlags, uint32_t rTime32LastPlayedOnServer) = 0;

	// removes the game server from the local storage; returns true if one was removed
	virtual bool RemoveFavoriteGame(AppId_t nAppID, uint32_t nIP, uint16_t nConnPort, uint16_t nQueryPort, uint32_t unFlags) = 0;

	///////
	// Game lobby functions

	// Get a list of relevant lobbies
	// this is an asynchronous request
	// results will be returned by LobbyMatchList_t callback & call result, with the number of lobbies found
	// this will never return lobbies that are full
	// to add more filter, the filter calls below need to be call before each and every RequestLobbyList() call
	// use the CCallResult<> object in steam_api.h to match the SteamAPICall_t call result to a function in an object, e.g.

	//
	//CALL_RESULT(LobbyMatchList_t)
	virtual SteamAPICall_t RequestLobbyList() = 0;
	// filters for lobbies
	// this needs to be called before RequestLobbyList() to take effect
	// these are cleared on each call to RequestLobbyList()
	virtual void AddRequestLobbyListStringFilter(const char *pchKeyToMatch, const char *pchValueToMatch, ELobbyComparison eComparisonType) = 0;
	// numerical comparison
	virtual void AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType) = 0;
	// returns results closest to the specified value. Multiple near filters can be added, with early filters taking precedence
	virtual void AddRequestLobbyListNearValueFilter(const char *pchKeyToMatch, int nValueToBeCloseTo) = 0;
	// returns only lobbies with the specified number of slots available
	virtual void AddRequestLobbyListFilterSlotsAvailable(int nSlotsAvailable) = 0;
	// sets the distance for which we should search for lobbies (based on users IP address to location map on the Steam backed)
	virtual void AddRequestLobbyListDistanceFilter(ELobbyDistanceFilter eLobbyDistanceFilter) = 0;
	// sets how many results to return, the lower the count the faster it is to download the lobby results & details to the client
	virtual void AddRequestLobbyListResultCountFilter(int cMaxResults) = 0;

	virtual void AddRequestLobbyListCompatibleMembersFilter(CSteamID steamIDLobby) = 0;

	// returns the CSteamID of a lobby, as retrieved by a RequestLobbyList call
	// should only be called after a LobbyMatchList_t callback is received
	// iLobby is of the range [0, LobbyMatchList_t::m_nLobbiesMatching)
	// the returned CSteamID::IsValid() will be false if iLobby is out of range
	virtual CSteamID GetLobbyByIndex(int iLobby) = 0;

	// Create a lobby on the Steam servers.
	// If private, then the lobby will not be returned by any RequestLobbyList() call; the CSteamID
	// of the lobby will need to be communicated via game channels or via InviteUserToLobby()
	// this is an asynchronous request
	// results will be returned by LobbyCreated_t callback and call result; lobby is joined & ready to use at this point
	// a LobbyEnter_t callback will also be received (since the local user is joining their own lobby)
	//CALL_RESULT(LobbyCreated_t)
	virtual SteamAPICall_t CreateLobby(ELobbyType eLobbyType, int cMaxMembers) = 0;

	// Joins an existing lobby
	// this is an asynchronous request
	// results will be returned by LobbyEnter_t callback & call result, check m_EChatRoomEnterResponse to see if was successful
	// lobby metadata is available to use immediately on this call completing
	//CALL_RESULT(LobbyEnter_t)
	virtual SteamAPICall_t JoinLobby(CSteamID steamIDLobby) = 0;

	// Leave a lobby; this will take effect immediately on the client side
	// other users in the lobby will be notified by a LobbyChatUpdate_t callback
	virtual void LeaveLobby(CSteamID steamIDLobby) = 0;

	// Invite another user to the lobby
	// the target user will receive a LobbyInvite_t callback
	// will return true if the invite is successfully sent, whether or not the target responds
	// returns false if the local user is not connected to the Steam servers
	// if the other user clicks the join link, a GameLobbyJoinRequested_t will be posted if the user is in-game,
	// or if the game isn't running yet the game will be launched with the parameter +connect_lobby <64-bit lobby id>
	virtual bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee) = 0;

	// Lobby iteration, for viewing details of users in a lobby
	// only accessible if the lobby user is a member of the specified lobby
	// persona information for other lobby members (name, avatar, etc.) will be asynchronously received
	// and accessible via ISteamFriends interface

	// returns the number of users in the specified lobby
	virtual int GetNumLobbyMembers(CSteamID steamIDLobby) = 0;
	// returns the CSteamID of a user in the lobby
	// iMember is of range [0,GetNumLobbyMembers())
	// note that the current user must be in a lobby to retrieve CSteamIDs of other users in that lobby
	virtual CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember) = 0;

	// Get data associated with this lobby
	// takes a simple key, and returns the string associated with it
	// "" will be returned if no value is set, or if steamIDLobby is invalid
	virtual const char *GetLobbyData(CSteamID steamIDLobby, const char *pchKey) = 0;
	// Sets a key/value pair in the lobby metadata
	// each user in the lobby will be broadcast this new value, and any new users joining will receive any existing data
	// this can be used to set lobby names, map, etc.
	// to reset a key, just set it to ""
	// other users in the lobby will receive notification of the lobby data change via a LobbyDataUpdate_t callback
	virtual bool SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue) = 0;

	// returns the number of metadata keys set on the specified lobby
	virtual int GetLobbyDataCount(CSteamID steamIDLobby) = 0;

	// returns a lobby metadata key/values pair by index, of range [0, GetLobbyDataCount())
	virtual bool GetLobbyDataByIndex(CSteamID steamIDLobby, int iLobbyData, char *pchKey, int cchKeyBufferSize, char *pchValue, int cchValueBufferSize) = 0;

	// removes a metadata key from the lobby
	virtual bool DeleteLobbyData(CSteamID steamIDLobby, const char *pchKey) = 0;

	// Gets per-user metadata for someone in this lobby
	virtual const char *GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey) = 0;
	// Sets per-user metadata (for the local user implicitly)
	virtual void SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue) = 0;

	// Broadcasts a chat message to the all the users in the lobby
	// users in the lobby (including the local user) will receive a LobbyChatMsg_t callback
	// returns true if the message is successfully sent
	// pvMsgBody can be binary or text data, up to 4k
	// if pvMsgBody is text, cubMsgBody should be strlen( text ) + 1, to include the null terminator
	virtual bool SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody) = 0;
	// Get a chat message as specified in a LobbyChatMsg_t callback
	// iChatID is the LobbyChatMsg_t::m_iChatID value in the callback
	// *pSteamIDUser is filled in with the CSteamID of the member
	// *pvData is filled in with the message itself
	// return value is the number of BYTEs written into the buffer
	virtual int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, void *peChatEntryType) = 0;

	// Refreshes metadata for a lobby you're not necessarily in right now
	// you never do this for lobbies you're a member of, only if your
	// this will send down all the metadata associated with a lobby
	// this is an asynchronous call
	// returns false if the local user is not connected to the Steam servers
	// results will be returned by a LobbyDataUpdate_t callback
	// if the specified lobby doesn't exist, LobbyDataUpdate_t::m_bSuccess will be set to false
	virtual bool RequestLobbyData(CSteamID steamIDLobby) = 0;

	// sets the game server associated with the lobby
	// usually at this point, the users will join the specified game server
	// either the IP/Port or the steamID of the game server has to be valid, depending on how you want the clients to be able to connect
	virtual void SetLobbyGameServer(CSteamID steamIDLobby, uint32_t unGameServerIP, uint16_t unGameServerPort, CSteamID steamIDGameServer) = 0;
	// returns the details of a game server set in a lobby - returns false if there is no game server set, or that lobby doesn't exist
	virtual bool GetLobbyGameServer(CSteamID steamIDLobby, uint32_t *punGameServerIP, uint16_t *punGameServerPort, CSteamID *psteamIDGameServer) = 0;

	// set the limit on the # of users who can join the lobby
	virtual bool SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers) = 0;
	// returns the current limit on the # of users who can join the lobby; returns 0 if no limit is defined
	virtual int GetLobbyMemberLimit(CSteamID steamIDLobby) = 0;

	// updates which type of lobby it is
	// only lobbies that are k_ELobbyTypePublic or k_ELobbyTypeInvisible, and are set to joinable, will be returned by RequestLobbyList() calls
	virtual bool SetLobbyType(CSteamID steamIDLobby, ELobbyType eLobbyType) = 0;

	// sets whether or not a lobby is joinable - defaults to true for a new lobby
	// if set to false, no user can join, even if they are a friend or have been invited
	virtual bool SetLobbyJoinable(CSteamID steamIDLobby, bool bLobbyJoinable) = 0;

	// returns the current lobby owner
	// you must be a member of the lobby to access this
	// there always one lobby owner - if the current owner leaves, another user will become the owner
	// it is possible (bur rare) to join a lobby just as the owner is leaving, thus entering a lobby with self as the owner
	virtual CSteamID GetLobbyOwner(CSteamID steamIDLobby) = 0;

	// changes who the lobby owner is
	// you must be the lobby owner for this to succeed, and steamIDNewOwner must be in the lobby
	// after completion, the local user will no longer be the owner
	virtual bool SetLobbyOwner(CSteamID steamIDLobby, CSteamID steamIDNewOwner) = 0;

	// link two lobbies for the purposes of checking player compatibility
	// you must be the lobby owner of both lobbies
	virtual bool SetLinkedLobby(CSteamID steamIDLobby, CSteamID steamIDLobbyDependent) = 0;*/
};
ISteamMatchmaking* g_pSteamMatchmaking = NULL;

//class ISteamUser
//{
//public:
//	virtual HSteamUser GetHSteamUser() = 0;
//	virtual bool BLoggedOn() = 0;
//	virtual CSteamID GetSteamID() = 0;
//
//	/*CSteamID GetSteamID()
//	{
//		//return ((CSteamID(__cdecl*)(ISteamUser*))GetProcAddress(GetModuleHandle("steam_api.dll"), "SteamAPI_ISteamUser_GetSteamID"))(this);
//		
//		typedef CSteamID(__thiscall* OriginalFn)(void*);
//		return CallVFunc<OriginalFn>(this, 2)(this);
//	}*/
//};
class ISteamUser
{
public:
	virtual uint32_t GetHSteamUser() = 0;
	virtual bool BLoggedOn() = 0;
	virtual CSteamID GetSteamID() = 0;
};
ISteamUser* g_pSteamUser = NULL;
//
//class ISteamClient
//{
//public:
//	ISteamUser *GetISteamUser(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
//	{
//		typedef ISteamUser*(__thiscall* OriginalFn)(void*, HSteamUser, HSteamPipe, const char*);
//		return CallVFunc<OriginalFn>(this, 5)(this, hSteamUser, hSteamPipe, pchVersion);
//	}
//
//	void *GetISteamGenericInterface(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
//	{
//		typedef void*(__thiscall* OriginalFn)(void*, HSteamUser, HSteamPipe, const char*);
//		return CallVFunc<OriginalFn>(this, 12)(this, hSteamUser, hSteamPipe, pchVersion);
//	}
//	ISteamMatchmaking *GetISteamMatchmaking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
//	{
//		typedef ISteamMatchmaking*(__thiscall* OriginalFn)(void*, HSteamUser, HSteamPipe, const char*);
//		return CallVFunc<OriginalFn>(this, 16)(this, hSteamUser, hSteamPipe, pchVersion);
//	}
//};

enum EGCResult
{
	k_EGCResultOK = 0,
	k_EGCResultNoMessage = 1,           // There is no message in the queue
	k_EGCResultBufferTooSmall = 2,      // The buffer is too small for the requested message
	k_EGCResultNotLoggedOn = 3,         // The client is not logged onto Steam
	k_EGCResultInvalidMessage = 4,      // Something was wrong with the message being sent with SendMessage
};


class ISteamGameCoordinator
{
public:
	virtual EGCResult GCSendMessage(int unMsgType, const void* pubData, int cubData) = 0;
	virtual bool IsMessageAvailable(int* pcubMsgSize) = 0;
	virtual EGCResult GCRetrieveMessage(int* punMsgType, void* pubDest, int cubDest, int* pcubMsgSize) = 0;

};
ISteamGameCoordinator* g_pSteamGameCoordinator = NULL;

class ISteamClient
{
public:
	ISteamUser* GetISteamUser(void* hSteamUser, void* hSteamPipe, const char* pchVersion)
	{
		typedef ISteamUser* (__stdcall* func)(void*, void*, const char*);
		return CallVFunc<func>(this, 5)(hSteamUser, hSteamPipe, pchVersion);
	}

	ISteamGameCoordinator* GetISteamGenericInterface(void* hSteamUser, void* hSteamPipe, const char* pchVersion)
	{
		typedef ISteamGameCoordinator* (__stdcall* func)(void*, void*, const char*);
		return CallVFunc<func>(this, 12)(hSteamUser, hSteamPipe, pchVersion);
	}
};

ISteamClient* g_pSteamClient = NULL;

//enum EGCResults
//{
//	k_EGCResultOK = 0,
//	k_EGCResultNoMessage = 1,			// There is no message in the queue
//	k_EGCResultBufferTooSmall = 2,		// The buffer is too small for the requested message
//	k_EGCResultNotLoggedOn = 3,			// The client is not logged onto Steam
//	k_EGCResultInvalidMessage = 4,		// Something was wrong with the message being sent with SendMessage
//};

//class ISteamGameCoordinator
//{
//public:
//	virtual EGCResults sendMessage(uint32_t unMsgType, const void *pubData, uint32_t cubData) = 0;
//	virtual bool IsMessageAvailable(uint32_t *pcubMsgSize) = 0;
//	virtual EGCResults RetrieveMessage(uint32_t *punMsgType, void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize) = 0;
//};

