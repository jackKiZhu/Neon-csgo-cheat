#pragma once
#include "AnimationLayers.h"
#include <../VMProtectSDK/VMProtectSDK.h>
#define CS_TEAM_CT 3
#define CS_TEAM_TT 2
char init2[10] = "huihuihui";
char init3[14] = "00123456layer";
class C_BasePlayer;
class CBaseAnimState
{
public:
	char pad[3];
	char bUnknown; //0x4
	char pad2[91];
	C_BasePlayer* pBaseEntity; //0x60
	void* pActiveWeapon; //0x64
	void* pLastActiveWeapon; //0x68
	float m_flLastClientSideAnimationUpdateTime; //0x6C
	int m_iLastClientSideAnimationUpdateFramecount; //0x70
	float m_flEyePitch; //0x74
	float m_flEyeYaw; //0x78
	float m_flPitch; //0x7C
	float m_flGoalFeetYaw; //0x80
	float m_flCurrentFeetYaw; //0x84
	float m_flCurrentTorsoYaw; //0x88
	float m_flUnknownVelocityLean; //0x8C //changes when moving/jumping/hitting ground
	float m_flLeanAmount; //0x90
	char pad4[4]; //NaN
	float m_flFeetCycle; //0x98 0 to 1
	float m_flFeetYawRate; //0x9C 0 to 1
	float m_fUnknown2;
	float m_fDuckAmount; //0xA4
	float m_fLandingDuckAdditiveSomething; //0xA8
	float m_fUnknown3; //0xAC
	Vector3 m_vOrigin; //0xB0, 0xB4, 0xB8
	Vector3 m_vLastOrigin; //0xBC, 0xC0, 0xC4
	float m_vVelocityX; //0xC8
	float m_vVelocityY; //0xCC
	char pad5[4];
	float m_flUnknownFloat1; //0xD4 Affected by movement and direction
	char pad6[8];
	float m_flUnknownFloat2; //0xE0 //from -1 to 1 when moving and affected by direction
	float m_flUnknownFloat3; //0xE4 //from -1 to 1 when moving and affected by direction
	float m_unknown; //0xE8
	float speed_2d; //0xEC
	float flUpVelocity; //0xF0
	float m_flSpeedNormalized; //0xF4 //from 0 to 1
	float m_flFeetSpeedForwardsOrSideWays; //0xF8 //from 0 to 2. something  is 1 when walking, 2.something when running, 0.653 when crouch walking
	float m_flFeetSpeedUnknownForwardOrSideways; //0xFC //from 0 to 3. something
	float m_flTimeSinceStartedMoving; //0x100
	float m_flTimeSinceStoppedMoving; //0x104
	unsigned char m_bOnGround; //0x108
	unsigned char m_bInHitGroundAnimation; //0x109
	char pad7[10];
	float m_flLastOriginZ; //0x114
	float m_flHeadHeightOrOffsetFromHittingGroundAnimation; //0x118 from 0 to 1, is 1 when standing
	float m_flStopToFullRunningFraction; //0x11C from 0 to 1, doesnt change when walking or crouching, only running
	char pad8[4]; //NaN
	float m_flUnknownFraction; //0x124 affected while jumping and running, or when just jumping, 0 to 1
	char pad9[4]; //NaN
	float m_flUnknown3;
	char pad10[528]; //0x0120
	float m_flMinBodyYawDegrees; //0x0330
	float m_flMaxBodyYawDegrees; //0x0334
};

class C_BasePlayer : public IClientEntity
{
public:
	static C_BasePlayer* LocalPlayer( ) {
		return g_pEntityList->GetClientEntity<C_BasePlayer>( g_pEngine->GetLocalPlayer( ) );
	}

	int Flags( ) {
		static auto m_flags = NetVarManager::GetOffset( "DT_BasePlayer", "m_fFlags" );
		return *( int* )( ( DWORD )this + m_flags );
	}


	int* GetWeapons( ) {
		static auto m_hMyWeapons = NetVarManager::GetOffset("DT_BaseCombatCharacter", "m_hMyWeapons");
		return reinterpret_cast< int* >( uintptr_t( this ) + m_hMyWeapons);
	}
	Vector3& GetAbsOrigin( ) {
		typedef Vector3& ( __thiscall* OriginalFn )( void* );
		return ( ( OriginalFn )CallVFunc<OriginalFn>( this, 10 ) )( this );
	}
	int MoveType( ) {
		return *( int* )( ( DWORD )this + 0x25C );
	}

