#pragma once

namespace RW
{
	const unsigned int k_unSteamAccountIDMask = 0xFFFFFFFF;
	const unsigned int k_unSteamAccountInstanceMask = 0x000FFFFF;
	// we allow 3 simultaneous user account instances right now, 1= desktop, 2 = console, 4 = web, 0 = all
	const unsigned int k_unSteamUserDesktopInstance = 1;
	const unsigned int k_unSteamUserConsoleInstance = 2;
	const unsigned int k_unSteamUserWebInstance = 4;

	// Special flags for Chat accounts - they go in the top 8 bits
	// of the steam ID's "instance", leaving 12 for the actual instances
	enum EChatSteamIDInstanceFlags
	{
		k_EChatAccountInstanceMask = 0x00000FFF, // top 8 bits are flags

		k_EChatInstanceFlagClan = (k_unSteamAccountInstanceMask + 1) >> 1,	// top bit
		k_EChatInstanceFlagLobby = (k_unSteamAccountInstanceMask + 1) >> 2,	// next one down, etc
		k_EChatInstanceFlagMMSLobby = (k_unSteamAccountInstanceMask + 1) >> 3,	// next one down, etc

																				// Max of 8 flags
	};
	enum EUserConnect
	{
		// TODO: Reverse this enum
	};

	typedef unsigned long long uint64;
	typedef uint64 SteamAPICall_t;


	typedef short int16;
	typedef unsigned short uint16;
	typedef unsigned int uint32;
	typedef unsigned long long uint64;
	typedef uint32 AppId_t;

	typedef unsigned int uint32;

	typedef int int32;

	typedef int32 HSteamPipe;
	// handle to single instance of a steam user
	typedef int32 HSteamUser;
	// reference to a steam call, to filter results by
	typedef int32 HSteamCall;

	typedef uint32 HAuthTicket;

	enum EServerMode
	{
		eServerModeInvalid = 0, // DO NOT USE		
		eServerModeNoAuthentication = 1, // Don't authenticate user logins and don't list on the server list
		eServerModeAuthentication = 2, // Authenticate users, list on the server list, don't run VAC on clients that connect
		eServerModeAuthenticationAndSecure = 3, // Authenticate users, list on the server list and VAC protect clients
	};

	// Steam universes.  Each universe is a self-contained Steam instance.
	enum EUniverse
	{
		k_EUniverseInvalid = 0,
		k_EUniversePublic = 1,
		k_EUniverseBeta = 2,
		k_EUniverseInternal = 3,
		k_EUniverseDev = 4,
		//	k_EUniverseRC = 5, // Removed

		k_EUniverseMax
	};


	typedef enum EBeginAuthSessionResult
	{
		k_EBeginAuthSessionResultOK = 0,						// Ticket is valid for this game and this steamID.
		k_EBeginAuthSessionResultInvalidTicket = 1,				// Ticket is not valid.
		k_EBeginAuthSessionResultDuplicateRequest = 2,			// A ticket has already been submitted for this steamID
		k_EBeginAuthSessionResultInvalidVersion = 3,			// Ticket is from an incompatible interface version
		k_EBeginAuthSessionResultGameMismatch = 4,				// Ticket is not for this game
		k_EBeginAuthSessionResultExpiredTicket = 5,				// Ticket has expired
	} EBeginAuthSessionResult;


	typedef enum EUserHasLicenseForAppResult
	{
		k_EUserHasLicenseResultHasLicense = 0,					// User has a license for specified app
		k_EUserHasLicenseResultDoesNotHaveLicense = 1,			// User does not have a license for the specified app
		k_EUserHasLicenseResultNoAuth = 2,						// User has not been authenticated
	} EUserHasLicenseForAppResult;

	typedef enum ELogonState
	{
		k_ELogonStateNotLoggedOn = 0,
		k_ELogonStateLoggingOn = 1,
		k_ELogonStateLoggingOff = 2,
		k_ELogonStateLoggedOn = 3
	} ELogonState;

	typedef enum EConnectionPriority
	{
		k_EConnectionPriorityLow = 0,
		k_EConnectionPriorityMedium = 1,
		k_EConnectionPriorityHigh = 2,
	} EConnectionPriority;


	typedef uint32 CellID_t;


	typedef enum ESteamUsageEvent
	{
		k_ESteamUsageEventMarketingMessageView = 1,
		k_ESteamUsageEventHardwareSurvey = 2,
		k_ESteamUsageEventDownloadStarted = 3,
		k_ESteamUsageEventLocalizedAudioChange = 4,
		k_ESteamUsageEventClientGUIUsage = 5,
		k_ESteamUsageEventCharityChoice = 6,
	} ESteamUsageEvent;



	typedef unsigned char uint8;
	typedef signed char int8;


	enum EAccountType
	{
		k_EAccountTypeInvalid = 0,
		k_EAccountTypeIndividual = 1,		// single user account
		k_EAccountTypeMultiseat = 2,		// multiseat (e.g. cybercafe) account
		k_EAccountTypeGameServer = 3,		// game server account
		k_EAccountTypeAnonGameServer = 4,	// anonymous game server account
		k_EAccountTypePending = 5,			// pending
		k_EAccountTypeContentServer = 6,	// content server
		k_EAccountTypeClan = 7,
		k_EAccountTypeChat = 8,
		k_EAccountTypeConsoleUser = 9,		// Fake SteamID for local PSN account on PS3 or Live account on 360, etc.
		k_EAccountTypeAnonUser = 10,

		// Max of 16 items in this field
		k_EAccountTypeMax
	};

#pragma pack( push, 1 )

	// Steam ID structure (64 bits total)
	class CSteamID
	{
	public:

		//-----------------------------------------------------------------------------
		// Purpose: Constructor
		//-----------------------------------------------------------------------------
		CSteamID()
		{
			m_steamid.m_comp.m_unAccountID = 0;
			m_steamid.m_comp.m_EAccountType = k_EAccountTypeInvalid;
			m_steamid.m_comp.m_EUniverse = k_EUniverseInvalid;
			m_steamid.m_comp.m_unAccountInstance = 0;
		}


		//-----------------------------------------------------------------------------
		// Purpose: Constructor
		// Input  : unAccountID -	32-bit account ID
		//			eUniverse -		Universe this account belongs to
		//			eAccountType -	Type of account
		//-----------------------------------------------------------------------------



