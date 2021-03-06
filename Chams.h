#pragma once

struct CUSTOMVERTEX { FLOAT x, y, z, r, h, w; };
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_TEX1) 

bool g_bDrawDIP = false;
bool g_bDrawingPlayers = false;
RainbowColor m_clrHandsRainbow = RainbowColor();

typedef void(__thiscall* SceneEndFn)(void*);
SceneEndFn oSceneEnd;


void __fastcall Hooked_SceneEnd(void* thisptr, void* edx) {
	C_BasePlayer* pLocal = C_BasePlayer::LocalPlayer();
	/*if( Options::Visuals::Misc::ThirdPerson && pLocal ) {
		auto angles = pLocal->EyeAnglesPtr( );
		auto oAngles = *angles;
		*angles = CRagebot::SavedFakeAngle;
		pLocal->DrawModel( STUDIO_RENDER, 80 );
		*angles = oAngles;
	}*/

	oSceneEnd(thisptr);

	static auto m_pGlowManager = *reinterpret_cast<CGlowObjectManager * *>(U::FindPattern("client.dll", "Glowmanager", "0F 11 05 ? ? ? ? 83 C8 01") + 3);

	if (Options::Visuals::Misc::glow_alpha > 0 && pLocal && g_pEngine->IsConnected() && g_pEngine->IsInGame() && m_pGlowManager)
	{
		for (auto i = 0; i < m_pGlowManager->GetSize(); i++)
		{
			auto& glowObject = m_pGlowManager->m_GlowObjectDefinitions[i];
			auto entity = reinterpret_cast<C_BasePlayer*>(glowObject.m_pEntity);

			if (!entity)
				continue;

			if (glowObject.IsUnused())
				continue;

			if (!entity->GetClientClass() || entity->GetClientClass()->iClassID != class_ids::CCSPlayer)
				continue;

			bool is_local_player = entity == pLocal;
			//bool is_teammate = cheat::main::local->m_iTeamNum() == entity->m_iTeamNum() && !is_local_player;
			bool is_enemy = pLocal->Team() != entity->Team() || is_local_player;

			if (!is_enemy || is_local_player)
				continue;

			//if (is_local_player && SETTINGS::main_configs.glow_local_enabled)
			//{
			//	should_draw_glow = true;
			//	color = SETTINGS::main_configs.glow_local_color;
			//	style = SETTINGS::main_configs.glow_local_style;
			//	full_bloom = SETTINGS::main_configs.glow_local_fullbloom_enabled;
			//}

			//if (is_teammate && SETTINGS::main_configs.glow_team_enabled)
			//{
			//	should_draw_glow = true;
			//	color = SETTINGS::main_configs.glow_team_color;
			//	style = SETTINGS::main_configs.glow_team_style;
			//	full_bloom = SETTINGS::main_configs.glow_team_fullbloom_enabled;
			//}

			glowObject.m_nGlowStyle = Options::Visuals::Hands::GlowStyle;

			glowObject.m_bFullBloomRender = false;
			glowObject.m_flRed = Options::Visuals::Chams::GlowColor[0];
			glowObject.m_flGreen = Options::Visuals::Chams::GlowColor[1];
			glowObject.m_flBlue = Options::Visuals::Chams::GlowColor[2];
			glowObject.m_flAlpha = Options::Visuals::Misc::glow_alpha / 255.0f;
			glowObject.m_bRenderWhenOccluded = true;
			glowObject.m_bRenderWhenUnoccluded = false;
		}
	}


	/*if (!Options::Visuals::Chams::Enabled)
		return oSceneEnd(thisptr);

	g_bDrawingPlayers = true;
	for (int i = 1; i < g_pEngine->GetMaxClients(); ++i) {
		auto entity = g_pEntityList->GetClientEntity<C_BasePlayer>(i);
		if (!entity)
			continue;

		entity->FastSetupBones();
		entity->DrawModel(STUDIO_RENDER, 255);
	}
	g_bDrawingPlayers = false;*/
}



