class IVDebugOverlay
{
public:
	virtual void AddEntityTextOverlay(int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) = 0;
	virtual void AddBoxOverlay(const Vector3& origin, const Vector3& mins, const Vector3& max, Vector3 const& orientation, int r, int g, int b, int a, float duration = 0) = 0;
	virtual void AddSphereOverlay(const Vector3& vOrigin, float flRadius, int nTheta, int nPhi, int r, int g, int b, int a, float flDuration = 0) = 0;
	virtual void AddTriangleOverlay(const Vector3& p1, const Vector3& p2, const Vector3& p3, int r, int g, int b, int a, bool noDepthTest, float duration = 0) = 0;
	virtual void AddBoxOverlayNew(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, int r, int g, int b, int a) = 0;
	virtual void AddLineOverlay(const Vector3& origin, const Vector3& dest, int r, int g, int b, bool noDepthTest, float duration = 0) = 0;
	virtual void AddTextOverlay(const Vector3& origin, float duration, const char *format, ...) = 0;
	virtual void AddTextOverlay(const Vector3& origin, int line_offset, float duration, const char *format, ...) = 0;
	virtual void AddScreenTextOverlay(float flXPos, float flYPos, float flDuration, int r, int g, int b, int a, const char *text) = 0;
	virtual void AddSweptBoxOverlay(const Vector3& start, const Vector3& end, const Vector3& mins, const Vector3& max, const Vector3 & angles, int r, int g, int b, int a, float flDuration = 0) = 0;
	virtual void AddGridOverlay(const Vector3& origin) = 0;
	virtual void AddCoordFrameOverlay(const matrix3x4& frame, float flScale, int vColorTable[3][3] = NULL) = 0;

	virtual int ScreenPosition(const Vector3& point, Vector3& screen) = 0;
	virtual int ScreenPosition(float flXPos, float flYPos, Vector3& screen) = 0;

	virtual void* *GetFirst(void) = 0;
	virtual void* *GetNext(void* current) = 0;
	virtual void ClearDeadOverlays(void) = 0;
	virtual void ClearAllOverlays() = 0;

	virtual void AddTextOverlayRGB(const Vector3& origin, int line_offset, float duration, float r, float g, float b, float alpha, const char *format, ...) = 0;
	virtual void AddTextOverlayRGB(const Vector3& origin, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) = 0;

	virtual void AddLineOverlayAlpha(const Vector3& origin, const Vector3& dest, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
	//virtual void Unknown1() = 0;
	virtual void AddBoxOverlay2(const Vector3& origin, const Vector3& mins, const Vector3& max, Vector3 const& orientation, const Color& faceColor, const Color& edgeColor, float duration) = 0;

	virtual void PurgeTextOverlays() = 0;

	virtual void NewOverlay(const Vector3& origin1, const Vector3& origin2, int a3, int r, int g, int b, int a, int unusedParam) = 0;
};

IVDebugOverlay* g_pDebugOverlay;