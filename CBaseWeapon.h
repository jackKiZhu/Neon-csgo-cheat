#pragma once

class CCSWeaponInfo_t
{
public:
	void* vftbl;
	char* consoleName;                   // 0x0004
	char pad_0008[12];                   // 0x0008
	int iMaxClip1;                       // 0x0014
	int iMaxClip2;                       // 0x0018
	int iDefaultClip1;                   // 0x001C
	int iDefaultClip2;                   // 0x0020
	char pad_0024[8];                    // 0x0024
	char* szWorldModel;                  // 0x002C
	char* szViewModel;                   // 0x0030
	char* szDroppedModel;                // 0x0034
	char pad_0038[4];                    // 0x0038
	char* N0000023E;                     // 0x003C
	char pad_0040[60];                   // 0x0040
	char* szEmptySound;                  // 0x0078
	char pad_007C[4];                    // 0x007C
	char* szBulletType;                  // 0x0080
	char pad_0084[4];                    // 0x0084
	char* szHudName;                     // 0x0088
	char* szWeaponName;                  // 0x008C
	char pad_0090[52];                   // 0x0090
	int WeaponType;                      // 0x00C8
	int WeaponPad;                       // 0x0CC
	int iWeaponPrice;                    // 0x00D0
	int iKillAward;                      // 0x00D4
	char* szAnimationPrefix;             // 0x00D8
	float flCycleTime;                   // 0x00DC
	float flCycleTimeAlt;                // 0x00E0
	float flTimeToIdle;                  // 0x00E4
	float flIdleInterval;                // 0x00E8
	bool bFullAuto;                      // 0x00E9
	char pad_0x00EC[3];                  // 0x00EC
	int iDamage;                         // 0x00F0
	float flArmorRatio;                  // 0x00F4
	int iBullets;                        // 0x00F8
	float flPenetration;                 // 0x00FC
	float flFlinchVelocityModifierLarge; // 0x0100
	float flFlinchVelocityModifierSmall; // 0x0104
	float flRange;                       // 0x0108
	float flRangeModifier;               // 0x010C
	float flThrowVelocity;               // 0x0110
	char pad_0x010C[12];                 // 0x011C
	bool bHasSilencer;                   // 0x011D
	char pad_0x0119[3];                  // 0x0120
	char* pSilencerModel;                // 0x0124
	int iCrosshairMinDistance;           // 0x0128
	int iCrosshairDeltaDistance;         // 0x012C - iTeam?
	float flMaxPlayerSpeed;              // 0x0130
	float flMaxPlayerSpeedAlt;           // 0x0134
	float flSpread;                      // 0x0134
	float flSpreadAlt;                   // 0x0138
	float flInaccuracyCrouch;            // 0x013C
	float flInaccuracyCrouchAlt;         // 0x0140
	float flInaccuracyStand;             // 0x0144
	float flInaccuracyStandAlt;          // 0x0148
	float flInaccuracyJumpInitial;       // 0x014C
	float flInaccuracyJump;              // 0x0150
	float flInaccuracyJumpAlt;           // 0x0154
	float flInaccuracyLand;              // 0x0158
	float flInaccuracyLandAlt;           // 0x015C
	float flInaccuracyLadder;            // 0x0160
	float flInaccuracyLadderAlt;         // 0x0164
	float flInaccuracyFire;              // 0x0168
	float flInaccuracyFireAlt;           // 0x016C
	float flInaccuracyMove;              // 0x0170
	float flInaccuracyMoveAlt;           // 0x0174
	float flInaccuracyReload;            // 0x0178
	int iRecoilSeed;                     // 0x017C
	float flRecoilAngle;                 // 0x0180
	float flRecoilAngleAlt;              // 0x0184
	float flRecoilAngleVariance;         // 0x0188
	float flRecoilAngleVarianceAlt;      // 0x018C
	float flRecoilMagnitude;             // 0x0190
	float flRecoilMagnitudeAlt;          // 0x0194
	float flRecoilMagnitudeVariance;     // 0x0198
	float flRecoilMagnitudeVarianceAlt;  // 0x019C
	float flRecoveryTimeCrouch;          // 0x01A0
	float flRecoveryTimeStand;           // 0x01A4
	float flRecoveryTimeCrouchFinal;     // 0x01A8
	float flRecoveryTimeStandFinal;      // 0x01AC
	int iRecoveryTransitionStartBullet;  // 0x01B0
	int iRecoveryTransitionEndBullet;    // 0x01B4
	bool bUnzoomAfterShot;               // 0x01B8
	bool bHideViewModelZoomed;           // 0x01B9
	char pad_0x01B5[2];                  // 0x01BA
	char iZoomLevels[4];                 // 0x01BC
	int iZoomFOV[2];                     // 0x01C0
	float fZoomTime[3];                  // 0x01C4
	char* szWeaponClass;                 // 0x01D4
	float flAddonScale;                  // 0x01D8
	char pad_0x01DC[4];                  // 0x01DC
	char* szEjectBrassEffect;            // 0x01E0
	char* szTracerEffect;                // 0x01E4
	int iTracerFrequency;                // 0x01E8
	int iTracerFrequencyAlt;             // 0x01EC
	char* szMuzzleFlashEffect_1stPerson; // 0x01F0
	char pad_0x01F4[4];                  // 0x01F4
	char* szMuzzleFlashEffect_3rdPerson; // 0x01F8
	char pad_0x01FC[4];                  // 0x01FC
	char* szMuzzleSmokeEffect;           // 0x0200
	float flHeatPerShot;                 // 0x0204
	char* szZoomInSound;                 // 0x0208
	char* szZoomOutSound;                // 0x020C
	float flInaccuracyPitchShift;        // 0x0210
	float flInaccuracySoundThreshold;    // 0x0214
	float flBotAudibleRange;             // 0x0218
	char pad_0x0218[8];                  // 0x0220
	char* pWrongTeamMsg;                 // 0x0224
	bool bHasBurstMode;                  // 0x0228
	char pad_0x0225[3];                  // 0x0229
	bool bIsRevolver;                    // 0x022C
	bool bCannotShootUnderwater;         // 0x0230
};