		//-----------------------------------------------------------------------------
		// Purpose: Constructor
		// Input  : ulSteamID -		64-bit representation of a Steam ID
		// Note:	Will not accept a uint32 or int32 as input, as that is a probable mistake.
		//			See the stubbed out overloads in the private: section for more info.
		//-----------------------------------------------------------------------------
		CSteamID(uint64 ulSteamID)
		{
			SetFromUint64(ulSteamID);
		}


		//-----------------------------------------------------------------------------
		// Purpose: Sets parameters for steam ID
		// Input  : unAccountID -	32-bit account ID
		//			eUniverse -		Universe this account belongs to
		//			eAccountType -	Type of account
		//-----------------------------------------------------------------------------
		void Set(uint32 unAccountID, EUniverse eUniverse, EAccountType eAccountType)
		{
			m_steamid.m_comp.m_unAccountID = unAccountID;
			m_steamid.m_comp.m_EUniverse = eUniverse;
			m_steamid.m_comp.m_EAccountType = eAccountType;

			if (eAccountType == k_EAccountTypeClan)
			{
				m_steamid.m_comp.m_unAccountInstance = 0;
			}
			else
			{
				// by default we pick the desktop instance
				m_steamid.m_comp.m_unAccountInstance = k_unSteamUserDesktopInstance;
			}
		}


		//-----------------------------------------------------------------------------
		// Purpose: Sets parameters for steam ID
		// Input  : unAccountID -	32-bit account ID
		//			eUniverse -		Universe this account belongs to
		//			eAccountType -	Type of account
		//-----------------------------------------------------------------------------
		void InstancedSet(uint32 unAccountID, uint32 unInstance, EUniverse eUniverse, EAccountType eAccountType)
		{
			m_steamid.m_comp.m_unAccountID = unAccountID;
			m_steamid.m_comp.m_EUniverse = eUniverse;
			m_steamid.m_comp.m_EAccountType = eAccountType;
			m_steamid.m_comp.m_unAccountInstance = unInstance;
		}


		//-----------------------------------------------------------------------------
		// Purpose: Initializes a steam ID from its 52 bit parts and universe/type
		// Input  : ulIdentifier - 52 bits of goodness
		//-----------------------------------------------------------------------------
		void FullSet(uint64 ulIdentifier, EUniverse eUniverse, EAccountType eAccountType)
		{
			m_steamid.m_comp.m_unAccountID = (ulIdentifier & k_unSteamAccountIDMask);						// account ID is low 32 bits
			m_steamid.m_comp.m_unAccountInstance = ((ulIdentifier >> 32) & k_unSteamAccountInstanceMask);			// account instance is next 20 bits
			m_steamid.m_comp.m_EUniverse = eUniverse;
			m_steamid.m_comp.m_EAccountType = eAccountType;
		}


		//-----------------------------------------------------------------------------
		// Purpose: Initializes a steam ID from its 64-bit representation
		// Input  : ulSteamID -		64-bit representation of a Steam ID
		//-----------------------------------------------------------------------------
		void SetFromUint64(uint64 ulSteamID)
		{
			m_steamid.m_unAll64Bits = ulSteamID;
		}



		//-----------------------------------------------------------------------------
		// Purpose: Converts steam ID to its 64-bit representation
		// Output : 64-bit representation of a Steam ID
		//-----------------------------------------------------------------------------
		uint64 ConvertToUint64() const
		{
			return m_steamid.m_unAll64Bits;
		}


		//-----------------------------------------------------------------------------
		// Purpose: Converts the static parts of a steam ID to a 64-bit representation.
		//			For multiseat accounts, all instances of that account will have the
		//			same static account key, so they can be grouped together by the static
		//			account key.
		// Output : 64-bit static account key
		//-----------------------------------------------------------------------------
		uint64 GetStaticAccountKey() const
		{
			// note we do NOT include the account instance (which is a dynamic property) in the static account key
			return (uint64)((((uint64)m_steamid.m_comp.m_EUniverse) << 56) + ((uint64)m_steamid.m_comp.m_EAccountType << 52) + m_steamid.m_comp.m_unAccountID);
		}


		//-----------------------------------------------------------------------------
		// Purpose: create an anonymous game server login to be filled in by the AM
		//-----------------------------------------------------------------------------
		void CreateBlankAnonLogon(EUniverse eUniverse)
		{
			m_steamid.m_comp.m_unAccountID = 0;
			m_steamid.m_comp.m_EAccountType = k_EAccountTypeAnonGameServer;
			m_steamid.m_comp.m_EUniverse = eUniverse;
			m_steamid.m_comp.m_unAccountInstance = 0;
		}


		//-----------------------------------------------------------------------------
		// Purpose: create an anonymous game server login to be filled in by the AM
		//-----------------------------------------------------------------------------
		void CreateBlankAnonUserLogon(EUniverse eUniverse)
		{
			m_steamid.m_comp.m_unAccountID = 0;
			m_steamid.m_comp.m_EAccountType = k_EAccountTypeAnonUser;
			m_steamid.m_comp.m_EUniverse = eUniverse;
			m_steamid.m_comp.m_unAccountInstance = 0;
		}

		//-----------------------------------------------------------------------------
		// Purpose: Is this an anonymous game server login that will be filled in?
		//-----------------------------------------------------------------------------
		bool BBlankAnonAccount() const
		{
			return m_steamid.m_comp.m_unAccountID == 0 && BAnonAccount() && m_steamid.m_comp.m_unAccountInstance == 0;
		}

		//-----------------------------------------------------------------------------
		// Purpose: Is this a game server account id?
		//-----------------------------------------------------------------------------
		bool BGameServerAccount() const
		{
			return m_steamid.m_comp.m_EAccountType == k_EAccountTypeGameServer || m_steamid.m_comp.m_EAccountType == k_EAccountTypeAnonGameServer;
		}

		//-----------------------------------------------------------------------------
		// Purpose: Is this a content server account id?
		//-----------------------------------------------------------------------------
		bool BContentServerAccount() const
		{
			return m_steamid.m_comp.m_EAccountType == k_EAccountTypeContentServer;
		}


		//-----------------------------------------------------------------------------
		// Purpose: Is this a clan account id?
		//-----------------------------------------------------------------------------
		bool BClanAccount() const
		{
			return m_steamid.m_comp.m_EAccountType == k_EAccountTypeClan;
		}


