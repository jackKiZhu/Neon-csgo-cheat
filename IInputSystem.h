class IInputSystem
{
public:
	virtual void AttachToWindow(void* hWnd) = 0;
	virtual void DetachFromWindow() = 0;

	// Enables/disables input. PollInputState will not update current 
	// button/analog states when it is called if the system is disabled.
	virtual void EnableInput(bool bEnable) = 0;
	void IInputSystem::GetCursorPosition(int* m_pX, int* m_pY)
	{
		typedef void(__thiscall* OriginalFn)(void*, int*, int*);
		return CallVFunc<OriginalFn>(this, 56)(this, m_pX, m_pY);
	}

	void IInputSystem::SetMouseCursorVisible(bool visible)
	{
		typedef void(__thiscall* OriginalFn)(void*, bool);
		return CallVFunc<OriginalFn>(this, 59)(this, visible);
	}


};

IInputSystem* g_pInput;