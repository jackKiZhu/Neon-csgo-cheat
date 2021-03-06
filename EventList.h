#pragma once

class Event_t
{
public:
	char m_szText[256];
	float m_flTime;
	float m_flPercentageOpened;
	Event_t(char szText[256], ...)
	{
		char szBuffer[256] = "";
		va_list va;
		va_start(va, szText);
		vsnprintf_s(szBuffer, 256, szText, va);
		va_end(va);

		s_strcpy(m_szText, szBuffer);
		m_flTime = g_pGlobals->curtime;
		m_flPercentageOpened = 0;
	}
};

namespace EventList
{
	std::vector<Event_t> m_Events;

	void Add(Event_t e)
	{
		m_Events.push_back(e);
	}

	
	void Add(char* str)
	{
		Add(Event_t(str));
	}

	void Clear()
	{
		m_Events.clear();
	}

	void Render()
	{
		int iScreenWidth, iScreenHeight;
		g_pEngine->GetScreenSize(iScreenWidth, iScreenHeight);

		for (int i = 0; i < m_Events.size(); i++)
		{
			if (m_Events[i].m_flTime > g_pGlobals->curtime - 5.f)
			{
				wchar_t szString[512] = L"";
				MultiByteToWideChar(CP_UTF8, 0, m_Events[i].m_szText, -1, szString, 512);
				RECT textRect = D::GetTextSize(szString, Font::ESP);
				float flProgress = (textRect.right + 10.f) / 100.f;
				if (m_Events[i].m_flPercentageOpened < 100.f) m_Events[i].m_flPercentageOpened += 228.f * g_pGlobals->frametime;
				else if (m_Events[i].m_flPercentageOpened > 100.f) m_Events[i].m_flPercentageOpened = 100.f;

				//D::Text(iScreenWidth - (flProgress * m_Events[i].m_flPercentageOpened), 100 + (i * 15.f), szString);
				//D::Text(iScreenWidth - (flProgress * m_Events[i].m_flPercentageOpened), 100 + (i * 15.f), Color::White(), false, false, Font::ESP, m_Events[i].m_szText);
			//	D::Text(-textRect.right + (flProgress * m_Events[i].m_flPercentageOpened), 30 + (i * 15.f), Color::White(), false, false, Font::ESP, m_Events[i].m_szText);
				
				D::Text(-textRect.right + (flProgress * m_Events[i].m_flPercentageOpened), 30 + (i * 15.f), Color(Options::Misc::LogColor[0], Options::Misc::LogColor[1], Options::Misc::LogColor[2], Options::Misc::LogColor[3]), false, false, Font::ESP, m_Events[i].m_szText);
			}
			else
			{
				m_Events.erase(m_Events.begin() + i);
				i--;
			}
		}
	}
}