		//-----------------------------------------------------------------------------
		// Purpose: Is this a chat account id?
		//-----------------------------------------------------------------------------
		bool BChatAccount() const
		{
			return m_steamid.m_comp.m_EAccountType == k_EAccountTypeChat;
		}

		//-----------------------------------------------------------------------------
		// Purpose: Is this a chat account id?
		//-----------------------------------------------------------------------------
		bool IsLobby() const
		{
			return (m_steamid.m_comp.m_EAccountType == k_EAccountTypeChat)
				&& (m_steamid.m_comp.m_unAccountInstance & k_EChatInstanceFlagLobby);
		}


		//-----------------------------------------------------------------------------
		// Purpose: Is this an individual user account id?
		//-----------------------------------------------------------------------------
		bool BIndividualAccount() const
		{
			return m_steamid.m_comp.m_EAccountType == k_EAccountTypeIndividual || m_steamid.m_comp.m_EAccountType == k_EAccountTypeConsoleUser;
		}


		//-----------------------------------------------------------------------------
		// Purpose: Is this an anonymous account?
		//-----------------------------------------------------------------------------
		bool BAnonAccount() const
		{
			return m_steamid.m_comp.m_EAccountType == k_EAccountTypeAnonUser || m_steamid.m_comp.m_EAccountType == k_EAccountTypeAnonGameServer;
		}

		//-----------------------------------------------------------------------------
		// Purpose: Is this an anonymous user account? ( used to create an account or reset a password )
		//-----------------------------------------------------------------------------
		bool BAnonUserAccount() const
		{
			return m_steamid.m_comp.m_EAccountType == k_EAccountTypeAnonUser;
		}

		//-----------------------------------------------------------------------------
		// Purpose: Is this a faked up Steam ID for a PSN friend account?
		//-----------------------------------------------------------------------------
		bool BConsoleUserAccount() const
		{
			return m_steamid.m_comp.m_EAccountType == k_EAccountTypeConsoleUser;
		}


		// simple accessors
		void SetAccountID(uint32 unAccountID) { m_steamid.m_comp.m_unAccountID = unAccountID; }
		void SetAccountInstance(uint32 unInstance) { m_steamid.m_comp.m_unAccountInstance = unInstance; }
		void ClearIndividualInstance() { if (BIndividualAccount()) m_steamid.m_comp.m_unAccountInstance = 0; }
		bool HasNoIndividualInstance() const { return BIndividualAccount() && (m_steamid.m_comp.m_unAccountInstance == 0); }
		uint32 GetAccountID() const			{ return m_steamid.m_comp.m_unAccountID; }
		uint32 GetUnAccountInstance() const { return m_steamid.m_comp.m_unAccountInstance; }
		EAccountType GetEAccountType() const { return (EAccountType)m_steamid.m_comp.m_EAccountType; }
		EUniverse GetEUniverse() const { return m_steamid.m_comp.m_EUniverse; }
		void SetEUniverse(EUniverse eUniverse) { m_steamid.m_comp.m_EUniverse = eUniverse; }
		bool IsValid() const;

		// this set of functions is hidden, will be moved out of class
		explicit CSteamID(const char *pchSteamID, EUniverse eDefaultUniverse = k_EUniverseInvalid);

#ifdef _MSC_VER
#pragma warning(push) 
#pragma warning(disable: 4996) 
#endif

		const char * Render() const				// renders this steam ID to string
		{
			const int k_cBufLen = 30;
			const int k_cBufs = 4;
			char* pchBuf;

			static char rgchBuf[k_cBufs][k_cBufLen];
			static int nBuf = 0;

			pchBuf = rgchBuf[nBuf++];
			nBuf %= k_cBufs;

			switch (m_steamid.m_comp.m_EAccountType)
			{
			case k_EAccountTypeInvalid:
			case k_EAccountTypeIndividual:
				sprintf(pchBuf, "STEAM_0:%u:%u", (m_steamid.m_comp.m_unAccountID % 2) ? 1 : 0, (uint32)m_steamid.m_comp.m_unAccountID);
				break;
			default:
				sprintf(pchBuf, "%llu", ConvertToUint64());
			}
			return pchBuf;
		}
		static const char * Render(uint64 ulSteamID)	// static method to render a uint64 representation of a steam ID to a string
		{
			return CSteamID(ulSteamID).Render();
		}

		const char *SteamRender() const // renders this steam ID to string using the new rendering style
		{
			const int k_cBufLen = 37;
			const int k_cBufs = 4;
			char* pchBuf;

			static char rgchBuf[k_cBufs][k_cBufLen];
			static int nBuf = 0;

			pchBuf = rgchBuf[nBuf++];
			nBuf %= k_cBufs;

			switch (m_steamid.m_comp.m_EAccountType)
			{
			case k_EAccountTypeAnonGameServer:
				sprintf(pchBuf, "[A:%u:%u:%u]", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID, m_steamid.m_comp.m_unAccountInstance);
				break;
			case k_EAccountTypeGameServer:
				sprintf(pchBuf, "[G:%u:%u]", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID);
				break;
			case k_EAccountTypeMultiseat:
				sprintf(pchBuf, "[M:%u:%u:%u]", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID, m_steamid.m_comp.m_unAccountInstance);
				break;
			case k_EAccountTypePending:
				sprintf(pchBuf, "[P:%u:%u]", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID);
				break;
			case k_EAccountTypeContentServer:
				sprintf(pchBuf, "[C:%u:%u]", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID);
				break;
			case k_EAccountTypeClan:
				sprintf(pchBuf, "[g:%u:%u]", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID);
				break;
			case k_EAccountTypeChat:
				switch (m_steamid.m_comp.m_unAccountInstance & ~k_EChatAccountInstanceMask)
				{
				case k_EChatInstanceFlagClan:
					sprintf(pchBuf, "[c:%u:%u]", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID);
					break;
				case k_EChatInstanceFlagLobby:
					sprintf(pchBuf, "[L:%u:%u]", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID);
					break;
				default:
					sprintf(pchBuf, "[T:%u:%u]", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID);
					break;
				}
				break;
			case k_EAccountTypeInvalid:
				sprintf(pchBuf, "[I:%u:%u]", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID);
				break;
			case k_EAccountTypeIndividual:
				sprintf(pchBuf, "[U:%u:%u]", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID);
				break;
			default:
				sprintf(pchBuf, "[i:%u:%u]", m_steamid.m_comp.m_EUniverse, m_steamid.m_comp.m_unAccountID);
				break;
			}

			return pchBuf;
		}