typedef void(__thiscall* DrawModelExecuteFn)(void*, IMatRenderContext* matctx, DrawModelState_t& state, ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld);
DrawModelExecuteFn oDrawModelExecute;
void DrawChams(const char* szModelName, int iEntity, void* thisptr, IMatRenderContext* matctx, DrawModelState_t& state, ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld) {
	if (Options::Visuals::Misc::StreamMode)
		return;

	if (g_pEngine->IsTakingScreenshot())
		return;

	auto pLocalPlayer = C_BasePlayer::LocalPlayer();

	if (!pLocalPlayer)
		return;

	if (strstr(szModelName, "models/player")) {

		C_BasePlayer* pBasePlayer = g_pEntityList->GetClientEntity<C_BasePlayer>(iEntity);
		if (!pBasePlayer)
			return;
		if (pBasePlayer->Dormant())
			return;
		if (pBasePlayer->Health() <= 0)
			return;
		if (pBasePlayer->Team() == pLocalPlayer->Team() && (pBasePlayer != pLocalPlayer) && Options::Visuals::Chams::EnemyOnly)
			return;

		if (Options::Visuals::Chams::BacktrackChams && g_Backtrack->data.count(pBasePlayer->GetIndex()) > 0) {

			static IMaterial* material = nullptr;

			switch (Options::Visuals::Chams::DesStyle) {
			case 0: material = Materials::ChamsNormalMaterial; break;
			case 1: material = Materials::ChamsFlatMaterial; break;
			case 2: material = Materials::ChamsWireframeMaterial; break;
			case 3: material = Materials::ChamsNormalMaterial; break;
			case 4: material = Materials::mettalic; break;
			}

			if (material) {
				auto& data = g_Backtrack->data.at(pBasePlayer->GetIndex());
				if (data.size() > 0) {
					if (Options::Visuals::Chams::BacktrackChams == 2) {
						for (auto& record : data) {
							U::ForceMaterial(material, Options::Visuals::Chams::BacktrackChamsColor);
							oDrawModelExecute(thisptr, matctx, state, pInfo, record.boneMatrix);
						}
					}
					else if (Options::Visuals::Chams::BacktrackChams == 1) {
						auto& back = data.back();
						U::ForceMaterial(material, Options::Visuals::Chams::BacktrackChamsColor);
						oDrawModelExecute(thisptr, matctx, state, pInfo, back.boneMatrix);
					}
				}
			}
		}

		if (!Options::Visuals::Chams::Enabled)
			return;

		if (pLocalPlayer == pBasePlayer && g_pCInput->m_fCameraInThirdPerson && Options::Visuals::Chams::DesyncChams
			&& Options::Misc::Desync) {
			matrix3x4 matrix[128];

			pBasePlayer->SetAbsAngles(g_RealAngle);

			if (pBasePlayer->SetupBones(matrix, 128, 0x100, 0)) {
				//U::ForceMaterial( material, Options::Visuals::Chams::DesyncChamsColor );
				//oDrawModelExecute( thisptr, matctx, state, pInfo, matrix );

				if (Options::Visuals::Chams::DesStyle == 0) // Normal
				{
					int iHealth = pBasePlayer->Health();


					U::ForceMaterial(Materials::ChamsNormalMaterial, Options::Visuals::Chams::DesyncChamsColor);
					oDrawModelExecute(thisptr, matctx, state, pInfo, matrix);


					//U::ForceMaterial(Materials::ChamsNormalMaterial, Options::Visuals::Chams::DesyncChamsColor);
				}
				else if (Options::Visuals::Chams::DesStyle == 1) // Flat
				{
					int iHealth = pBasePlayer->Health();

					U::ForceMaterial(Materials::ChamsFlatMaterial, Options::Visuals::Chams::DesyncChamsColor);
					oDrawModelExecute(thisptr, matctx, state, pInfo, matrix);


					//U::ForceMaterial(Materials::ChamsFlatMaterial, Options::Visuals::Chams::DesyncChamsColor);

				}
				else if (Options::Visuals::Chams::DesStyle == 2) // Wireframe
				{
					int iHealth = pBasePlayer->Health();


					U::ForceMaterial(Materials::ChamsWireframeMaterial, Options::Visuals::Chams::DesyncChamsColor);
					oDrawModelExecute(thisptr, matctx, state, pInfo, matrix);


					//U::ForceMaterial(Materials::ChamsWireframeMaterial, Options::Visuals::Chams::DesyncChamsColor);

				}
				else if (Options::Visuals::Chams::DesStyle == 3) // Platinum
				{
					int iHealth = pBasePlayer->Health();


					U::ForceMaterial(Materials::ChamsNormalMaterial, Options::Visuals::Chams::DesyncChamsColor);
					oDrawModelExecute(thisptr, matctx, state, pInfo, matrix);


					//U::ForceMaterial(Materials::ChamsNormalMaterial, Color(Options::Visuals::Chams::DesyncChamsColor[0] * 255, Options::Visuals::Chams::DesyncChamsColor[1] * 255, Options::Visuals::Chams::DesyncChamsColor[2] * 255, Options::Visuals::Chams::DesyncChamsColor[3] * 255) + (100 - Options::Visuals::Chams::Intensity));


				}
				else if (Options::Visuals::Chams::DesStyle == 4) // metal
				{
					int iHealth = pBasePlayer->Health();


					U::ForceMaterial(Materials::mettalic, Options::Visuals::Chams::DesyncChamsColor);
					oDrawModelExecute(thisptr, matctx, state, pInfo, matrix);


					//U::ForceMaterial(Materials::mettalic, Options::Visuals::Chams::DesyncChamsColor);
				}
			}

			pBasePlayer->SetAbsAngles(QAngle(0, g_FakeAngle.y, 0));

		}

		Color visible_color = Color(Options::Visuals::Chams::VisibleColor[0] * 255, Options::Visuals::Chams::VisibleColor[1] * 255, Options::Visuals::Chams::VisibleColor[2] * 255, Options::Visuals::Chams::VisibleColor[3] * 255);

		if (Options::Visuals::Chams::Style == 0) // Normal
		{
			int iHealth = pBasePlayer->Health();

			if (!Options::Visuals::Chams::VisibleOnly) {
				U::ForceMaterial(Materials::ChamsNormalMaterial, Options::Visuals::Chams::InvisibleColor, true);
				oDrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
			}

			if (Options::Visuals::ESP::ChamsCheckColor) {
				if (iHealth <= 100)
					U::ForceMaterial(Materials::ChamsNormalMaterial, Color(0, 255, 0));
				if (iHealth <= 80)
					U::ForceMaterial(Materials::ChamsNormalMaterial, Color(255, 234, 0));
				if (iHealth <= 60)
					U::ForceMaterial(Materials::ChamsNormalMaterial, Color(255, 136, 0));
				if (iHealth <= 30)
					U::ForceMaterial(Materials::ChamsNormalMaterial, Color(255, 72, 0));
				if (iHealth <= 10)
					U::ForceMaterial(Materials::ChamsNormalMaterial, Color(51, 14, 0));
			}
			else if (Options::Visuals::ESP::RainbowChams) {
				U::ForceMaterial(Materials::ChamsNormalMaterial, m_clrHandsRainbow.GetColor());
			}
			else {
				U::ForceMaterial(Materials::ChamsNormalMaterial, visible_color);
			}
		}
		else if (Options::Visuals::Chams::Style == 1) // Flat
		{
			int iHealth = pBasePlayer->Health();
			if (!Options::Visuals::Chams::VisibleOnly) {
				U::ForceMaterial(Materials::ChamsFlatMaterial, Options::Visuals::Chams::InvisibleColor, true);
				oDrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
			}

			if (Options::Visuals::ESP::ChamsCheckColor) {
				if (iHealth <= 100)U::ForceMaterial(Materials::ChamsFlatMaterial, Color(0, 255, 0));
				if (iHealth <= 80)U::ForceMaterial(Materials::ChamsFlatMaterial, Color(255, 234, 0));
				if (iHealth <= 60)U::ForceMaterial(Materials::ChamsFlatMaterial, Color(255, 136, 0));
				if (iHealth <= 30)U::ForceMaterial(Materials::ChamsFlatMaterial, Color(255, 72, 0));
				if (iHealth <= 10)U::ForceMaterial(Materials::ChamsFlatMaterial, Color(51, 14, 0));
			}
			else if (Options::Visuals::ESP::RainbowChams) {
				U::ForceMaterial(Materials::ChamsFlatMaterial, m_clrHandsRainbow.GetColor());
			}
			else {
				U::ForceMaterial(Materials::ChamsFlatMaterial, visible_color);
			}
		}
		else if (Options::Visuals::Chams::Style == 2) { // Wireframe
			int iHealth = pBasePlayer->Health();

			if (!Options::Visuals::Chams::VisibleOnly) {
				U::ForceMaterial(Materials::ChamsWireframeMaterial, Options::Visuals::Chams::InvisibleColor, true);
				oDrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
			}

			if (Options::Visuals::ESP::ChamsCheckColor) {
				if (iHealth <= 100)U::ForceMaterial(Materials::ChamsWireframeMaterial, Color(0, 255, 0));
				if (iHealth <= 80) U::ForceMaterial(Materials::ChamsWireframeMaterial, Color(255, 234, 0));
				if (iHealth <= 60) U::ForceMaterial(Materials::ChamsWireframeMaterial, Color(255, 136, 0));
				if (iHealth <= 30) U::ForceMaterial(Materials::ChamsWireframeMaterial, Color(255, 72, 0));
				if (iHealth <= 10)U::ForceMaterial(Materials::ChamsWireframeMaterial, Color(51, 14, 0));
			}
			else if (Options::Visuals::ESP::RainbowChams) {
				U::ForceMaterial(Materials::ChamsWireframeMaterial, m_clrHandsRainbow.GetColor());
			}
			else {
				U::ForceMaterial(Materials::ChamsWireframeMaterial, visible_color);
			}
		}
		else if (Options::Visuals::Chams::Style == 3) // Platinum
		{
			int iHealth = pBasePlayer->Health();

			if (!Options::Visuals::Chams::VisibleOnly) {
				U::ForceMaterial(Materials::ChamsNormalMaterial, Options::Visuals::Chams::InvisibleColor, true);
				oDrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
			}

			if (Options::Visuals::ESP::ChamsCheckColor) {
				if (iHealth <= 100) U::ForceMaterial(Materials::ChamsNormalMaterial, Color(133 - Options::Visuals::Chams::Intensity, 1000 - Options::Visuals::Chams::Intensity, 0 - Options::Visuals::Chams::Intensity));
				if (iHealth <= 80) U::ForceMaterial(Materials::ChamsNormalMaterial, Color(1000 - Options::Visuals::Chams::Intensity, 166 - Options::Visuals::Chams::Intensity, 0 - Options::Visuals::Chams::Intensity));
				if (iHealth <= 60) U::ForceMaterial(Materials::ChamsNormalMaterial, Color(1000 - Options::Visuals::Chams::Intensity, 100 - Options::Visuals::Chams::Intensity, 0 - Options::Visuals::Chams::Intensity));
				if (iHealth <= 30) U::ForceMaterial(Materials::ChamsNormalMaterial, Color(1000 - Options::Visuals::Chams::Intensity, 50 - Options::Visuals::Chams::Intensity, 0 - Options::Visuals::Chams::Intensity));
				if (iHealth <= 10) U::ForceMaterial(Materials::ChamsNormalMaterial, Color(33 - Options::Visuals::Chams::Intensity, 0 - Options::Visuals::Chams::Intensity, 0 - Options::Visuals::Chams::Intensity));
			}
			else if (Options::Visuals::ESP::RainbowChams) {
				U::ForceMaterial(Materials::ChamsNormalMaterial, m_clrHandsRainbow.GetColor() + (100 - Options::Visuals::Chams::Intensity));
			}
			else {
				U::ForceMaterial(Materials::ChamsNormalMaterial, Color(Options::Visuals::Chams::VisibleColor[0] * 255, Options::Visuals::Chams::VisibleColor[1] * 255, Options::Visuals::Chams::VisibleColor[2] * 255, Options::Visuals::Chams::VisibleColor[3] * 255) + (100 - Options::Visuals::Chams::Intensity));
			}

		}
		else if (Options::Visuals::Chams::Style == 4) // metal
		{
			int iHealth = pBasePlayer->Health();

			if (!Options::Visuals::Chams::VisibleOnly) {
				U::ForceMaterial(Materials::mettalic, Options::Visuals::Chams::InvisibleColor, true);
				oDrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
			}

			if (Options::Visuals::ESP::ChamsCheckColor) {
				if (iHealth <= 100)
					U::ForceMaterial(Materials::mettalic, Color(0, 255, 0));
				if (iHealth <= 80)
					U::ForceMaterial(Materials::mettalic, Color(255, 234, 0));
				if (iHealth <= 60)
					U::ForceMaterial(Materials::mettalic, Color(255, 136, 0));
				if (iHealth <= 30)
					U::ForceMaterial(Materials::mettalic, Color(255, 72, 0));
				if (iHealth <= 10)
					U::ForceMaterial(Materials::mettalic, Color(51, 14, 0));
			}
			else if (Options::Visuals::ESP::RainbowChams) {
				U::ForceMaterial(Materials::mettalic, m_clrHandsRainbow.GetColor());
			}
			else {
				U::ForceMaterial(Materials::mettalic, visible_color);
			}
		}

		/*else if (Options::Visuals::Chams::Style == 4) // Ebalo
		{
			int iHealth = pBasePlayer->Health();

		float flt_invis_color[4] =
			{
				(Options::Visuals::Chams::InvisibleColor[0] / 255.f) * Options::Visuals::Chams::Intensity,
				(Options::Visuals::Chams::InvisibleColor[1] / 255.f) * Options::Visuals::Chams::Intensity,
				(Options::Visuals::Chams::InvisibleColor[2] / 255.f) * Options::Visuals::Chams::Intensity,
				255.f,
			};

			float flt_vis_color[4] =
		{

			(Options::Visuals::Chams::VisibleColor[1] / 255.f) * Options::Visuals::Chams::Intensity,
			(Options::Visuals::Chams::VisibleColor[2] / 255.f) * Options::Visuals::Chams::Intensity,
			(Options::Visuals::Chams::VisibleColor[3] / 255.f) * Options::Visuals::Chams::Intensity,
			255.f,
		};


			if (!Options::Visuals::Chams::VisibleOnly)
			{
				g_bDrawDIP = true;
				g_pRenderView->SetColorModulation(flt_invis_color);
				oDrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
				g_bDrawDIP = false;
			}
			g_pRenderView->SetColorModulation(flt_vis_color);

		}*/

	}
	else if (Options::Visuals::Hands::Enabled && strstr(szModelName, "arms")) {
		Materials::Hands->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
		Materials::Hands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
		Materials::Hands->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);

		switch (Options::Visuals::Hands::Style) {
		case 0:
			Materials::Hands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			g_pModelRender->ForcedMaterialOverride(Materials::Hands);
			break;
		case 1:
			Materials::Hands->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			g_pModelRender->ForcedMaterialOverride(Materials::Hands);
			break;
		case 2:
			U::ForceMaterial(Materials::ChamsNormalMaterial, Options::Visuals::Hands::color);
			break;
		case 3:
			U::ForceMaterial(Materials::ChamsNormalMaterial, Options::Visuals::Hands::color);
			oDrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
			g_pModelRender->ForcedMaterialOverride(Materials::ChamsWireframeMaterial);
			break;
		case 4:
			U::ForceMaterial(Materials::ChamsNormalMaterial, m_clrHandsRainbow.GetColor());
			break;
		case 5:
			U::ForceMaterial(Materials::ChamsNormalMaterial, m_clrHandsRainbow.GetColor());
			oDrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
			//	g_pModelRender->ForcedMaterialOverride(Materials::ChamsWireframeMaterial);
			break;
		case 6: // metal
			U::ForceMaterial(Materials::mettalic, Options::Visuals::Hands::color);
			break;
		case 7: // metal
			U::ForceMaterial(Materials::test2, Options::Visuals::Hands::color);
			break;


		default:
			break;
		}
	}
}

