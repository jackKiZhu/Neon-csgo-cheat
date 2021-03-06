#pragma once

#define RADAR_MAP_SIZE 1024
#define RADAR_ICON_SIZE 15
namespace TrueRadar
{
	// Radar settings
	bool m_bLoaded = false;
	IDirect3DTexture9* m_pMapTexture = NULL;

	// Parsable
	Vector3 m_vMapOrigin;
	double m_flMapScale;

	// Map settings
	int m_iScreenWidth, m_iScreenHeight;
	float m_flMapX;
	float m_flMapY;
	float m_flMapSize;
	
	string parseString(string szBefore, string szSource)
	{
		if (!szBefore.empty() && !szSource.empty() && (szSource.find(szBefore) != std::string::npos))
		{
			string t = strstr(szSource.c_str(), szBefore.c_str());
			t.erase(0, szBefore.length());
			size_t firstLoc = t.find("\"", 0);
			size_t secondLoc = t.find("\"", firstLoc + 1);
			t = t.substr(firstLoc + 1, secondLoc - 3);
			return t;
		}
		else
			return "";
	}

	Vector3 WorldToMap(Vector3 vWorldPosition)
	{
		const int iMapCenter = RADAR_MAP_SIZE / 2;

		// World2Map
		Vector3 vMapPosition;
		vMapPosition.x = (vWorldPosition.x - m_vMapOrigin.x) / m_flMapScale;
		vMapPosition.y = (vWorldPosition.y - m_vMapOrigin.y) / -m_flMapScale;
		vMapPosition.z = 0;

		// Map2Panel
		Vector3 vOffset;
		vOffset.x = vMapPosition.x - iMapCenter;
		vOffset.y = vMapPosition.y - iMapCenter;
		vOffset.z = 0;

		// Scale // TODO: Is it right? ((m_fZoom * m_fFullZoom) / OVERVIEW_MAP_SIZE)
		float fScale = Options::Radar::Zoom/*1.f*/ / RADAR_MAP_SIZE;
		vOffset.x *= fScale;
		vOffset.y *= fScale;

		Vector3 vFinalPos;
		vFinalPos.x = (m_flMapSize * 0.5f) + (m_flMapSize * vOffset.x);
		vFinalPos.y = (m_flMapSize * 0.5f) + (m_flMapSize * vOffset.y);
		vFinalPos.z = 0;

		// Clamp
		//Math::Clamp(vOffset.x, 0, m_iScreenHeight - RADAR_ICON_SIZE);
		//Math::Clamp(vOffset.y, 0, m_iScreenHeight - RADAR_ICON_SIZE);

		return vFinalPos;
	}