/*class CCSWeaponInfo_t
{
public:
	BYTE pad_0x0000[4]; //0x0000
	bool m_bParsedScript; //0x0004
	bool m_bLoadedHudElements; //0x0005
	char m_szClassName[80]; //0x0006
	char m_szPrintName[80]; //0x0056
	char m_szViewModel[80]; //0x00A6
	char m_szWorldModel[80]; //0x00F6
	char m_szBulletType[32]; //0x0146
	char m_szWorldDroppedModel[80];//0x0166
	char m_szAnimationPrefix[16]; //0x01B6
	BYTE m_pad_0x01C6[2]; //0x01C6
	int m_iSlot; //0x01C8
	int m_iPosition; //0x01CC
	int m_iMaxClip1; //0x01D0
	int m_iMaxClip2; //0x01D4
	int m_iDefaultClip1; //0x01D8
	int m_iDefaultClip2; //0x01DC
	int m_iWeight; //0x01E0
	int m_iRumbleEffect; //0x01E4
	bool m_bAutoSwitchTo; //0x01E8
	bool m_bAutoSwitchFrom; //0x01E9
	BYTE m_pad_0x01EA[2]; //0x01EA
	int m_iFlags; //0x01EC
	char m_szAmmo1[16]; //0x01F0
	char m_szAmmo2[16]; //0x0200
	char m_szAIAddOn[80]; //0x0210
	char m_aShootSounds[17][80]; //0x0260
	char PAD_NEW[80];
	int m_iAmmoType;
	int m_iAmmo2Type;
	bool m_bMeleeWeapon;
	bool m_bBuiltRightHanded;
	bool m_bAllowFlipping;
	BYTE pad_0x07BB;
	int m_iSpriteCount;
	void* iconWeaponS;
	void* iconWeapon;
	void* iconAmmo;
	void* iconAmmo2;
	void* iconCrosshair;
	void* iconAutoaim;
	void* iconZoomedCrosshair;
	void* iconZoomedAutoaim;
	void* iconWeaponSmall;
	bool m_bShowUsageHint;
	BYTE pad_0x07E5[3];
	int m_iWeaponType;
	int m_iTeam;
	int m_iWeaponID;
	bool m_bFullAuto;
	BYTE pad_0x07F5[3];
	float m_flHeatPerShot;
	int m_iWeaponPrice;
	float m_flArmorRatio;
	float m_flMaxPlayerSpeed;
	float m_flMaxPlayerSpeedAlt;
	int m_iCrosshairMinDistance;
	int m_iCrosshairDeltaDistance;
	float m_flPenetration;
	int m_iDamage;
	float m_flRange;
	float m_flRangeModifier;
	int m_iBullets;
	float m_flCycleTime;
	float m_flCycleTimeAlt;
	char m_szHeatEffect[80];
	float m_aflSmokeColor[3];
	char m_szMuzzleFlashEffect_1stPerson[80];
	char m_szMuzzleFlashEffect_3rdPerson[80];
	char m_szEjectBrassEffect[80];
	char m_szTracerEffect[80];
	int m_iTracerFrequency;
	float m_flSpread;
	float m_flSpreadAlt;
	float m_flInaccuracyCrouch;
	float m_flInaccuracyCrouchAlt;
	float m_flInaccuracyStand;
	float m_flInaccuracyStandAlt;
	float m_flInaccuracyJump;
	float m_flInaccuracyJumpAlt;
	float m_flInaccuracyLand;
	float m_flInaccuracyLandAlt;
	float m_flInaccuracyLadder;
	float m_flInaccuracyLadderAlt;
	float m_flInaccuracyFire;
	float m_flInaccuracyFireAlt;
	float m_flInaccuracyMove;
	float m_flInaccuracyMoveAlt;
	float m_flRecoveryTimeStand;
	float m_flRecoveryTimeCrouch;
	float m_flInaccuracyReload;
	float m_fl
	AltSwitch;
	float m_flRecoilAngle;
	float m_flRecoilAngleAlt;
	float m_flRecoilAngleVariance;
	float m_flRecoilAngleVarianceAlt;
	float m_flRecoilMagnitude;
	float m_flRecoilMagnitudeAlt;
	float m_flRecoilMagnitudeVariance;
	float m_flRecoilMagnitudeVarianceAlt;
	int m_iRecoilSeed;
	float m_flFlinchVelocityModifierLarge;
	float m_flFlinchVelocityModifierSmall;
	float m_flTimeToIdle;
	float m_flIdleInterval;
	float m_recoilTable[2][128];
	int m_iZoomLevels;
	int m_iZoomFOV[3];
	float m_fZoomTime[3];
	bool m_bHideViewModelZoomed;
	char m_szZoomInSound[80];
	char m_szZoomOutSound[80];
	BYTE m_pad_0x0F11[3];
	float m_flBotAudibleRange;
	bool m_bCanUseWithShield;
	char m_szWrongTeamMsg[32];
	char m_szAnimPrefix[16];
	char m_szShieldViewModel[64];
	char m_szAddonModel[80];
	char m_szAddonLocation[80];
	char m_szSilencerModel[80];
	BYTE pad_0x1079[3];
	float m_flAddonScale;
	float m_flThrowVelocity;
	int m_iKillAward;
	BYTE pad_0x1088[8];
};*/