void __fastcall Hooked_DrawModelExecute(void* thisptr, int edx, IMatRenderContext* matctx, DrawModelState_t& state, ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld) {
	if (!oDrawModelExecute)
		return;

	if (g_pModelRender->IsForcedMaterialOverride())
		return oDrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);

	if (pInfo.pModel && thisptr && g_pEngine->IsInGame() && !Options::Visuals::Chams::bStreamSafe) {
		const char* szModelName = g_pModelInfo->GetModelName(pInfo.pModel);
		DrawChams(szModelName, pInfo.entity_index, thisptr, matctx, state, pInfo, pCustomBoneToWorld);
	}
	oDrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
	g_pModelRender->ForcedMaterialOverride(NULL);

}


namespace CChams
{
	struct CUSTOMVERTEX { FLOAT x, y, z, r, h, w; };
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_TEX1) 

	LPDIRECT3DTEXTURE9 pTexturer;
	LPDIRECT3DTEXTURE9 pTexturey;
	IDirect3DBaseTexture9* deftexture;
	IDirect3DBaseTexture9* deftexture2;

	const BYTE bRed[60] = { 0x42, 0x4D, 0x3C, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00,
		0x00, 0x28, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
		0x01,0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x0B,
		0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
		0x00, 0x01 };
	const BYTE bYellow[60] = { 0x42, 0x4D, 0x3C, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00,
		0x00, 0x28, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x0B,
		0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
		0x00, 0x01 };

	IDirect3DStateBlock9* ppSB = nullptr;
	DWORD oldz;

	IDirect3DPixelShader9* pixelshader = NULL;
	LPDIRECT3DTEXTURE9 sil_texture = NULL;
	IDirect3DSurface9* ppSurfaceLevel = NULL;
	IDirect3DPixelShader9* sil_ps = nullptr;

	IDirect3DPixelShader9* oldpixelshader;
	IDirect3DSurface9* oldrendersurface;
	IDirect3DSurface9* oldrendersurface2;

	IDirect3DSurface9* backbuffer = NULL;
	D3DSURFACE_DESC desc;

	IDirect3DVertexBuffer9* v_buffer = NULL;

	LPDIRECT3DTEXTURE9 EnemyVis1;
	LPDIRECT3DTEXTURE9 EnemyInVis1;
	LPDIRECT3DTEXTURE9 TeamVis1;
	LPDIRECT3DTEXTURE9 TeamInVis1;

	void* traverse_stack(void** ebp) {
		if (ebp == nullptr)
			return nullptr;
		static auto draw_points_ret_addr = (void*)(U::FindPattern("studiorender.dll", "draw_points_ret_addr", "8B 7D FC 03 F8"));
		auto** next = *(void***)(ebp);
		if (ebp[1] == draw_points_ret_addr)
			return next[4];

		return traverse_stack(next);
	}

	void* get_ent() {
		auto data = 0;
		__asm {
			mov data, ebp
		}
		return traverse_stack((void**)(data));
	}

	HRESULT Generate(LPDIRECT3DDEVICE9 pDevice) {
		D3DCAPS9 caps;

		int major_vs, minor_vs;
		int major_ps, minor_ps;
		pDevice->GetDeviceCaps(&caps);

		DWORD VERSPX1 = D3DSHADER_VERSION_MAJOR(caps.PixelShaderVersion);
		DWORD VERSPX2 = D3DSHADER_VERSION_MINOR(caps.PixelShaderVersion);

		char szVersion[32];
		sprintf(szVersion, "ps_%d_%d", VERSPX1, VERSPX2);

		char szShader[256];
		sprintf(szShader, "%s \n mov oC0, c0", szVersion); // версия 1.1 / цвет rgba(0.0, 1.0, 1.0, 1.0) 

		ID3DXBuffer* pShaderBuf = NULL;

		D3DXAssembleShader(szShader, sizeof(szShader), NULL, NULL, 0, &pShaderBuf, NULL);
		if (pShaderBuf)
			pDevice->CreatePixelShader((const DWORD*)pShaderBuf->GetBufferPointer(), &pixelshader);

		pDevice->GetRenderTarget(0, &backbuffer);
		backbuffer->GetDesc(&desc);
		backbuffer->Release();

		if (!sil_texture) {
			pDevice->CreateTexture(desc.Width, desc.Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &sil_texture, NULL);
			sil_texture->GetSurfaceLevel(0, &ppSurfaceLevel);
		}

		if (!v_buffer) {
			auto hr = pDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX), // change to 4, instead of 3 
				D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
				CUSTOMFVF,
				D3DPOOL_DEFAULT,
				&v_buffer,
				nullptr);
		}

		return S_OK;
	}

	void drawtexture(LPDIRECT3DDEVICE9 pDevice) {
		pDevice->GetRenderTarget(0, &backbuffer);
		backbuffer->GetDesc(&desc);
		backbuffer->Release();

		pDevice->CreateStateBlock(D3DSBT_ALL, &ppSB);

		CUSTOMVERTEX vertices[] =
		{
			{ 0, 0.0, 0, 1.0,0.0,0.0, },
		{ desc.Width, 0, 0.0, 1.0,1.0,0.0 , },
		{ 0, desc.Height, 0, 1.0,0.0,1.0, },
		{ desc.Width, desc.Height, 0, 1.0,1.0,1.0 , },

		};

		VOID* pVoid; // a void pointer 

		v_buffer->Lock(0, 0, (void**)& pVoid, 0);
		_memcpy(pVoid, vertices, sizeof(vertices));
		v_buffer->Unlock();

		pDevice->SetPixelShader(NULL);
		pDevice->SetTexture(0, sil_texture);

		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		pDevice->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
		pDevice->SetFVF(CUSTOMFVF);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		ppSB->Apply();
		ppSB->Release();
	}

	void DrawRect(LPDIRECT3DDEVICE9 pDevice, int x1, int y1, int x2, int y2, BYTE r, BYTE g, BYTE b) {
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		D3DRECT BarRect;
		D3DCOLOR Cor;

		BarRect.x1 = x1;
		BarRect.x2 = x2;
		BarRect.y1 = y1;
		BarRect.y2 = y2;

		Cor = 0x00000000;

		pDevice->Clear(1, &BarRect, D3DCLEAR_TARGET || D3DCLEAR_ZBUFFER, Cor, 0, 0);
	}

	HRESULT GenerateTexture(IDirect3DDevice9* vDevice, IDirect3DTexture9** ppD3Dtex, DWORD color) {
		HRESULT hr = vDevice->CreateTexture(8, 8, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, ppD3Dtex, NULL);
		if (FAILED(hr))
			return hr;

		D3DLOCKED_RECT d3dlr;
		(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);

		BYTE* pDstRow = (BYTE*)d3dlr.pBits;
		DWORD* pDst32;

		for (int y = 0; y < 8; y++) {
			pDst32 = (DWORD*)pDstRow;

			for (int x = 0; x < 8; x++)
				* pDst32++ = color;

			pDstRow += d3dlr.Pitch;
		}

		(*ppD3Dtex)->UnlockRect(0);

		return S_OK;
	}

	void Render(LPDIRECT3DDEVICE9 pDevice) {
		if (Options::Visuals::Chams::Enabled && Options::Visuals::Chams::bStreamSafe && pDevice) {
			static bool eblo_tupoe = true;
			if (eblo_tupoe) {
				Generate(pDevice);
				D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)& bRed, sizeof(bRed), &pTexturer);
				eblo_tupoe = false;
			}

			pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);
			if (!sil_texture || !ppSurfaceLevel || !v_buffer)
				Generate(pDevice);

			if (sil_texture && ppSurfaceLevel && v_buffer) {
				drawtexture(pDevice);
			}

			pDevice->GetRenderTarget(0, &oldrendersurface);
			pDevice->SetRenderTarget(0, ppSurfaceLevel);
			DrawRect(pDevice, 0, 0, desc.Width, desc.Height, 0, 0, 0);
			pDevice->SetRenderTarget(0, oldrendersurface);
			oldrendersurface->Release();

			//pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, false );
		}
	}

	void Reset() {
		if (v_buffer) {
			v_buffer->Release();
			v_buffer = 0;
		}

		if (sil_texture) {
			sil_texture->Release();
			sil_texture = nullptr;
		}

		if (ppSurfaceLevel) {
			ppSurfaceLevel->Release();
			ppSurfaceLevel = 0;
		}

		if (EnemyInVis1) {
			EnemyInVis1->Release();
			EnemyInVis1 = 0;
		}

		if (EnemyVis1) {
			EnemyVis1->Release();
			EnemyVis1 = 0;
		}
	}

	// DrawIndexPrimitive Hook For Render Shaders
	DWORD old_zenable;
	DWORD old_fillmode;
	IDirect3DStateBlock9* pStateBlock = NULL;
	typedef long(__stdcall* DrawIndexedPrimitiveFn)(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);

	DrawIndexedPrimitiveFn oDrawIndexedPrimitive;
	long __stdcall Hooked_DrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDev,
		D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex,
		UINT NumVertices, UINT startIndex, UINT PrimitiveCount) {
		oDrawIndexedPrimitive(pDev, PrimType, BaseVertexIndex,
			MinVertexIndex, NumVertices, startIndex,
			PrimitiveCount);

		Color ChamsEnemyVis = Color(int(Options::Visuals::ESP::RepachinoVis[0] * 255), int(Options::Visuals::ESP::RepachinoVis[1] * 255), int(Options::Visuals::ESP::RepachinoVis[2] * 255));
		Color ChamsEnemyInvis = Color(int(Options::Visuals::ESP::RepachinoInvis[0] * 255), int(Options::Visuals::ESP::RepachinoInvis[1] * 255), int(Options::Visuals::ESP::RepachinoInvis[2] * 255));
		float flMaterialChamsBrightness = Options::Visuals::Chams::flMaterialChamsBrightness;
		bool bChamsVisibleOnly = Options::Visuals::Chams::VisibleOnly;
		bool bMaterialChams = Options::Visuals::Chams::bMaterialChams;
		bool bFlatChams = Options::Visuals::Chams::bFlatChams;
		bool bWireFrameChams = Options::Visuals::Chams::bWireFrameChams;

		if (!sil_texture || !ppSurfaceLevel || !v_buffer)
			Generate(pDev);

		if (Options::Visuals::Chams::bStreamSafe && Options::Visuals::Chams::Enabled) {

			if (!EnemyInVis1 || !EnemyVis1) {
				GenerateTexture(pDev, &EnemyInVis1, D3DCOLOR_RGBA(255, (int)ChamsEnemyVis.r(), (int)ChamsEnemyVis.g(), (int)ChamsEnemyVis.b()));
				GenerateTexture(pDev, &EnemyVis1, D3DCOLOR_RGBA(255, (int)ChamsEnemyInvis.r(), (int)ChamsEnemyInvis.g(), (int)ChamsEnemyInvis.b()));
			}

			auto ent = (C_BasePlayer*)get_ent();
			auto local = C_BasePlayer::LocalPlayer();
			if (ent != nullptr && local && *(int*)((uintptr_t)(ent))) {
				int team = ent->Team();
				int hpp = ent->Health();

				if ((!Options::Visuals::Chams::EnemyOnly || local->Team() != team && (team == 3 || team == 2)) && hpp) {

					// IClientEntity* entry = (IClientEntity*) ent; 

					float multiply = 255.f - flMaterialChamsBrightness;
					if (multiply == 0)
						multiply = 1;
					//flat 
					float def[4] = { 1,1,1,1 };
					float alpha = 255.f;
					/*{ ChamsTeamVis.r / 255.f, ChamsTeamVis.g / 255.f, ChamsTeamVis.b / 255.f, 255.f / 255.f};*/
					float value2[4] = { ChamsEnemyVis.r() / 255.f * alpha / 255.f, ChamsEnemyVis.g() / 255.f * alpha / 255.f, ChamsEnemyVis.b() / 255.f * alpha / 255.f, alpha / 255.f };
					float value[4] = { ChamsEnemyInvis.r() / 255.f * alpha / 255.f, ChamsEnemyInvis.g() / 255.f * alpha / 255.f, ChamsEnemyInvis.b() / 255.f * alpha / 255.f, alpha / 255.f };
					//textured 
					float value4[4] = { ChamsEnemyVis.r() / multiply , ChamsEnemyVis.g() / multiply, ChamsEnemyVis.b() / multiply, alpha };
					float value3[4] = { ChamsEnemyInvis.r() / multiply, ChamsEnemyInvis.g() / multiply, ChamsEnemyInvis.b() / multiply , alpha };
					//not flat not textured 
					float value6[4] = { ChamsEnemyVis.r() / 500.f , ChamsEnemyVis.g() / 500.f, ChamsEnemyVis.b() / 500.f , alpha / 500.f };
					float value5[4] = { ChamsEnemyInvis.r() / 500.f, ChamsEnemyInvis.g() / 500.f, ChamsEnemyInvis.b() / 500.f , alpha / 500.f };

					pDev->GetRenderTarget(0, &oldrendersurface);
					pDev->GetPixelShader(&oldpixelshader);
					pDev->GetRenderState(D3DRS_ZENABLE, &old_zenable);
					pDev->GetRenderState(D3DRS_FILLMODE, &old_fillmode);
					/*************************************************************/
					pDev->SetRenderTarget(0, ppSurfaceLevel);
					pDev->GetTexture(0, &deftexture);

					/*******************************************************/
					if (!bChamsVisibleOnly) {
						pDev->SetRenderState(D3DRS_ZENABLE, false);
						if (!bMaterialChams) {
							if (bFlatChams) {

								pDev->SetPixelShaderConstantF(0, value, 1);
								pDev->SetPixelShader(pixelshader);
							}
							else {
								pDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
								pDev->SetTexture(0, EnemyVis1);
							}
						}
						else pDev->SetPixelShaderConstantF(1, value3, 1);


						oDrawIndexedPrimitive(pDev, PrimType, BaseVertexIndex,
							MinVertexIndex, NumVertices, startIndex,
							PrimitiveCount);
					}

					pDev->SetRenderState(D3DRS_ZENABLE, old_zenable);
					pDev->SetRenderState(D3DRS_FILLMODE, old_fillmode);
					if (!bMaterialChams) {
						if (bFlatChams) {
							pDev->SetPixelShader(pixelshader);//а что обозначает ::O?
							pDev->SetPixelShaderConstantF(0, value2, 1);
						}
						else {
							pDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
							pDev->SetTexture(0, EnemyInVis1);
						}
					}
					else pDev->SetPixelShaderConstantF(1, value4, 1);
					if (bWireFrameChams == 1)	pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
					oDrawIndexedPrimitive(pDev, PrimType, BaseVertexIndex,
						MinVertexIndex, NumVertices, startIndex,
						PrimitiveCount);

					/****************************************/
					pDev->SetPixelShaderConstantF(0, def, 1);
					pDev->SetPixelShaderConstantF(1, def, 1);
					pDev->SetRenderTarget(0, oldrendersurface);
					pDev->SetRenderState(D3DRS_ZENABLE, old_zenable);
					pDev->SetRenderState(D3DRS_FILLMODE, old_fillmode);
					pDev->SetPixelShader(oldpixelshader);

					pDev->SetTexture(0, deftexture);
					if (deftexture)
						deftexture->Release();
					oldrendersurface->Release();
					oldpixelshader->Release();
				}
			}
		}
		return true;
	}
}