	bool ValidMoveType( ) {
		return	MoveType( ) != MOVETYPE_LADDER &&
			MoveType( ) != MOVETYPE_NOCLIP;
	}

	DWORD GetObserverTargetHandle( ) {
		if( !this )
			return NULL;
		static auto a = NetVarManager::GetOffset( "DT_BasePlayer", "m_hObserverTarget" );
		return *( DWORD* )( ( DWORD )this + a );
	}

	int Health() {
	//	VMProtectBeginUltra("qw");
		//static auto a = NetVarManager::GetOffset(init3, init2);
	//		VMProtectEnd();
	
		static auto a = NetVarManager::GetOffset("DT_BasePlayer", "m_iHealth");
		return *(int*)((DWORD)this + a);

	}

	CBaseAnimState* GetAnimState();
	float GetMaxDesyncDelta();


	float* m_flCustomBloomScale()
	{
		static int m_flCustomBloomScale_ = NetVarManager::GetOffset("DT_EnvTonemapController", "m_flCustomBloomScale");
		return (float*)((DWORD)this + m_flCustomBloomScale_);
	}

	unsigned char* UseCustomExposureMin()
	{
		static int m_bUseCustomAutoExposureMin = NetVarManager::GetOffset("DT_EnvTonemapController", "m_bUseCustomAutoExposureMin");
		return (unsigned char*)((DWORD)this + m_bUseCustomAutoExposureMin);
	}

	unsigned char* UseCustomExposureMax()
	{
		static int m_bUseCustomAutoExposureMax = NetVarManager::GetOffset("DT_EnvTonemapController", "m_bUseCustomAutoExposureMax");
		return (unsigned char*)((DWORD)this + m_bUseCustomAutoExposureMax);
	}

	float* CustomExposureMin()
	{
		static int m_flCustomAutoExposureMin = NetVarManager::GetOffset("DT_EnvTonemapController", "m_flCustomAutoExposureMin");
		return (float*)((DWORD)this + m_flCustomAutoExposureMin);
	}

	float* CustomExposureMax()
	{
		static int m_flCustomAutoExposureMax = NetVarManager::GetOffset("DT_EnvTonemapController", "m_flCustomAutoExposureMax");
		return (float*)((DWORD)this + m_flCustomAutoExposureMax);
	}


	void set_m_bUseCustomBloomScale(bool value)
	{
		static int m_bUseCustomBloomScale = NetVarManager::GetOffset("DT_EnvTonemapController", "m_bUseCustomBloomScale");
		*reinterpret_cast<unsigned char*>(uintptr_t(this) + m_bUseCustomBloomScale) = value;
	}



	void set_m_flCustomBloomScale(float value)
	{
		static int m_flCustomBloomScale = NetVarManager::GetOffset("DT_EnvTonemapController", "m_flCustomBloomScale");
		*reinterpret_cast<float*>(uintptr_t(this) + m_flCustomBloomScale) = value;
	}



	int MaxHealth( ) {
		static auto a = NetVarManager::GetOffset( "DT_CHostage", "m_iMaxHealth" );
		return *( int* )( ( DWORD )this + a );
	}

	int Armor( ) {
		return *( int* )( ( DWORD )this + /*NetVarManager::GetOffset("DT_CSPlayer", "m_ArmorValue")*/0xB324 );
	}

	bool HasHelmet( ) {
		static auto a = NetVarManager::GetOffset( "DT_CSPlayer", "m_bHasHelmet" );
		return *( bool* )( ( DWORD )this + a );
	}

#define CS_TEAM_TT 2
#define CS_TEAM_CT 3
	int Team( ) {
		return *( int* )( ( DWORD )this + /*NetVarManager::GetOffset("DT_CSPlayer", "m_iTeamNum")*/0xF4 );
	}

	bool IsNotTarget();

	IClientEntity* ViewModel( ) {
		static auto a = NetVarManager::GetOffset( "DT_CSPlayer", "m_hViewModel[0]" );
		return g_pEntityList->GetClientEntityFromHandle( *( DWORD* )( ( DWORD )this + a ) );
	}

	Vector3 Velocity( ) {
		static auto a = NetVarManager::GetOffset( "DT_BasePlayer", "m_vecVelocity[0]" );
		return *( Vector3* )( ( DWORD )this + a );
	}

