#pragma once

#define POINTERCHK( pointer ) ( pointer  && pointer !=0  && HIWORD( pointer ) )
#define M_PI		3.14159265358979323846
#define M_PI_F		((float)(M_PI))
#define PITCH 0
#define YAW 1
#define ROLL 2

namespace Math
{
	typedef float(*RandomFloat_t)(float, float);
	float vstRandomFloat(float min, float max) {
		static RandomFloat_t m_RandomFloat;
		if (!m_RandomFloat)
			m_RandomFloat = (RandomFloat_t)_GetProcAddress(_GetModuleHandleA("vstdlib.dll"), "RandomFloat");

		return m_RandomFloat(min, max);
	}

	typedef void(*RandomSeed_t)(UINT);
	void vstRandomSeed(UINT seed) {
		static RandomSeed_t m_RandomSeed;
		if (!m_RandomSeed)
			m_RandomSeed = (RandomSeed_t)_GetProcAddress(_GetModuleHandleA("vstdlib.dll"), "RandomSeed");

		m_RandomSeed(seed);
	}

	inline void Clamp(int& value, int min, int max)
	{
		if (value < min) value = min;
		if (value > max) value = max;
	}

	inline void Clamp(float& value, float min, float max)
	{
		if (value < min) value = min;
		if (value > max) value = max;
	}

	inline const int RandomInt(int low, int high) {
		return rand() % (high - low + 1) + low;
	}

	inline const float RandomFloat(float low, float high) {
		return RandomInt(low * 100.f, high * 100.f) / 100.f;
	}

	inline float DotProduct(const Vector3& a, const Vector3& b)
	{
		return(a.x*b.x + a.y*b.y + a.z*b.z);
	}

	inline void VectorTransform(const Vector3& in1, const matrix3x4& in2, Vector3& out)
	{
		out.x = in1.x * in2[0][0] + in1.y * in2[0][1] + in1.z * in2[0][2] + in2[0][3];
		out.y = in1.x * in2[1][0] + in1.y * in2[1][1] + in1.z * in2[1][2] + in2[1][3];
		out.z = in1.x * in2[2][0] + in1.y * in2[2][1] + in1.z * in2[2][2] + in2[2][3];
	}

