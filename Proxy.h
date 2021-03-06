#pragma once
#define SEQUENCE_DEFAULT_DRAW 0
#define SEQUENCE_DEFAULT_IDLE1 1
#define SEQUENCE_DEFAULT_IDLE2 2
#define SEQUENCE_DEFAULT_LIGHT_MISS1 3
#define SEQUENCE_DEFAULT_LIGHT_MISS2 4
#define SEQUENCE_DEFAULT_HEAVY_MISS1 9
#define SEQUENCE_DEFAULT_HEAVY_HIT1 10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB 11
#define SEQUENCE_DEFAULT_LOOKAT01 12

#define SEQUENCE_BUTTERFLY_DRAW 0
#define SEQUENCE_BUTTERFLY_DRAW2 1
#define SEQUENCE_BUTTERFLY_LOOKAT01 13
#define SEQUENCE_BUTTERFLY_LOOKAT03 15

#define SEQUENCE_FALCHION_IDLE1 1
#define SEQUENCE_FALCHION_HEAVY_MISS1 8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP 9
#define SEQUENCE_FALCHION_LOOKAT01 12
#define SEQUENCE_FALCHION_LOOKAT02 13

#define SEQUENCE_DAGGERS_IDLE1 1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 12

#define SEQUENCE_BOWIE_IDLE1 1

inline const int RandomSequence(int low, int high) {
	return (rand() % (high - low + 1) + low);
}

RecvPropHook* SequenceHook = new RecvPropHook( );
void SequenceProxy(const CRecvProxyData *pDataConst, void *pStruct, void *pOut)
{
	CRecvProxyData* pData = const_cast< CRecvProxyData* >( pDataConst );
	IClientEntity* pViewModel = ( IClientEntity* )pStruct;

	if( pViewModel ) {
		IClientEntity* pOwnerEntity = g_pEntityList->GetClientEntityFromHandle( *( DWORD* )( ( DWORD )pViewModel + NetVarManager::GetOffset("DT_BaseViewModel", "m_hOwner") ) );

		if( pOwnerEntity && pOwnerEntity->GetIndex( ) == g_pEngine->GetLocalPlayer( ) ) {
			C_BasePlayer* pOwnerPlayer = ( C_BasePlayer* )pOwnerEntity;
			if( !pOwnerPlayer->IsControllingBot( ) ) {
				const char* szModel = g_pModelInfo->GetModelName( g_pModelInfo->GetModel( pViewModel->GetModelIndex( ) ) );
				//if( strstr( szModel, "knife" ) )
				//	szModel = g_pModelInfo->GetModelName( g_pModelInfo->GetModel( U::GetCurrentKnifeModel( C_BasePlayer::LocalPlayer( )->Team( ) == CS_TEAM_TT ? Options::SkinChanger::KnifeTT : Options::SkinChanger::KnifeCT ) ) );

				int m_nSequence = pData->m_Value.m_Int;
				if( !_strcmp( szModel, "models/weapons/v_knife_butterfly.mdl" ) ) {
					//// Fix animations for the Butterfly Knife.
					//switch( m_nSequence ) {
					//case SEQUENCE_DEFAULT_DRAW:
					//#if _DEBUG
					//	m_nSequence = SEQUENCE_BUTTERFLY_DRAW2; break;
					//#else
					//	m_nSequence = Math::RandomInt( SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2 ); break;
					//#endif
					//case SEQUENCE_DEFAULT_LOOKAT01:
					//	m_nSequence = Math::RandomInt( SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03 ); break;
					//default:
					//	m_nSequence++;
					//}
					switch (m_nSequence) {
					case SEQUENCE_DEFAULT_DRAW:
						m_nSequence = RandomSequence(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2); break;
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = RandomSequence(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03); break;
					default:
						m_nSequence++;
					}
				} else if( !_strcmp( szModel, "models/weapons/v_knife_falchion_advanced.mdl" ) ) {
					// Fix animations for the Falchion Knife.
					switch( m_nSequence ) {
					case SEQUENCE_DEFAULT_IDLE2:
						m_nSequence = SEQUENCE_FALCHION_IDLE1; break;
					case SEQUENCE_DEFAULT_HEAVY_MISS1:
						m_nSequence = Math::RandomInt( SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP ); break;
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = Math::RandomInt( 0, 100 ) < 90 ? SEQUENCE_FALCHION_LOOKAT01 : SEQUENCE_FALCHION_LOOKAT02; break;
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;
					default:
						m_nSequence--;
					}
				} else if( !_strcmp( szModel, "models/weapons/v_knife_push.mdl" ) ) {
					// Fix animations for the Shadow Daggers.
					switch( m_nSequence ) {
					case SEQUENCE_DEFAULT_IDLE2:
						m_nSequence = SEQUENCE_DAGGERS_IDLE1; break;
					case SEQUENCE_DEFAULT_LIGHT_MISS1:
					case SEQUENCE_DEFAULT_LIGHT_MISS2:
						m_nSequence = Math::RandomInt( SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5 ); break;
					case SEQUENCE_DEFAULT_HEAVY_MISS1:
						m_nSequence = Math::RandomInt( SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1 ); break;
					case SEQUENCE_DEFAULT_HEAVY_HIT1:
					case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence += 3; break;
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;
					default:
						m_nSequence += 2;
					}
				} else if( !_strcmp( szModel, "models/weapons/v_knife_survival_bowie.mdl" ) ) {
					// Fix animations for the Bowie Knife.
					switch( m_nSequence ) {
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;
					case SEQUENCE_DEFAULT_IDLE2:
						m_nSequence = SEQUENCE_BOWIE_IDLE1; break;
					default:
						m_nSequence--;
					}
				}
				else if (!_strcmp(szModel, "models/weapons/v_knife_ursus.mdl"))
				{
					switch (m_nSequence)
					{
					case SEQUENCE_DEFAULT_DRAW:
						m_nSequence = Math::RandomInt(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
						break;
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = Math::RandomInt(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
						break;
					default:
						m_nSequence++;
						break;
					}
				}
				else if (!_strcmp(szModel, "models/weapons/v_knife_stiletto.mdl"))
				{
					switch (m_nSequence)
					{
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = Math::RandomInt(12, 13);
						break;
					}
				}
				else if (!_strcmp(szModel, "models/weapons/v_knife_widowmaker.mdl"))
				{
					switch (m_nSequence)
					{
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = Math::RandomInt(14, 15);
						break;
					case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
						m_nSequence--;
						break;
					}
				}
				if (!_strcmp(szModel, "models/weapons/v_knife_canis.mdl") || !_strcmp(szModel, "models/weapons/v_knife_outdoor.mdl") || !_strcmp(szModel, "models/weapons/v_knife_cord.mdl") || !_strcmp(szModel, "models/weapons/v_knife_skeleton.mdl")) {
					
					switch (m_nSequence)
					{
					case SEQUENCE_DEFAULT_DRAW:
						m_nSequence = Math::RandomInt(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
						break;
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = Math::RandomInt(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
						break;
					default:
						m_nSequence++;
						break;
					}
				}
				pData->m_Value.m_Int = m_nSequence;
			}
		}
	}

	SequenceHook->GetOriginalFunction( )( pData, pStruct, pOut );
}