		static const char *SteamRender(uint64 ulSteamID)	// static method to render a uint64 representation of a steam ID to a string
		{
			return CSteamID(ulSteamID).SteamRender();
		}

#ifdef _MSC_VER
#pragma warning(pop) 
#endif

		void SetFromString(const char *pchSteamID, EUniverse eDefaultUniverse);
		bool SetFromSteam2String(const char *pchSteam2ID, EUniverse eUniverse);

		inline bool operator==(const CSteamID &val) const { return m_steamid.m_unAll64Bits == val.m_steamid.m_unAll64Bits; }
		inline bool operator!=(const CSteamID &val) const { return !operator==(val); }
		inline bool operator<(const CSteamID &val) const { return m_steamid.m_unAll64Bits < val.m_steamid.m_unAll64Bits; }
		inline bool operator>(const CSteamID &val) const { return m_steamid.m_unAll64Bits > val.m_steamid.m_unAll64Bits; }

		// DEBUG function
		bool BValidExternalSteamID() const;

	private:
		// These are defined here to prevent accidental implicit conversion of a u32AccountID to a CSteamID.
		// If you get a compiler error about an ambiguous constructor/function then it may be because you're
		// passing a 32-bit int to a function that takes a CSteamID. You should explicitly create the SteamID
		// using the correct Universe and account Type/Instance values.
		CSteamID(uint32);
		CSteamID(int32);

		// 64 bits total
		union SteamID_t
		{
			struct SteamIDComponent_t
			{

				uint32				m_unAccountID : 32;			// unique account identifier
				unsigned int		m_unAccountInstance : 20;	// dynamic instance ID
				unsigned int		m_EAccountType : 4;			// type of account - can't show as EAccountType, due to signed / unsigned difference
				EUniverse			m_EUniverse : 8;	// universe this account belongs to
			} m_comp;

			uint64 m_unAll64Bits;
		} m_steamid;
	};

#ifndef NO_CSTEAMID_STL
	inline std::ostream& operator<<(std::ostream& out, const CSteamID& s)
	{
		out << s.Render();
		return out;
	}
#endif //NO_CSTEAMID_STL

	inline bool CSteamID::IsValid() const
	{
		if (m_steamid.m_comp.m_EAccountType <= k_EAccountTypeInvalid || m_steamid.m_comp.m_EAccountType >= k_EAccountTypeMax)
			return false;

		if (m_steamid.m_comp.m_EUniverse <= k_EUniverseInvalid || m_steamid.m_comp.m_EUniverse >= k_EUniverseMax)
			return false;

		if (m_steamid.m_comp.m_EAccountType == k_EAccountTypeIndividual)
		{
			if (m_steamid.m_comp.m_unAccountID == 0 || m_steamid.m_comp.m_unAccountInstance > k_unSteamUserWebInstance)
				return false;
		}

		if (m_steamid.m_comp.m_EAccountType == k_EAccountTypeClan)
		{
			if (m_steamid.m_comp.m_unAccountID == 0 || m_steamid.m_comp.m_unAccountInstance != 0)
				return false;
		}

		if (m_steamid.m_comp.m_EAccountType == k_EAccountTypeGameServer)
		{
			if (m_steamid.m_comp.m_unAccountID == 0)
				return false;
			// Any limit on instances?  We use them for local users and bots
		}
		return true;
	}

	// generic invalid CSteamID
#define k_steamIDNil CSteamID()

	// This steamID comes from a user game connection to an out of date GS that hasnt implemented the protocol
	// to provide its steamID
#define k_steamIDOutofDateGS CSteamID( 0, 0, k_EUniverseInvalid, k_EAccountTypeInvalid )
	// This steamID comes from a user game connection to an sv_lan GS
#define k_steamIDLanModeGS CSteamID( 0, 0, k_EUniversePublic, k_EAccountTypeInvalid )
	// This steamID can come from a user game connection to a GS that has just booted but hasnt yet even initialized
	// its steam3 component and started logging on.
#define k_steamIDNotInitYetGS CSteamID( 1, 0, k_EUniverseInvalid, k_EAccountTypeInvalid )
	// This steamID can come from a user game connection to a GS that isn't using the steam authentication system but still
	// wants to support the "Join Game" option in the friends list
#define k_steamIDNonSteamGS CSteamID( 2, 0, k_EUniverseInvalid, k_EAccountTypeInvalid )

	struct ConnectedUserInfo_t
	{
		int32 m_cubConnectedUserInfo;
		int32 m_nCountOfGuestUsers;
		CSteamID m_SteamID;
		uint32 m_unIPPublic;
		uint32 m_nFrags;
		double m_flConnectTime;
		//EGameConnectSteamResponse m_eGameConnectSteamResponse;
		//EDenyReason m_eDenyReason;
	};

	class ISteamGameServer
	{
	public:
		// returns the HSteamUser this interface represents
		virtual HSteamUser GetHSteamUser() = 0;

		virtual bool InitGameServer(uint32 unGameIP, uint16 unGamePort, uint16 usQueryPort, uint32 unServerFlags, AppId_t nAppID, const char *pchVersion) = 0;
		virtual void SetProduct(const char *pchProductName) = 0;
		virtual void SetGameDescription(const char *pchGameDescription) = 0;
		virtual void SetModDir(const char *pchModDir) = 0;
		virtual void SetDedicatedServer(bool bDedicatedServer) = 0;
		virtual void LogOn(const char *pchToken) = 0;
		virtual void LogOnAnonymous() = 0;
		virtual void LogOff() = 0;

		virtual CSteamID GetSteamID() = 0;

		virtual bool BLoggedOn() = 0;

		virtual bool BSecure() = 0;

		// Returns true if the master server has requested a restart.
		// Only returns true once per request.
		virtual bool WasRestartRequested() = 0;