class C_BaseWeapon : IClientEntity
{
public:
	float NextPrimaryAttack()
	{
		return *(float*)((DWORD)this + NetVarManager::GetOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack"));
	}

	bool InReload()
	{
		return *(bool*)((DWORD)this + 0x3285);
	}

	float PostponeFireReadyTime()
	{
		return *(float*)((DWORD)this + NetVarManager::GetOffset("DT_WeaponCSBaseGun", "m_flPostponeFireReadyTime"));
	}

	float ThrowTime()
	{
		return *(float*)((DWORD)this + NetVarManager::GetOffset("DT_BaseCSGrenade", "m_fThrowTime"));
	}

	float NextSecondaryAttack()
	{
		return *(float*)((DWORD)this + NetVarManager::GetOffset("DT_BaseCombatWeapon", "m_flNextSecondaryAttack"));
	}

	int ClipAmmo()
	{
		return *(int*)((DWORD)this + NetVarManager::GetOffset("DT_BaseCombatWeapon", "m_iClip1"));
	}

	int ClipAmmo2()
	{
		return *(int*)((DWORD)this + NetVarManager::GetOffset("DT_BaseCombatWeapon", "m_iClip2"));
	}

	int PrimaryReserveAmmoCount()
	{
		return *(int*)((DWORD)this + NetVarManager::GetOffset("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount"));
	}

	int ZoomLvl()
	{
		static auto lol = NetVarManager::GetOffset("DT_WeaponCSBaseGun", "m_zoomLevel");
		return *(int*)((DWORD)this + lol);
	}

	int ShotsFired()
	{
		return 1;
	}

	CCSWeaponInfo_t* GetWpnData();

	bool m_bPinPulled() {
		static auto a = NetVarManager::GetOffset("DT_BaseCSGrenade", "m_bPinPulled");
		return *(bool*)((DWORD)this + a);
	}

	float_t m_fThrowTime() {
		static auto a = NetVarManager::GetOffset("DT_BaseCSGrenade", "m_fThrowTime");
		return *(float_t*)((DWORD)this + a);
	}

	void UpdateAccuracyPenalty()
	{
		typedef void(__thiscall *OriginalFn)(void*);
		return CallVFunc<OriginalFn>(this, 483)(this);
	}

	float GetAccuracyPenalty()
	{
		typedef float(__thiscall* OriginalFn)(void*);
		return CallVFunc<OriginalFn>(this, 482)(this);
	}

	float GetWeaponSpread()
	{
		typedef float(__thiscall* OriginalFn)(void*);
		return CallVFunc<OriginalFn>(this, 452)(this);
	}
	short GetItemDefinitionIndex5() {
		return *(short*)((DWORD)this + /*NetVarManager::GetOffset("DT_BaseAttributableItem", "m_iItemDefinitionIndex")*/0x2FAA);
	}
	ItemDefinitionIndex GetItemDefinitionIndex() {
		return *(short*)((DWORD)this + /*NetVarManager::GetOffset("DT_BaseAttributableItem", "m_iItemDefinitionIndex")*/0x2FAA);
	}
};
