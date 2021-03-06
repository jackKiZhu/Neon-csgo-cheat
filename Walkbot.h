#pragma once
#define STEP_SIZE 20
#define DEBUG_BOX_SIZE 5

namespace WalkBot
{
	C_BasePlayer* m_pLocalPlayer;
	INavFile* m_pNavFile;
	bool m_bParsed;
	bool m_bPathFounded;
	std::vector<CNavArea> Path;
	std::vector<CNavArea> Areas;

	void Setup(const char* szMap)
	{
		return;

		char buffer[256] = "";
		sprintf(buffer, "csgo\\maps\\%s.nav", szMap);
		m_pNavFile = new INavFile();
		m_bParsed = m_pNavFile->Load(buffer);
		m_bPathFounded = false;
		if (m_bParsed)
		{
			Areas.clear();
			Areas.resize(10000);
			for (int i = 0; i < m_pNavFile->m_areas.size(); i++)
				Areas[m_pNavFile->m_areas[i].m_id] = m_pNavFile->m_areas[i];
		}
	}

	bool ValidArea(CNavArea Area) // TODO: Remove
	{
		return true;
		/*return (Area.m_attributeFlags & NAV_MESH_RUN) ||
			(Area.m_attributeFlags & NAV_MESH_WALK) ||
			(Area.m_attributeFlags & NAV_MESH_STAIRS);*/
	}

	CNavArea GetClosestArea()
	{
		Vector3 vecLocalPos = m_pLocalPlayer->GetOrigin();

		float flBestDistance = FLT_MAX;
		CNavArea cBestArea;
		for each (CNavArea cArea in m_pNavFile->m_areas)
		{
			if (!ValidArea(cArea))
				continue;

			float flDistance = vecLocalPos.DistTo(cArea.m_center);
			if (flDistance < flBestDistance)
			{
				flBestDistance = flDistance;
				cBestArea = cArea;
			}
		}

		return cBestArea;
	}

	bool FindPath()
	{
		Path.clear();

		CNavArea ClosestArea = GetClosestArea();
		CNavArea CurrentArea = ClosestArea;
		std::vector<UINT> PathedIDs;
		for (int i = 0; i < STEP_SIZE; i++)
		{
			for each (NavConnect Connect in CurrentArea.m_connect)
			{
				for each (UINT id in PathedIDs)
					if (id == Connect.id)
						continue;

				CNavArea Area = Areas[Connect.id];
				if (!ValidArea(Area))
					continue;

				CurrentArea = Area;
				Path.push_back(Area);
				break;
			}

			/*while (true)
			{
				NavConnect Connect = CurrentArea.m_connect[Math::RandomInt(0, CurrentArea.m_connect.size())];
				for each (UINT id in PathedIDs)
					if (id == Connect.id)
						continue;

				CNavArea Area = Areas[Connect.id];
				if (!ValidArea(Area))
					continue;

				CurrentArea = Area;
				Path.push_back(Area);
				break;
			}*/
		}

		return Path.size() == STEP_SIZE;
	}

	void Run()
	{
		return;

		static bool bOnce = false;
		if (GetAsyncKeyState(VK_LMENU) && !bOnce)
		{
			m_bPathFounded = false;
			bOnce = true;
		}
		else
			bOnce = false;

		m_pLocalPlayer = C_BasePlayer::LocalPlayer();
		if (!m_pLocalPlayer || m_pLocalPlayer->Health() < 1) // no player or player dead
			return;
		if (!m_pNavFile || !m_bParsed) // map's not parsed/initalized
			return;

		if (!m_bPathFounded)
		{
			m_bPathFounded = FindPath();
			if (!m_bPathFounded)
			{
				DEVMSG("[WALKBOT] ERROR: CAN'T FIND PATH!");
				return;
			}
		}

		for each (CNavArea pArea in Path)
			g_pDebugOverlay->AddBoxOverlay(pArea.m_center, Vector3(-DEBUG_BOX_SIZE, -DEBUG_BOX_SIZE, 0), Vector3(DEBUG_BOX_SIZE, DEBUG_BOX_SIZE, DEBUG_BOX_SIZE *2), Vector3(0, 0, 0), 0, 255, 0, 100, 0.1f);
	}
}