	bool WorldToScreen(Vector3 &vOrigin, Vector3 &vScreen, bool bOffscreen = false)
	{
		const matrix4x4& worldToScreen = *(matrix4x4*)(*(PDWORD)(Offsets::WorldToScreen) + 988);
		if (!POINTERCHK(worldToScreen))
			return false;

		int ScrW, ScrH;
		g_pEngine->GetScreenSize(ScrW, ScrH);

		Vector3 vReturn;
		float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3];
		vReturn.z = 0;
		if (w > 0.01)
		{
			float inverseWidth = 1 / w;
			vReturn.x = (ScrW / 2) + (0.5 * ((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * inverseWidth) * ScrW + 0.5);
			vReturn.y = (ScrH / 2) - (0.5 * ((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * inverseWidth) * ScrH + 0.5);
			vScreen = vReturn;
			return true;
		}
		return false;
	}

	void FindPoint(Vector3 &point, int screenwidth, int screenheight, int degrees)
	{
		float x2 = screenwidth / 2;
		float y2 = screenheight / 2;

		float d = sqrt(pow((point.x - x2), 2) + (pow((point.y - y2), 2))); //Distance
		float r = degrees / d; //Segment ratio

		point.x = r * point.x + (1 - r) * x2; //find point that divides the segment
		point.y = r * point.y + (1 - r) * y2; //into the ratio (1-r):r
	}

	bool ScreenTransform(Vector3 &point, Vector3 &screen)
	{
		//const VMatrix &worldToScreen = g_pEngine->WorldToScreenMatrix();
		const matrix4x4& worldToScreen = *(matrix4x4*)(*(PDWORD)(Offsets::WorldToScreen) + 988);
		if (!POINTERCHK(worldToScreen))
			return false;

		float w;
		screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
		screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
		w = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
		screen.z = 0.0f;
		bool behind = false;
		if (w < 0.001f) {
			behind = true;
			float invw = -1.0f / w;
			screen.x *= invw;
			screen.y *= invw;
		}
		else {
			behind = false;
			float invw = 1.0f / w;
			screen.x *= invw;
			screen.y *= invw;
		}
		return behind;
	}

	bool WorldToScreen3D(Vector3 &vOrigin, Vector3 &vScreen)
	{
		bool bBehind = ScreenTransform(vOrigin, vScreen);
		int iScreenWidth, iScreenHeight;
		g_pEngine->GetScreenSize(iScreenWidth, iScreenHeight);
		float x = iScreenWidth / 2;
		float y = iScreenHeight / 2;
		x += 0.5 * vScreen.x * iScreenWidth + 0.5;
		y -= 0.5 * vScreen.y * iScreenHeight + 0.5;
		vScreen.x = x;
		vScreen.y = y;
		
		int i = 40;
		if (vScreen.x < i) vScreen.x = i;
		if (vScreen.y < i) vScreen.y = i;
		if (vScreen.x > iScreenWidth - i) vScreen.x = iScreenWidth - i;
		if (vScreen.y > iScreenHeight - i) vScreen.y = iScreenHeight - i;
		if (bBehind)
		{
			if (vScreen.x < iScreenWidth / 2) vScreen.x = i;
			else if (vScreen.x > iScreenWidth / 2) vScreen.x = iScreenWidth - i;

			//if (vScreen.y < iScreenHeight / 2) vScreen.y = i;
			//else if (vScreen.y > iScreenHeight / 2) vScreen.y = iScreenHeight - i;
		}
		return true;

		/*if (vScreen.x > iScreenHeight || vScreen.x < 0 || vScreen.y > iScreenWidth || vScreen.y < 0 || st)
		{
			FindPoint(vScreen, iScreenWidth, iScreenHeight, iScreenHeight / 2);
			return true;
		}
		return false;*/
	}

	float CalcBombDamageArmor(float flDamage, int ArmorValue)
	{
		float flArmorRatio = 0.5f;
		float flArmorBonus = 0.5f;
		if (ArmorValue > 0) {
			float flNew = flDamage * flArmorRatio;
			float flArmor = (flDamage - flNew) * flArmorBonus;

			if (flArmor > static_cast<float>(ArmorValue)) {
				flArmor = static_cast<float>(ArmorValue) * (1.f / flArmorBonus);
				flNew = flDamage - flArmor;
			}

			flDamage = flNew;
		}
		return flDamage;
	}

	float CalcBombDamage(const Vector3 vecLocalPos, const Vector3 vecBombPos, int iArmorValue) // pasted, thanks Casual_Hacker
	{
		float flDistance = vecLocalPos.DistTo(vecBombPos);

		float a = 450.7f;
		float b = 75.68f;
		float c = 789.2f;
		float d = ((flDistance - b) / c);
		float flDamage = a*exp(-d * d);

		return max((int)ceilf(CalcBombDamageArmor(flDamage, iArmorValue)), 0);
	}

	void VectorAngles(const Vector3& forward, Vector3& angles)
	{
		if (forward.y == 0.0f && forward.x == 0.0f)
		{
			angles.x = (forward.z > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
			angles.y = 0.0f;  //yaw left/right
		}
		else
		{
			angles.x = atan2(-forward.z, forward.Length2d()) * -180 / M_PI;
			angles.y = atan2(forward.y, forward.x) * 180 / M_PI;

			if (angles.y > 90)
				angles.y -= 180;
			else if (angles.y < 90)
				angles.y += 180;
			else if (angles.y == 90)
				angles.y = 0;
		}

		angles.z = 0.0f;
	}

	void VectorAngles2(const Vector3 &vecForward, Vector3 &vecAngles)
	{
		Vector3 vecView;
		if (vecForward[1] == 0.f && vecForward[0] == 0.f)
		{
			vecView[0] = 0.f;
			vecView[1] = 0.f;
		}
		else
		{
			vecView[1] = atan2(vecForward[1], vecForward[0]) * 180.f / M_PI;

			if (vecView[1] < 0.f)
				vecView[1] += 360.f;

			vecView[2] = sqrt(vecForward[0] * vecForward[0] + vecForward[1] * vecForward[1]);

			vecView[0] = atan2(vecForward[2], vecView[2]) * 180.f / M_PI;
		}

		vecAngles[0] = -vecView[0];
		vecAngles[1] = vecView[1];
		vecAngles[2] = 0.f;
	}

	QAngle CalculateAngle(const Vector3 in, const Vector3 out)
	{
		Vector3 angles;
		Vector3 delta = in - out;

		VectorAngles(delta, angles);
		//Math::NormalizeAngle(angles);
		delta.Normalize();

		return angles;
	}

	void ClampAngle(QAngle& angle)
	{
		while (angle.x < -89.0f)
			angle.x = -89.0f;
		while (angle.x > 89.0f)
			angle.x = 89.0f;

		while (angle.y < -180.0f)
			angle.y += 360.0f;
		while (angle.y > 180.0f)
			angle.y -= 360.0f;

		angle.z = 0;
	}


	template<class T>
	void Normalize3(T& vec) {
		for (auto i = 0; i < 2; i++) {
			while (vec[i] < -180.0f) vec[i] += 360.0f;
			while (vec[i] > 180.0f) vec[i] -= 360.0f;
		}
		vec[2] = 0.f;
	}

	void FixAngles(QAngle& angles) {
		Normalize3(angles);
		ClampAngle(angles);
	}

	void NormalizeAngle(QAngle& vAngles)
	{
		if (vAngles.x > 89.0f && vAngles.x <= 180.0f)
			vAngles.x = 89.0f;
		while (vAngles.x > 180.f)
			vAngles.x -= 360.f;
		while (vAngles.x < -89.0f)
			vAngles.x = -89.0f;
		while (vAngles.y > 180.f)
			vAngles.y -= 360.f;
		while (vAngles.y < -180.f)
			vAngles.y += 360.f;
		vAngles.z = 0;
	}

	float NormalizeF(float angle)
	{
		while (angle > 180.f)
			angle -= 360.f;

		while (angle < -180.f)
			angle += 360.f;

		return angle;
	}

	float VectorNormalize(Vector3& v)
	{
		float l = v.Length();
		if (l != 0.0f)
		{
			v /= l;
		}
		else
		{
			// FIXME: 
			// Just copying the existing implemenation; shouldn't res.z == 0?
			v.x = v.y = 0.0f; v.z = 1.0f;
		}
		return l;
	}
	
	float Rad2Deg(float x)
	{
		return (x * (180.0f / M_PI));
	}

	float Deg2Rad(float x)
	{
		return (x * (M_PI / 180.0f));
	}

	void SinCos(float x, float* s, float* c)
	{
		__asm
		{
			fld dword ptr[x]
			fsincos
			mov edx, dword ptr[c]
			mov eax, dword ptr[s]
			fstp dword ptr[edx]
			fstp dword ptr[eax]
		}
	}

	void SinCos(float x, float &s, float &c)
	{
		__asm
		{
			fld dword ptr[x]
			fsincos
			mov edx, dword ptr[c]
			mov eax, dword ptr[s]
			fstp dword ptr[edx]
			fstp dword ptr[eax]
		}
	}

	void AngleVectors(const Vector3& angles, Vector3* forward, Vector3* right, Vector3* up)
	{
		float sr, sp, sy, cr, cp, cy;

		SinCos(Deg2Rad(angles.x), &sp, &cp);
		SinCos(Deg2Rad(angles.y), &sy, &cy);
		SinCos(Deg2Rad(angles.z), &sr, &cr);

		if (forward)
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		if (right)
		{
			right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
			right->y = (-1 * sr * sp * sy + -1 * cr * cy);
			right->z = -1 * sr * cp;
		}

		if (up)
		{
			up->x = (cr * sp * cy + -sr * -sy);
			up->y = (cr * sp * sy + -sr * cy);
			up->z = cr * cp;
		}
	}

	void MatrixSetColumn(const Vector3 &in, int column, matrix3x4& out)
	{
		out[0][column] = in.x;
		out[1][column] = in.y;
		out[2][column] = in.z;
	}

	void AngleMatrix(const QAngle &angles, matrix3x4& matrix)
	{
		float sr, sp, sy, cr, cp, cy;
		SinCos(Deg2Rad(angles[YAW]), &sy, &cy);
		SinCos(Deg2Rad(angles[PITCH]), &sp, &cp);
		SinCos(Deg2Rad(angles[ROLL]), &sr, &cr);

		// matrix = (YAW * PITCH) * ROLL
		matrix[0][0] = cp*cy;
		matrix[1][0] = cp*sy;
		matrix[2][0] = -sp;

		float crcy = cr*cy;
		float crsy = cr*sy;
		float srcy = sr*cy;
		float srsy = sr*sy;
		matrix[0][1] = sp*srcy - crsy;
		matrix[1][1] = sp*srsy + crcy;
		matrix[2][1] = sr*cp;

		matrix[0][2] = (sp*crcy + srsy);
		matrix[1][2] = (sp*crsy - srcy);
		matrix[2][2] = cr*cp;

		matrix[0][3] = 0.0f;
		matrix[1][3] = 0.0f;
		matrix[2][3] = 0.0f;
	}

	void AngleMatrix(const QAngle &angles, const Vector3 &position, matrix3x4& matrix)
	{
		AngleMatrix(angles, matrix);
		MatrixSetColumn(position, 3, matrix);
	}

	bool RotatePoint(Vector3& p, float size, float x, float y, float a)
	{
		a = Math::Deg2Rad(a + 90.f);
		float s = sin(a);
		float c = cos(a);
		float cs = (size / 2);
		float cx = x + cs;
		float cy = y + cs;

		// translate point back to origin:
		p.x -= cx;
		p.y -= cy;

		// rotate point
		float xnew = p.x * c - p.y * s;
		float ynew = p.x * s + p.y * c;

		// translate point back:
		p.x = xnew + cx;
		p.y = ynew + cy;

		return true;
	}
};