#if 0
namespace CChams
{
	IDirect3DBaseTexture9* OldTexture = NULL;
	IDirect3DPixelShader9* PixelShader = NULL;
	IDirect3DPixelShader9* OldPixelShader = NULL;
	IDirect3DSurface9* SurfaceLevel = NULL;
	IDirect3DSurface9* OldSurfaceLevel = NULL;
	IDirect3DSurface9* TempSurfaceLevel = NULL;
	IDirect3DStateBlock9* StateBlock = NULL;
	IDirect3DVertexBuffer9* VertexBuffer = NULL;
	D3DSURFACE_DESC TextureCoords;
	LPDIRECT3DTEXTURE9 ChamsTexture = NULL;
	DWORD OldIgnoreZ;

	HRESULT Generate(LPDIRECT3DDEVICE9 pDevice) {
		// Create Shader String
		D3DCAPS9 Caps;
		pDevice->GetDeviceCaps(&Caps);
		DWORD VERSPX1 = D3DSHADER_VERSION_MAJOR(Caps.PixelShaderVersion);
		DWORD VERSPX2 = D3DSHADER_VERSION_MINOR(Caps.PixelShaderVersion);
		char szVersion[32];
		sprintf(szVersion, "ps_%d_%d", VERSPX1, VERSPX2);
		char szShader[256];
		sprintf(szShader, "%s \n mov oC0, c0", szVersion);

		// Create Shader From String
		ID3DXBuffer* ShaderBuffer = NULL;
		D3DXAssembleShader(szShader, sizeof(szShader), NULL, NULL, 0, &ShaderBuffer, NULL);
		if (ShaderBuffer)
			pDevice->CreatePixelShader((const DWORD*)ShaderBuffer->GetBufferPointer(), &PixelShader);

		// Create Texture Coords
		pDevice->GetRenderTarget(0, &TempSurfaceLevel);
		TempSurfaceLevel->GetDesc(&TextureCoords);
		TempSurfaceLevel->Release();

		// Create Texture From Coords
		pDevice->CreateTexture(TextureCoords.Width, TextureCoords.Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &ChamsTexture, NULL);
		ChamsTexture->GetSurfaceLevel(0, &SurfaceLevel);

		// Create Vertex Buffer
		pDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX), 0, CUSTOMFVF, D3DPOOL_MANAGED, &VertexBuffer, NULL);

		return S_OK;
	}

	// Util For Render Texture
	void DrawRect(LPDIRECT3DDEVICE9 pDevice, int x1, int y1, int x2, int y2, BYTE r, BYTE g, BYTE b) {
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		D3DRECT BarRect;
		D3DCOLOR Color;

		BarRect.x1 = x1;
		BarRect.x2 = x2;
		BarRect.y1 = y1;
		BarRect.y2 = y2;

		Color = 0x00000000;

		pDevice->Clear(1, &BarRect, D3DCLEAR_TARGET || D3DCLEAR_ZBUFFER, Color, 0, 0);
	}

	// Get Render Entity Function
	void* DrawPoints = (void*)(U::FindPattern("studiorender.dll", "DrawPoints", "8B 7D FC 03 F8"));
	void* TraverseStack(void** ebp) {
		if (ebp == nullptr)
			return nullptr;

		auto** next = *(void***)(ebp);

		if (ebp[1] == DrawPoints)
			return next[4];

		return TraverseStack(next);
	}
	void* GetEntity() {
		auto data = 0;
		__asm { mov data, ebp }
		return TraverseStack((void**)(data));
	}

	void DrawTexture(LPDIRECT3DDEVICE9 pDevice) {
		pDevice->GetRenderTarget(0, &TempSurfaceLevel);
		TempSurfaceLevel->GetDesc(&TextureCoords);
		TempSurfaceLevel->Release();

		pDevice->CreateStateBlock(D3DSBT_ALL, &StateBlock);

		CUSTOMVERTEX vertices[] =
		{
			{ 0, 0.0, 0, 1.0, 0.0, 0.0, },
		{ TextureCoords.Width, 0, 0.0, 1.0, 1.0, 0.0, },
		{ 0, TextureCoords.Height, 0, 1.0, 0.0, 1.0, },
		{ TextureCoords.Width, TextureCoords.Height, 0, 1.0, 1.0, 1.0, },
		};

		VOID* pVoid;
		VertexBuffer->Lock(0, 0, (void**)& pVoid, 0);
		memcpy(pVoid, vertices, sizeof(vertices));
		VertexBuffer->Unlock();

		pDevice->SetPixelShader(NULL);
		pDevice->SetTexture(0, ChamsTexture);

		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(CUSTOMVERTEX));
		pDevice->SetFVF(CUSTOMFVF);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		StateBlock->Apply();
		StateBlock->Release();
		VertexBuffer->Release();
	}

	void Render(LPDIRECT3DDEVICE9 pDevice) {
		if (Options::Visuals::Chams::Enabled && Options::Visuals::Chams::Style >= 4) {
			if (ChamsTexture && SurfaceLevel)
				DrawTexture(pDevice);

			if (pDevice != NULL) {
				pDevice->GetRenderTarget(0, &OldSurfaceLevel);
				pDevice->SetRenderTarget(0, SurfaceLevel);
				DrawRect(pDevice, 0, 0, TextureCoords.Width, TextureCoords.Height, 0, 0, 0);
				pDevice->SetRenderTarget(0, OldSurfaceLevel);
				OldSurfaceLevel->Release();
			}
		}

		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}

	void Reset() {
		VertexBuffer->Release();
		ChamsTexture->Release();
		SurfaceLevel->Release();
	}
}