		virtual void SetMaxPlayerCount(int32 cPlayersMax) = 0;
		virtual void SetBotPlayerCount(int32 cBotPlayers) = 0;
		virtual void SetServerName(const char *pchServerName) = 0;
		virtual void SetMapName(const char *pchMapName) = 0;
		virtual void SetPasswordProtected(bool bPasswordProtected) = 0;

		// This can be called if spectator goes away or comes back (passing 0 means there is no spectator server now).
		virtual void SetSpectatorPort() = 0;

		virtual void SetSpectatorServerName(const char *pchSpectatorServerName) = 0;

		// Call this to clear the whole list of key/values that are sent in rules queries.
		virtual void ClearAllKeyValues() = 0;

		// Call this to add/update a key/value pair.
		virtual void SetKeyValue(const char *pKey, const char *pValue) = 0;

		// Sets a string defining the "gametags" for this server, this is optional, but if it is set
		// it allows users to filter in the matchmaking/server-browser interfaces based on the value
		virtual void SetGameTags(const char *pchGameTags) = 0;

		// Sets a string defining the "gamedata" for this server, this is optional, but if it is set
		// it allows users to filter in the matchmaking/server-browser interfaces based on the value
		// don't set this unless it actually changes, its only uploaded to the master once (when
		// acknowledged)
		virtual void SetGameData(const char *pchGameData) = 0;

		virtual void SetRegion(const char *pchRegionName) = 0;

		// Handles receiving a new connection from a Steam user.  This call will ask the Steam
		// servers to validate the users identity, app ownership, and VAC status.  If the Steam servers 
		// are off-line, then it will validate the cached ticket itself which will validate app ownership 
		// and identity.  The AuthBlob here should be acquired on the game client using SteamUser()->InitiateGameConnection()
		// and must then be sent up to the game server for authentication.
		//
		// Return Value: returns true if the users ticket passes basic checks. pSteamIDUser will contain the Steam ID of this user. pSteamIDUser must NOT be NULL
		// If the call succeeds then you should expect a GSClientApprove_t or GSClientDeny_t callback which will tell you whether authentication
		// for the user has succeeded or failed (the steamid in the callback will match the one returned by this call)
		virtual EUserConnect SendUserConnectAndAuthenticate(uint32 unIPClient, const void *pvAuthBlob, uint32 cubAuthBlobSize, CSteamID *pSteamIDUser) = 0;

		// Creates a fake user (ie, a bot) which will be listed as playing on the server, but skips validation.  
		// 
		// Return Value: Returns a SteamID for the user to be tracked with, you should call HandleUserDisconnect()
		// when this user leaves the server just like you would for a real user.
		virtual CSteamID CreateUnauthenticatedUserConnection() = 0;

		// Should be called whenever a user leaves our game server, this lets Steam internally
		// track which users are currently on which servers for the purposes of preventing a single
		// account being logged into multiple servers, showing who is currently on a server, etc.
		virtual void SendUserDisconnect(CSteamID steamIDUser) = 0;

		// Update the data to be displayed in the server browser and matchmaking interfaces for a user
		// currently connected to the server.  For regular users you must call this after you receive a
		// GSUserValidationSuccess callback.
		// 
		// Return Value: true if successful, false if failure (ie, steamIDUser wasn't for an active player)
		virtual bool BUpdateUserData(CSteamID steamIDUser, const char *pchPlayerName, uint32 uScore) = 0;

		// New auth system APIs - do not mix with the old auth system APIs.
		// ----------------------------------------------------------------

		// Retrieve ticket to be sent to the entity who wishes to authenticate you ( using BeginAuthSession API ). 
		// pcbTicket retrieves the length of the actual ticket.
		virtual HAuthTicket GetAuthSessionTicket(void *pTicket, int32 cbMaxTicket, uint32 *pcbTicket) = 0;

		// Authenticate ticket ( from GetAuthSessionTicket ) from entity steamID to be sure it is valid and isnt reused
		// Registers for callbacks if the entity goes offline or cancels the ticket ( see ValidateAuthTicketResponse_t callback and EAuthSessionResponse )
		virtual EBeginAuthSessionResult BeginAuthSession(const void *pAuthTicket, int32 cbAuthTicket, CSteamID steamID) = 0;

		// Stop tracking started by BeginAuthSession - called when no longer playing game with this entity
		virtual void EndAuthSession(CSteamID steamID) = 0;

		// Cancel auth ticket from GetAuthSessionTicket, called when no longer playing game with the entity you gave the ticket to
		virtual void CancelAuthTicket(HAuthTicket hAuthTicket) = 0;

		// After receiving a user's authentication data, and passing it to SendUserConnectAndAuthenticate, use this function
		// to determine if the user owns downloadable content specified by the provided AppID.
		virtual EUserHasLicenseForAppResult IsUserSubscribedAppInTicket(CSteamID steamID, AppId_t appID) = 0;

		// Ask if a user in in the specified group, results returns async by GSUserGroupStatus_t
		// returns false if we're not connected to the steam servers and thus cannot ask
		virtual bool RequestUserGroupStatus(CSteamID steamIDUser, CSteamID steamIDGroup) = 0;

		// Ask for the gameplay stats for the server. Results returned in a callback
		virtual void GetGameplayStats() = 0;

		// Gets the reputation score for the game server. This API also checks if the server or some
		// other server on the same IP is banned from the Steam master servers.
		virtual SteamAPICall_t GetServerReputation() = 0;

		// Returns the public IP of the server according to Steam, useful when the server is 
		// behind NAT and you want to advertise its IP in a lobby for other clients to directly
		// connect to
		virtual uint32 GetPublicIP() = 0;

		// These are in GameSocketShare mode, where instead of ISteamGameServer creating its own
		// socket to talk to the master server on, it lets the game use its socket to forward messages
		// back and forth. This prevents us from requiring server ops to open up yet another port
		// in their firewalls.
		//
		// the IP address and port should be in host order, i.e 127.0.0.1 == 0x7f000001

		// These are used when you've elected to multiplex the game server's UDP socket
		// rather than having the master server updater use its own sockets.
		// 
		// Source games use this to simplify the job of the server admins, so they 
		// don't have to open up more ports on their firewalls.

		// Call this when a packet that starts with 0xFFFFFFFF comes in. That means
		// it's for us.
		virtual bool HandleIncomingPacket(const void *pData, int32 cbData, uint32 srcIP, uint16 srcPort) = 0;

