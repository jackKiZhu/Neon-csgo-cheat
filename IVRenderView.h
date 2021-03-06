#pragma once

class IVRenderView
{
public:
	void SetBlend(float blend)
	{
		typedef void(__thiscall* SetBlendFn)(void*, float);
		CallVFunc< SetBlendFn >(this, 4)(this, blend);
	}

	void SetColorModulation(const float* color)
	{
		typedef void(__thiscall* SetColorModulationFn)(void*, const float*);
		CallVFunc< SetColorModulationFn >(this, 6)(this, color);
	}

	void GetColorModulation(float* blend)
	{
		typedef void(__thiscall* GetColorModulationFn)(void*, float*);
		CallVFunc< GetColorModulationFn >(this, 7)(this, blend);
	}
};

IVRenderView* g_pRenderView;