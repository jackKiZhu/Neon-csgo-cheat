#pragma once

class ISoundClient
{
public:
	/*void ISoundClient::GetCursorPosition(int* m_pX, int* m_pY)
	{
		typedef void(__thiscall* OriginalFn)(void*, int*, int*);
		return CallVFunc<OriginalFn>(this, 56)(this, m_pX, m_pY);
	}*/
};

ISoundClient* g_pSoundClient;