		// AFTER calling HandleIncomingPacket for any packets that came in that frame, call this.
		// This gets a packet that the master server updater needs to send out on UDP.
		// It returns the length of the packet it wants to send, or 0 if there are no more packets to send.
		// Call this each frame until it returns 0.
		virtual int32 GetNextOutgoingPacket(void *pOut, int32 cbMaxOut, uint32 *pNetAdr, uint16 *pPort) = 0;

		virtual void EnableHeartbeats(bool bEnabled) = 0;
		virtual void SetHeartbeatInterval(int32 iInterval) = 0;

		// Force it to request a heartbeat from the master servers.
		virtual void ForceHeartbeat() = 0;


		virtual ELogonState GetLogonState() = 0;
		virtual bool BConnected() = 0;

		virtual int32 RaiseConnectionPriority(EConnectionPriority eConnectionPriority) = 0;
		virtual void ResetConnectionPriority(int32 hRaiseConnectionPriorityPrev) = 0;

		virtual void SetCellID(CellID_t cellID) = 0;

		virtual void TrackSteamUsageEvent(ESteamUsageEvent eSteamUsageEvent, const uint8 *pubKV, uint32 cubKV) = 0;

		virtual void SetCountOfSimultaneousGuestUsersPerSteamAccount(int32 nCount) = 0;

		virtual bool EnumerateConnectedUsers(int32 iterator, ConnectedUserInfo_t *pConnectedUserInfo) = 0;

		virtual SteamAPICall_t AssociateWithClan(CSteamID clanID) = 0;
		virtual SteamAPICall_t ComputeNewPlayerCompatibility(CSteamID steamID) = 0;

		// Ask if a user has a specific achievement for this game, will get a callback on reply
		virtual bool _BGetUserAchievementStatus(CSteamID steamID, const char *pchAchievementName) = 0;

		virtual void _GSSetSpawnCount(uint32 ucSpawn) = 0;
		virtual bool _GSGetSteam2GetEncryptionKeyToSendToNewClient(void *pvEncryptionKey, uint32 *pcbEncryptionKey, uint32 cbMaxEncryptionKey) = 0;

		virtual bool _GSSendSteam2UserConnect(uint32 unUserID, const void *pvRawKey, uint32 unKeyLen, uint32 unIPPublic, uint16 usPort, const void *pvCookie, uint32 cubCookie) = 0;
		virtual bool _GSSendSteam3UserConnect(CSteamID steamID, uint32 unIPPublic, const void *pvCookie, uint32 cubCookie) = 0;

		virtual bool _GSSendUserConnect(uint32 unUserID, uint32 unIPPublic, uint16 usPort, const void *pvCookie, uint32 cubCookie) = 0;
		virtual bool _GSRemoveUserConnect(uint32 unUserID) = 0;

		// Updates server status values which shows up in the server browser and matchmaking APIs
		virtual bool _GSUpdateStatus(int32 cPlayers, int32 cPlayersMax, int32 cBotPlayers, const char *pchServerName, const char *pSpectatorServerName, const char *pchMapName) = 0;

		virtual bool _GSCreateUnauthenticatedUser(CSteamID *pSteamID) = 0;

		virtual bool _GSSetServerType(int32 iAppID, uint32 unServerFlags, uint32 unGameIP, uint16 unGamePort, uint16 unSpectatorPort, uint16 usQueryPort, const char *pchGameDir, const char *pchVersion, bool bLANMode) = 0;
		virtual void _SetBasicServerData(unsigned short nProtocolVersion, bool bDedicatedServer, const char *pRegionName, const char *pProductName, unsigned short nMaxReportedClients, bool bPasswordProtected, const char *pGameDescription) = 0;

		virtual bool _GSSendUserDisconnect(CSteamID, uint32 unUserID) = 0;
	};


	class IClientUser
	{
	public:
		virtual HSteamUser GetHSteamUser() = 0;

		virtual void LogOn(bool bInteractive, CSteamID steamID) = 0;
		virtual void LogOnWithPassword(bool bInteractive, const char * pchLogin, const char * pchPassword) = 0;
		virtual void LogOnAndCreateNewSteamAccountIfNeeded(bool bInteractive) = 0;
		virtual int LogOnConnectionless() = 0;
		virtual void LogOff() = 0;
		virtual bool BLoggedOn() = 0;
		virtual int GetLogonState() = 0;
		virtual bool BConnected() = 0;
		virtual bool BTryingToLogin() = 0;

		virtual CSteamID GetSteamID() = 0;
		virtual CSteamID GetConsoleSteamID() = 0;

		virtual bool IsVACBanned(unsigned int nGameID) = 0;
		virtual bool RequireShowVACBannedMessage(AppId_t nAppID) = 0;
		virtual void AcknowledgeVACBanning(AppId_t nAppID) = 0;

		virtual bool SetEmail(const char *pchEmail) = 0;

		virtual bool SetConfigString() = 0;
		virtual bool GetConfigString() = 0;
		virtual bool SetConfigInt() = 0;
		virtual bool GetConfigInt() = 0;

		virtual bool GetConfigStoreKeyName() = 0; // 20

		virtual int32 InitiateGameConnection() = 0;
		virtual int32 InitiateGameConnectionOld() = 0;

		virtual void TerminateGameConnection() = 0;
		virtual bool TerminateAppMultiStep() = 0;

		virtual void SetSelfAsPrimaryChatDestination() = 0;
		virtual bool IsPrimaryChatDestination() = 0;

		virtual void RequestLegacyCDKey(AppId_t iAppID) = 0;

		virtual bool AckGuestPass(const char *pchGuestPassCode) = 0;
		virtual bool RedeemGuestPass(const char *pchGuestPassCode) = 0;

		virtual uint32 GetGuestPassToGiveCount() = 0;
		virtual uint32 GetGuestPassToRedeemCount() = 0;

		virtual bool GetGuestPassToGiveInfo() = 0;
		virtual bool GetGuestPassToRedeemInfo() = 0;
		virtual bool GetGuestPassToRedeemSenderName(uint32 nPassIndex, char* pchSenderName, int32 cSenderNameSize) = 0;

		virtual void AcknowledgeMessageByGID(const char *pchMessageGID) = 0;

		virtual bool SetLanguage(const char *pchLanguage) = 0;

		virtual void TrackAppUsageEvent() = 0;

