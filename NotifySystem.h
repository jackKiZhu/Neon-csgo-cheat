#pragma once
#define MakeNotify NotifySystem::Notify

class Notify_t
{
public:
	string m_szText;
	float m_flTime;
	Notify_t()
	{
		m_szText = "";
		m_flTime = g_pGlobals->curtime;
	}
	Notify_t(string szText)
	{
		m_szText = szText;
		m_flTime = g_pGlobals->curtime;
	}
};

namespace NotifySystem
{
	vector<Notify_t> m_NotifyList;

	void Notify(string szText)
	{
		m_NotifyList.push_back(Notify_t(szText));
	}

	void Render()
	{
		const float NOTIFY_ANIM_TIME = 0.3f;
		const float NOTIFY_STAY_TIME = 4.f;

		int iScreenX, iScreenY;
		g_pEngine->GetScreenSize(iScreenX, iScreenY);
		float flCurTime = g_pGlobals->curtime;

		for (int i = 0; i < m_NotifyList.size(); i++)
		{
			auto notify = m_NotifyList[i];
			const int NOTFIY_SPACE_BEFORE = 30;
			const int NOTIFY_SPACE_AFTER = 10;
			const int NOTIFY_WIDTH = D::GetTextSize(notify.m_szText.c_str(), Font::ESP).right + NOTIFY_SPACE_AFTER + NOTFIY_SPACE_BEFORE;
			const int NOTIFY_HEIGHT = 30;
			int NOTIFY_X = iScreenX - NOTIFY_WIDTH;
			int NOTIFY_Y = 0 + (i * (NOTIFY_HEIGHT + 1)); 
			int NOTIFY_ALPHA = 255;

			if (flCurTime < notify.m_flTime + NOTIFY_ANIM_TIME) // animate apearing
			{
				NOTIFY_X = iScreenX - NOTIFY_WIDTH * ((flCurTime - notify.m_flTime) * (1.f / NOTIFY_ANIM_TIME));
			}
			else if (flCurTime < notify.m_flTime + NOTIFY_STAY_TIME) // normal rendering
			{
				;
			}
			else if (flCurTime < notify.m_flTime + NOTIFY_STAY_TIME + NOTIFY_ANIM_TIME) // animate fade out
			{
				NOTIFY_ALPHA = 255.f * (((notify.m_flTime + NOTIFY_STAY_TIME + NOTIFY_ANIM_TIME) - flCurTime) * (1.f / NOTIFY_ANIM_TIME));
			} 
			else // end shit
			{
				m_NotifyList.erase(m_NotifyList.begin() + i); // erase
				i--;
				continue;
			}
			//MultiColor
			D::m_pDrawList->AddRectFilled({ (float)NOTIFY_X + 100.f, (float)NOTIFY_Y }, { (float)(NOTIFY_X + NOTIFY_WIDTH) , (float)(NOTIFY_Y + NOTIFY_HEIGHT) }, ImColor(1, 10, 24, 255), ImColor(0, 0, 0, NOTIFY_ALPHA), ImColor(0, 0, 0, NOTIFY_ALPHA));
			D::m_pDrawList->AddRectFilled({ (float)NOTIFY_X + 100.f, (float)(NOTIFY_Y + NOTIFY_HEIGHT) }, { (float)(NOTIFY_X + NOTIFY_WIDTH) , (float)(NOTIFY_Y + NOTIFY_HEIGHT + 1) }, ImColor(1, 10, 24, 255), ImColor(255, 255, 255, NOTIFY_ALPHA), ImColor(255, 255, 255, NOTIFY_ALPHA));
			D::Text(NOTIFY_X + NOTFIY_SPACE_BEFORE + 100.f, NOTIFY_Y + (NOTIFY_HEIGHT / 2), {255, 255, 255, 255}, false, true, Font::ESP, notify.m_szText.c_str());//Color::White(NOTIFY_ALPHA),
		}
	}
}