	QAngle* PunchAnglesPtr( ) {
		static auto a = NetVarManager::GetOffset( "DT_BasePlayer", "m_aimPunchAngle" );
		return ( QAngle* )( ( DWORD )this + a );
	}

	QAngle* ViewPunchAnglesPtr( ) {
		static auto a = NetVarManager::GetOffset( "DT_BasePlayer", "m_viewPunchAngle" );
		return ( QAngle* )( ( DWORD )this + a );
	}

	QAngle PunchAngles( ) {
		return *PunchAnglesPtr( );
	}

	QAngle ViewPunchAngles( ) {
		return *ViewPunchAnglesPtr( );
	}

	Vector3 ViewOffset( ) {
		static auto a = NetVarManager::GetOffset( "DT_BasePlayer", "m_vecViewOffset[0]" );
		return *( Vector3* )( ( DWORD )this + a );
	}

	Vector3 EyePosition( ) {
		return ViewOffset( ) + GetOrigin( );
	}

	int Money( ) {
		static auto a = NetVarManager::GetOffset( "DT_CSPlayer", "m_iAccount" );
		return *( int* )( ( DWORD )this + a );
	}

	float MaxSpeed( ) {
		static auto a = NetVarManager::GetOffset( "DT_BasePlayer", "m_flMaxspeed" );
		return *( float* )( ( DWORD )this + a );
	}

	bool IsControllingBot( ) {
		static auto a = NetVarManager::GetOffset( "DT_CSPlayer", "m_bIsControllingBot" );
		return *( bool* )( ( DWORD )this + a );
	}

	int FOV( ) {
		static auto a = NetVarManager::GetOffset( "DT_BasePlayer", "m_iFOV" );
		return *( int* )( ( DWORD )this + a );
	}

	int DefaultFOV( ) {
		static auto a = NetVarManager::GetOffset( "DT_BasePlayer", "m_iDefaultFOV" );
		return *( int* )( ( DWORD )this + a );
	}

	bool HasHeavyArmor( ) {
		static auto a = NetVarManager::GetOffset( "DT_CSPlayer", "m_bHasHeavyArmor" );
		return *( int* )( ( DWORD )this + a );
	}

	int ArmorValue( ) {
		static auto a = NetVarManager::GetOffset( "DT_CSPlayer", "m_ArmorValue" );
		return *( int* )( ( DWORD )this + a );
	}

	int index() {
		return *(int*)((DWORD)this + 0x64);
	}

	bool FastSetupBones( ) {
		matrix3x4 matrix[128];
		return FastSetupBones( matrix );
	}

	bool FastSetupBones( matrix3x4* matrix ) {
	//	*( int* )( ( DWORD )this + 0xA30 ) = g_pGlobals->framecount; //we'll skip occlusion checks now
	//	*( int* )( ( DWORD )this + 0xA28 ) = 0; //clear occlusion flags

		return this->SetupBones( matrix, 128, 0x100, 0 );
	}

	int HitboxSet( ) {
		static auto a = NetVarManager::GetOffset( "DT_BaseAnimating", "m_nHitboxSet" );
		return *( int* )( ( DWORD )this + a );
	}

	Vector3 BonePosition( int bone ) {
		matrix3x4 matrix[128];

		if( !FastSetupBones( matrix ) )
			return Vector3( );

		return Vector3( matrix[bone][0][3], matrix[bone][1][3], matrix[bone][2][3] );
	}

	Vector3 HitboxPosition( int hitbox ) {
		model_t* model = this->GetModel( );
		if( !model )
			return VECNULL;

		studiohdr_t* hdr = g_pModelInfo->GetStudioModel( model );
		if( !hdr )
			return VECNULL;

		matrix3x4 matrix[128];
		if( !FastSetupBones( matrix ) )
			return VECNULL;

		mstudiohitboxset_t *set = hdr->pHitboxSet( HitboxSet( ) );
		if( !set )
			return VECNULL;

		mstudiobbox_t* box = set->pHitbox( hitbox );
		if( !box )
			return VECNULL;

		Vector3 center = ( ( box->bbmin + box->bbmax ) * .5f );

		Vector3 hitboxpos;

		for( auto i = 0; i < 3; i++ )
			hitboxpos[i] = center.Dot( ( Vector3& )matrix[box->bone][i] ) + matrix[box->bone][i][3];

		return hitboxpos;
	}