		virtual int32 RaiseConnectionPriority(EConnectionPriority eConnectionPriority) = 0;
		virtual void ResetConnectionPriority(int32 hRaiseConnectionPriorityPrev) = 0;

		virtual void SetAccountNameFromSteam2(const char *pchAccountName) = 0;
		virtual bool SetPasswordFromSteam2(const char *pchPassword) = 0;

		virtual bool BHasCachedCredentials(const char * pchUnk) = 0;
		virtual bool SetAccountNameForCachedCredentialLogin(const char *pchAccountName, bool bUnk) = 0;
		virtual void SetLoginInformation(const char *pchAccountName, const char *pchPassword, bool bRememberPassword) = 0;
		virtual void ClearAllLoginInformation() = 0;

		virtual void SetAccountCreationTime() = 0;

		virtual SteamAPICall_t RequestWebAuthToken() = 0;
		virtual bool GetCurrentWebAuthToken(char *pchBuffer, int32 cubBuffer) = 0;

		virtual bool GetLanguage(char* pchLanguage, int32 cbLanguage) = 0;

		virtual bool BIsCyberCafe() = 0;
		virtual bool BIsAcademicAccount() = 0;

		virtual void CreateAccount(const char *pchAccountName, const char *pchNewPassword, const char *pchNewEmail, int32 iQuestion, const char *pchNewQuestion, const char *pchNewAnswer) = 0;

		virtual SteamAPICall_t ResetPassword(const char *pchAccountName, const char *pchOldPassword, const char *pchNewPassword, const char *pchValidationCode, const char *pcwer) = 0;

		virtual void TrackNatTraversalStat(const void *pNatStat) = 0;

		virtual void TrackSteamUsageEvent(ESteamUsageEvent eSteamUsageEvent, const uint8 *pubKV, uint32 cubKV) = 0;
		virtual void TrackSteamGUIUsage(const char *) = 0;

		virtual void SetComputerInUse() = 0;

		virtual bool BIsGameRunning(void* gameID) = 0;


		virtual uint64 GetCurrentSessionToken() = 0;

		virtual bool BUpdateAppOwnershipTicket(AppId_t nAppID, bool bOnlyUpdateIfStale, bool bIsDepot) = 0;

		virtual bool RequestCustomBinary(const char *pszAbsolutePath, AppId_t nAppID, bool bForceUpdate, bool bAppLaunchRequest) = 0;
		virtual void* GetCustomBinariesState(AppId_t unAppID, uint32 *punProgress) = 0;
		virtual void* RequestCustomBinaries(AppId_t unAppID, bool, bool, uint32 *) = 0;

		virtual void SetCellID(CellID_t cellID) = 0;
		virtual void SetWinningPingTimeForCellID(uint32 uPing) = 0;

		virtual const char *GetUserBaseFolder() = 0;

		virtual bool GetUserDataFolder(void* gameID, char* pchBuffer, int32 cubBuffer) = 0;
		virtual bool GetUserConfigFolder(char *pchBuffer, int32 cubBuffer) = 0;

		virtual bool GetAccountName(char* pchAccountName, uint32 cb) = 0;
		virtual bool GetAccountName(CSteamID userID, char * pchAccountName, uint32 cb) = 0;
		virtual bool IsPasswordRemembered() = 0;

		virtual bool RequiresLegacyCDKey(AppId_t nAppID, bool * pbUnk) = 0;
		virtual bool GetLegacyCDKey(AppId_t nAppID, char* pchKeyData, int32 cbKeyData) = 0;
		virtual bool SetLegacyCDKey(AppId_t nAppID, const char* pchKeyData) = 0;
		virtual bool WriteLegacyCDKey(AppId_t nAppID) = 0;
		virtual void RemoveLegacyCDKey(AppId_t nAppID) = 0;
		virtual void RequestLegacyCDKeyFromApp(AppId_t nMainAppID, AppId_t nDLCAppID) = 0;

		virtual bool BIsAnyGameRunning() = 0;

		virtual void TestAvailablePassword(const uint8 *pubDigestPassword, int32 cubDigestPassword) = 0;
		virtual void GetSteamGuardDetails() = 0;

		virtual void ChangePassword(const char *pchOldPassword, const char *pchNewPassword) = 0;
		virtual void ChangeEmail(const char *, const char *pchEmail) = 0;
		virtual void ChangeSecretQuestionAndAnswer(const char *, int32 iQuestion, const char *pchNewQuestion, const char *pchNewAnswer) = 0;

		virtual void SetSteam2FullASTicket(uint8* pubTicket, int32 cubTicket) = 0;
		virtual int32 GetSteam2FullASTicket(uint8* pubTicket, int32 cubTicket) = 0;

		virtual bool GetEmail(char* pchEmail, int32 cchEmail, bool* pbValidated) = 0;

		virtual void RequestForgottenPasswordEmail(const char *pchAccountName, const char *pchTriedPassword) = 0;

		virtual void FindAccountsByEmailAddress(const char *pchEmailAddress) = 0;
		virtual void FindAccountsByCdKey(const char *pchCdKey) = 0;
		virtual void GetNumAccountsWithEmailAddress(const char * pchEmailAddress) = 0;
		virtual void IsAccountNameInUse(const char * pchAccountName) = 0;

		virtual void Test_FakeConnectionTimeout() = 0;

		virtual bool RunInstallScript(AppId_t *pAppIDs, int32 cAppIDs, const char *pchInstallPath, const char *pchLanguage, bool bUninstall) = 0;

		virtual AppId_t IsInstallScriptRunning() = 0;

		virtual bool GetInstallScriptState(char* pchDescription, uint32 cchDescription, uint32* punNumSteps, uint32* punCurrStep) = 0;

		virtual bool SpawnProcess(void *lpVACBlob, uint32 cbBlobSize, const char *lpApplicationName, const char *lpCommandLine, uint32 dwCreationFlags, const char *lpCurrentDirectory, void* gameID, AppId_t nAppID, const char *pchGameName, uint32 uUnk) = 0;

		virtual uint32 GetAppOwnershipTicketLength(uint32 nAppID) = 0;
		virtual uint32 GetAppOwnershipTicketData(uint32 nAppID, void *pvBuffer, uint32 cbBufferLength) = 0;

