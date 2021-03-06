#pragma once
#define MULTIPLAYER_BACKUP 150
class bf_write;
class bf_read;

class CInput
{
public:
	void* pvftable; //0x00
	char m_pad001[0x8]; //add this padding
	bool m_fTrackIRAvailable;
	bool m_fMouseInitialized;
	bool m_fMouseActive;
	bool m_fJoystickAdvancedInit;
	char pad_0x08[0x2C];
	void* m_pKeys;
	char pad_0x38[0x64];
	int pad_0x41;
	int pad_0x42;
	bool m_fCameraInterceptingMouse;
	bool m_fCameraInThirdPerson;
	bool m_fCameraMovingWithMouse;
	Vector3 m_vecCameraOffset;
	bool m_fCameraDistanceMove;
	int m_nCameraOldX;
	int m_nCameraOldY;
	int m_nCameraX;
	int m_nCameraY;
	bool m_CameraIsOrthographic;
	Vector3 m_angPreviousViewAngles;
	Vector3 m_angPreviousViewAnglesTilt;
	float m_flLastForwardMove;
	int m_nClearInputState;
	char pad_0xE4[0x8];
	CUserCmd* m_pCommands;
	CVerifiedUserCmd* m_pVerifiedCommands;
	CVerifiedUserCmd * GetVerifiedCmd(int sequence_number)
	{
		return &m_pVerifiedCommands[sequence_number % 64];
	}

	CUserCmd* GetUserCmd(int sequence_number)
	{
		return &m_pCommands[sequence_number % 64];
	}
};


CInput* g_pCInput;