	bool OnMapLoad(const char* pszMapName)
	{
		m_bLoaded = false;
		char szPath[256] = "\0";

		sprintf(szPath, "csgo\\resource\\overviews\\%s_radar.dds", pszMapName);
		if (FAILED(D3DXCreateTextureFromFileA(D::m_pDevice, szPath, &m_pMapTexture)))
		{
			MakeNotify("Radar: Failed loading radar texture! #1");
			DEVMSG("OnMapLoad: Failed loading radar texture!");
			return false;
		}

		sprintf(szPath, ".\\csgo\\resource\\overviews\\%s.txt", pszMapName);
		std::ifstream ifs(szPath);
		if (ifs.bad())
		{
			MakeNotify("Radar: Failed loading radar texture! #2");
			DEVMSG("OnMapLoad: Info file not found!");
			return false;
		}
		std::string szInfo((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		if (szInfo.empty())
		{
			MakeNotify("Radar: Failed loading radar texture! #3");
			DEVMSG("OnMapLoad: Info file empty!");
			return false;
		}
		m_vMapOrigin.x = std::stoi(parseString("\"pos_x\"", szInfo));
		m_vMapOrigin.y = std::stoi(parseString("\"pos_y\"", szInfo));
		m_flMapScale = std::stod(parseString("\"scale\"", szInfo));

		m_bLoaded = true;
		return true;
	}

	bool RotatePoint(ImVec2& p, float a)
	{
		a = Math::Deg2Rad(a - 90.f);
		float s = sin(a);
		float c = cos(a);
		float cs = (m_flMapSize / 2);
		float cx = m_flMapX + cs;
		float cy = m_flMapY + cs;

		// translate point back to origin
		p.x -= cx;
		p.y -= cy;

		// rotate point
		float xnew = p.x * c - p.y * s;
		float ynew = p.x * s + p.y * c;

		// translate point back
		p.x = xnew + cx;
		p.y = ynew + cy;

		return true;
	}

	bool RenderMap()
	{
		// Prepare location/size
		g_pEngine->GetScreenSize(m_iScreenWidth, m_iScreenHeight);
		m_flMapX = Options::Radar::X;
		m_flMapY = Options::Radar::Y;
		m_flMapSize = Options::Radar::Size;

		// Vars
		int x = m_flMapX;
		int y = m_flMapY;
		int size = m_flMapSize;
		int center_size = (size / 2);

		// Limit radar bounds
		D::m_pDrawList->PushClipRect(ImVec2(x, y), ImVec2(x + size, y + size), false);
		 
		// Scale map
		float new_size = size * Options::Radar::Zoom;
		float size_diff = new_size - size;
		size = new_size;
		x -= size_diff / 2;
		y -= size_diff / 2;

		// Locate map by our local player
		auto local_player = C_BasePlayer::LocalPlayer();
		if (local_player)
		{
			Vector3 world_origin = local_player->GetOrigin();
			Vector3 map_origin = WorldToMap(world_origin);
			x += (center_size - map_origin.x);
			y += (center_size - map_origin.y);
		}
		
		// Prepare imgui shit
		ImVec2 uv_a(0, 0), uv_c(1, 1), uv_b(uv_c.x, uv_a.y), uv_d(uv_a.x, uv_c.y);
		ImVec2 a(x, y), c(x + size, y + size), b(c.x, a.y), d(a.x, c.y);

		// Rotate
		Vector3 vAngle;
		g_pEngine->GetViewAngles(vAngle);
		float angle = vAngle.y;
		RotatePoint(a, angle);
		RotatePoint(b, angle);
		RotatePoint(c, angle);
		RotatePoint(d, angle);

		// Render background first
		D::RectFilled(m_flMapX, m_flMapY, m_flMapSize, m_flMapSize, Color::Black());

		// Render
		D::m_pDrawList->PushTextureID(m_pMapTexture);
		D::m_pDrawList->PrimReserve(6, 4);
		D::m_pDrawList->PrimQuadUV(a, b, c, d, uv_a, uv_b, uv_c, uv_d, 0xFFFFFFFF);
		D::m_pDrawList->PopTextureID();

		// Remove limit
		D::m_pDrawList->PopClipRect();

		return true;
	}

	void Render()
	{
		if (!m_pMapTexture)
			return;
		if (!m_bLoaded)
			return;

		// Draw map
		RenderMap();
		return;

		// Draw player
		/*C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer();
		for (int i = 0; i < g_pEngine->GetMaxClients(); i++) {
			C_BasePlayer* pBasePlayer = g_pEntityList->GetClientEntity<C_BasePlayer>(i);
			if (!pBasePlayer)
				continue;
			if (pBasePlayer->Health() < 1)
				continue;

			player_info_t PlayerInfo;
			if (!g_pEngine->GetPlayerInfo(i, &PlayerInfo))
				continue;

			Vector3 EntityPos = WorldToMap(pBasePlayer->GetOrigin());
			EntityPos.x = (int)EntityPos.x;
			EntityPos.y = (int)EntityPos.y;
			EntityPos.x += m_flMapX;

			int iPlayerTeam = pBasePlayer->Team();
			Color clrColor = Color(255, 255, 255, pBasePlayer->Dormant() ? 100 : 255);

			//D::m_pDrawList->AddImage(iPlayerTeam == CS_TEAM_TT ? m_pTextureT : m_pTextureCT, { EntityPos.x - RADAR_ICON_SIZE, EntityPos.y - RADAR_ICON_SIZE }, { EntityPos.x + RADAR_ICON_SIZE, EntityPos.y + RADAR_ICON_SIZE }, { 1, 1 }, { 0, 0 }, D::GetImColor(clrColor));
			//D::Text(EntityPos.x, EntityPos.y - RADAR_ICON_SIZE - 6, clrColor, true, true, Font::Small, PlayerInfo.name);
		}*/
	}
}