		virtual uint32 GetAppOwnershipTicketExtendedData(uint32 nAppID, void *pvBuffer, uint32 cbBufferLength, uint32* piAppId, uint32* piSteamId, uint32* piSignature, uint32* pcbSignature) = 0;

		virtual int32 GetMarketingMessageCount() = 0;
		virtual bool GetMarketingMessage(int32 cMarketingMessage, void* gidMarketingMessageID, char* pubMsgUrl, int32 cubMessageUrl, void *eMarketingMssageFlags) = 0;

		virtual HAuthTicket GetAuthSessionTicket(void *pMyAuthTicket, int32 cbMaxMyAuthTicket, uint32* pcbAuthTicket) = 0;

		virtual EBeginAuthSessionResult BeginAuthSession(void const* pTheirAuthTicket, int32 cbTicket, CSteamID steamID) = 0;
		virtual void EndAuthSession(CSteamID steamID) = 0;

		virtual void CancelAuthTicket(HAuthTicket hAuthTicket) = 0;

		virtual EUserHasLicenseForAppResult IsUserSubscribedAppInTicket(CSteamID steamID, AppId_t appID) = 0;

		virtual void AdvertiseGame(void* gameID, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer) = 0;

		virtual SteamAPICall_t RequestEncryptedAppTicket(const void *pUserData, int32 cbUserData) = 0;
		virtual bool GetEncryptedAppTicket(void *pTicket, int32 cbMaxTicket, uint32 *pcbTicket) = 0;

		virtual int32 GetGameBadgeLevel(int32 nSeries, bool bFoil) = 0;
		virtual int32 GetPlayerSteamLevel() = 0;

		virtual void SetAccountLimited(bool bAccountLimited) = 0;
		virtual bool BIsAccountLimited() = 0;

		virtual void SetAccountCommunityBanned(bool bBanned) = 0;
		virtual bool BIsAccountCommunityBanned() = 0;

		virtual void SetLimitedAccountCanInviteFriends(bool bCanInviteFriends) = 0;
		virtual bool BLimitedAccountCanInviteFriends() = 0;

		virtual void SendValidationEmail() = 0;
		virtual bool BGameConnectTokensAvailable() = 0;

		virtual int32 NumGamesRunning() = 0;
		virtual void* GetRunningGameID(int32 iGame) = 0;

		virtual uint32 GetAccountSecurityPolicyFlags() = 0;

		virtual void RequestChangeEmail(const char *pchPassword, int32 eRequestType) = 0;
		virtual void ChangePasswordWithCode(const char *pchOldPassword, const char *pchCode, const char *pchNewPassword) = 0;
		virtual void ChangeEmailWithCode(const char *pchPassword, const char *pchCode, const char *pchEmail, bool bFinal) = 0;
		virtual void ChangeSecretQuestionAndAnswerWithCode(const char *pchPassword, const char *pchCode, const char *pchNewQuestion, const char *pchNewAnswer) = 0;

		virtual void SetClientStat(int eStat, int llValue, AppId_t nAppID, int nDepotID, CellID_t nCellID) = 0;

		virtual void VerifyPassword(const char *pchPassword) = 0;

		virtual bool BSupportUser() = 0;

	};
	class IClientEngine
	{
	public:
		virtual HSteamPipe CreateSteamPipe() = 0;
		virtual bool BReleaseSteamPipe(HSteamPipe hSteamPipe) = 0;

		virtual HSteamUser CreateGlobalUser(HSteamPipe* phSteamPipe) = 0;
		virtual HSteamUser ConnectToGlobalUser(HSteamPipe hSteamPipe) = 0;

		virtual HSteamUser CreateLocalUser(HSteamPipe* phSteamPipe, int eAccountType) = 0;
		virtual void CreatePipeToLocalUser(HSteamUser hSteamUser, HSteamPipe* phSteamPipe) = 0;

		virtual void ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser) = 0;

		virtual bool IsValidHSteamUserPipe(HSteamPipe hSteamPipe, HSteamUser hUser) = 0;

		virtual IClientUser *GetIClientUser(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion) = 0;
		virtual ISteamGameServer *GetIClientGameServer(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

		/*void * GetNetworking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion)
		{
		typedef void*(__thiscall* getNetwork)(PVOID, HSteamUser, HSteamPipe, char const*);
		return call_vfunc< getNetwork >(this, 22)(this, hSteamUser, hSteamPipe, pchVersion);
		}*/

		virtual void SetLocalIPBinding(uint32 unIP, uint16 usPort) = 0;
		virtual char const *GetUniverseName(EUniverse eUniverse) = 0;

		virtual void *GetIClientFriends(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion) = 0;
		virtual void *GetIClientUtils(HSteamPipe hSteamPipe, char const* pchVersion) = 0;
		virtual void *GetIClientBilling(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion) = 0;
		virtual void *GetIClientMatchmaking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion) = 0;
		virtual void *GetIClientApps(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion) = 0;
		virtual void *GetIClientMatchmakingServers(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion) = 0;

		virtual void RunFrame() = 0;
		virtual uint32 GetIPCCallCount() = 0;

		virtual void *GetIClientUserStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, char const* pchVersion) = 0;
	};
	IClientEngine* g_pClientEngine = NULL;


	class ISteamClient012
	{
	public:
		virtual HSteamPipe CreateSteamPipe() = 0;

		// Releases a previously created communications pipe
		virtual bool BReleaseSteamPipe(HSteamPipe hSteamPipe) = 0;

		// connects to an existing global user, failing if none exists
		// used by the game to coordinate with the steamUI
		virtual HSteamUser ConnectToGlobalUser(HSteamPipe hSteamPipe) = 0;

		// used by game servers, create a steam user that won't be shared with anyone else
		virtual HSteamUser CreateLocalUser() = 0;

		// removes an allocated user
		virtual void ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser) = 0;

		// retrieves the ISteamUser interface associated with the handle
		virtual void *GetISteamUser(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

		// retrieves the ISteamGameServer interface associated with the handle
		virtual ISteamGameServer *GetISteamGameServer(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
	};



	// Asserts steamID type before conversion
	CSteamID ChatIDFromClanID(const CSteamID &steamIDClan);
	// Asserts steamID type before conversion
	CSteamID ClanIDFromChatID(const CSteamID &steamIDChat);

	namespace STEAM
	{
		extern IClientUser *pClientUser;
	}

}