	model_t* GetPlayerModel( ) {
		return *( model_t** )( ( DWORD )this + 0x6C );
	}

	bool Dormant( ) {
		return *( bool* )( ( DWORD )this + 0xED );
	}

	int ShotsFired( ) {
		static auto a = NetVarManager::GetOffset( "DT_CSPlayer", "m_iShotsFired" );
		return *( int* )( ( DWORD )this + a );
	}

	int TickBase( ) {
		static auto a = NetVarManager::GetOffset( "DT_BasePlayer", "m_nTickBase" );
		return *( int* )( ( DWORD )this + a );
	}


	C_BaseWeapon* Weapon( ) {
		static auto  a = NetVarManager::GetOffset( "DT_BaseCombatCharacter", "m_hActiveWeapon" );
		UINT* hWeapon = *( UINT** )( ( DWORD )this + a );
		return ( C_BaseWeapon* )g_pEntityList->GetClientEntityFromHandle( ( DWORD )hWeapon );
	}

	int* Weapons( ) {
		static auto a = NetVarManager::GetOffset( "DT_BaseCombatCharacter", "m_hMyWeapons" );
		return reinterpret_cast< int* >( uintptr_t( this ) + a );
	}

	int* Wearables( ) {
		static auto a = NetVarManager::GetOffset( "DT_BaseCombatCharacter", "m_hMyWearables" );
		return reinterpret_cast< int* >( uintptr_t( this ) + a );
	}

	bool Scoped( ) {
		static auto a = NetVarManager::GetOffset( "DT_CSPlayer", "m_bIsScoped" );
		return *( bool* )( ( DWORD )this + a );
	}

	float FlashDuration( ) {
		static auto a = NetVarManager::GetOffset( "DT_CSPlayer", "m_flFlashDuration" );
		return *( float* )( ( DWORD )this + a );
	}

	float* FlashMaxAlphaPointer( ) {
		static auto a = NetVarManager::GetOffset( "DT_CSPlayer", "m_flFlashMaxAlpha" );
		return ( float* )( ( DWORD )this + a );
	}

	IClientEntity* ObserverTarget( ) {
		static auto a = NetVarManager::GetOffset( "DT_BasePlayer", "m_hObserverTarget" );
		DWORD hEntity = ( *( DWORD* )( ( DWORD )this + a ) );
		if( hEntity == INVALID_EHANDLE_INDEX )
			return NULL;

		return g_pEntityList->GetClientEntityFromHandle( hEntity );
		//return g_pEntityList->GetClientEntity<IClientEntity>(hEntity & 0xFFF);
	}

	float C_BasePlayer::NextAttack( ) {
		static auto a = NetVarManager::GetOffset( "DT_BaseCombatCharacter", "m_flNextAttack" );
		return *( float* )( ( DWORD )this + a );
	}

	float LowerBodyYaw( ) {
		static auto a = NetVarManager::GetOffset( "DT_CSPlayer", "m_flLowerBodyYawTarget" );
		return *( float* )( ( DWORD )this + a );
	}

	int Sequence( ) {
		static auto a = NetVarManager::GetOffset( "DT_BaseAnimating", "m_nSequence" );
		return *( int* )( ( DWORD )this + a );
	}

	QAngle* EyeAnglesPtr( ) {
		static auto a = NetVarManager::GetOffset( "DT_CSPlayer", "m_angEyeAngles[0]" );
		return ( QAngle* )( ( DWORD )this + a );
	}

	QAngle EyeAngles( ) {
		return *EyeAnglesPtr( );
	}

	float SimulationTime( ) {
		static auto a = NetVarManager::GetOffset( "DT_BaseEntity", "m_flSimulationTime" );
		return *( float* )( ( DWORD )this + a );
	}


	void InvalidateBoneCache();


	float Cycle( ) {
		static auto a = NetVarManager::GetOffset( "DT_BaseAnimating", "m_flCycle" );
		return *( float* )( ( DWORD )this + a );
	}

	int& GetBoneCount()
	{
		return *(int*)((uintptr_t)this + 0x2924 /*0x291C*/);
	}

	matrix3x4* dwBoneMatrixptr()
	{
		return *(matrix3x4**)((uintptr_t)this + 0x26A8); // m_CachedBoneData.Base()
	}
};