// DrawIndexPrimitive Hook For Render Shaders
typedef long(__stdcall* DrawIndexedPrimitiveFn)(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
DrawIndexedPrimitiveFn oDrawIndexedPrimitive;
long __stdcall Hooked_DrawIndexedPrimitive(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount) {
	if (!oDrawIndexedPrimitive)
		return 0;

	oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);

	if (Options::Visuals::Chams::Enabled && Options::Visuals::Chams::Style >= 4) {
		const auto* ent = CChams::GetEntity();
		C_BasePlayer* local = C_BasePlayer::LocalPlayer();

		if (ent != nullptr && local && Options::Visuals::Chams::Enabled && *(int*)((uintptr_t)(ent))) {
			int team = *(int*)((uintptr_t)(ent)+0xF0);
			int hpp = *(int*)((uintptr_t)(ent)+0xFC);

			bool visible = false;

			if ((Options::Visuals::Chams::EnemyOnly && (local->Team() != team)) ||
				(!Options::Visuals::Chams::EnemyOnly && (local->Team() == team))) {
				if (Options::Visuals::Chams::EnemyOnly && (local->Team() != team))
					visible = true;
				if (!Options::Visuals::Chams::EnemyOnly && (local->Team() == team))
					visible = true;
			}
			else {
				visible = false;
			}

			if (visible && (team == 3 || team == 2) && hpp) {
				float def[4] = { 1, 1, 1, 1 };
				//flat
				float flat_invis_col[4] = { Options::Visuals::Chams::InvisibleColor[0], Options::Visuals::Chams::InvisibleColor[1], Options::Visuals::Chams::InvisibleColor[2], 255.f };
				float flat_vis_col[4] = { Options::Visuals::Chams::VisibleColor[0] , Options::Visuals::Chams::VisibleColor[1], Options::Visuals::Chams::VisibleColor[2], 255.f };
				//textured
				float tex_invis_col[4] = { Options::Visuals::Chams::InvisibleColor[0] * Options::Visuals::Chams::Intensity , Options::Visuals::Chams::InvisibleColor[1] * Options::Visuals::Chams::Intensity , Options::Visuals::Chams::InvisibleColor[2] * Options::Visuals::Chams::Intensity , 255.f };
				float tex_vis_col[4] = { Options::Visuals::Chams::VisibleColor[0] * Options::Visuals::Chams::Intensity , Options::Visuals::Chams::VisibleColor[1] * Options::Visuals::Chams::Intensity , Options::Visuals::Chams::VisibleColor[2] * Options::Visuals::Chams::Intensity , 255.f };
				/*************************************************************/
				pDevice->GetRenderTarget(0, &CChams::OldSurfaceLevel);
				pDevice->GetPixelShader(&CChams::OldPixelShader);
				pDevice->GetTexture(0, &CChams::OldTexture);
				pDevice->GetRenderState(D3DRS_ZENABLE, &CChams::OldIgnoreZ);
				/*************************************************************/
				// Begin Render
				/*************************************************************/
				pDevice->SetRenderTarget(0, CChams::SurfaceLevel);
				if (!Options::Visuals::Chams::VisibleOnly) {
					pDevice->SetRenderState(D3DRS_ZENABLE, false);
					if (Options::Visuals::Chams::Style == 4) {
						pDevice->SetPixelShaderConstantF(1, tex_invis_col, 1);
					}
					else if (Options::Visuals::Chams::Style == 5) {
						pDevice->SetPixelShaderConstantF(0, flat_invis_col, 1);
						pDevice->SetPixelShader(CChams::PixelShader);
					}
					oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
				}
				pDevice->SetRenderState(D3DRS_ZENABLE, true);
				if (Options::Visuals::Chams::Style == 4) {
					pDevice->SetPixelShaderConstantF(1, tex_vis_col, 1);
				}
				else if (Options::Visuals::Chams::Style == 5) {
					pDevice->SetPixelShader(CChams::PixelShader);
					pDevice->SetPixelShaderConstantF(0, flat_vis_col, 1);
				}
				oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
				/*************************************************************/
				pDevice->SetPixelShaderConstantF(0, def, 1);
				pDevice->SetPixelShaderConstantF(1, def, 1);
				pDevice->SetRenderTarget(0, CChams::OldSurfaceLevel);
				pDevice->SetPixelShader(CChams::OldPixelShader);
				pDevice->SetTexture(0, CChams::OldTexture);
				pDevice->SetRenderState(D3DRS_ZENABLE, CChams::OldIgnoreZ);
				/*************************************************************/
				if (CChams::OldTexture)
					CChams::OldTexture->Release();
				if (CChams::OldSurfaceLevel)
					CChams::OldSurfaceLevel->Release();
				if (CChams::OldPixelShader)
					CChams::OldPixelShader->Release();
			}
		}
	}
	return true;
}
#endif
