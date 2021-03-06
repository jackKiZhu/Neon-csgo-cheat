

class IRefCounted
{
public:
	virtual int AddRef() = 0;
	virtual int Release() = 0;
};

class ITexture
{
public:
	virtual const char* GetName(void) const = 0;
	virtual int GetMappingWidth() const = 0;
	virtual int GetMappingHeight() const = 0;
	virtual int GetActualWidth() const = 0;
	virtual int GetActualHeight() const = 0;
	virtual int GetNumAnimationFrames() const = 0;
	virtual bool IsTranslucent() const = 0;
	virtual bool IsMipmapped() const = 0;
};


class IMatRenderContext : IRefCounted {
public:
	int Release()
	{
		typedef int(__thiscall* CreateMaterialFn)(void*);
		return CallVFunc<CreateMaterialFn>(this, 1)(this);
	}
	//DVMethod(int(), Release, StaticVIndex<1>);

	void SetRenderTarget(ITexture* pTexture)
	{
		typedef void(__thiscall* CreateMaterialFn)(void*, ITexture*);
		return CallVFunc<CreateMaterialFn>(this, 6)(this, pTexture);
	}

	//	DVMethod(void(ITexture* pTexture), SetRenderTarget, StaticVIndex<6>);

	void PushRenderTargetAndViewport()
	{
		typedef void(__thiscall* CreateMaterialFn)(void*);
		return CallVFunc<CreateMaterialFn>(this, 119)(this);
	}
	//	DVMethod(void(), PushRenderTargetAndViewport, StaticVIndex<118>);
	void PopRenderTargetAndViewport()
	{
		typedef void(__thiscall* CreateMaterialFn)(void*);
		return CallVFunc<CreateMaterialFn>(this, 120)(this);
	}

	//DVMethod(void(), PopRenderTargetAndViewport, StaticVIndex<119>);


	void DrawScreenSpaceRectangle(IMaterial* pMaterial,
		int destX, int destY, int width, int height,
		float srcTextureX0, float srcTextureY0, float srcTextureX1, float srcTextureY1,
		int srcTextureWidth, int srcTextureHeight,
		void* pClientRenderable, int nXDice, int nYDice)
	{
		typedef void(__thiscall* CreateMaterialFn)(void*, IMaterial*,
			int, int, int, int,
			float, float, float, float,
			int, int,
			void*, int, int);
		return CallVFunc<CreateMaterialFn>(this, 114)(this, pMaterial,
			destX, destY, width, height,
			srcTextureX0, srcTextureY0, srcTextureX1, srcTextureY1,
			srcTextureWidth, srcTextureHeight,
			pClientRenderable, nXDice, nYDice);
	}


	//DVMethod(void(
	//	IMaterial* pMaterial,
	//	int destX, int destY, int width, int height,
	//	float srcTextureX0, float srcTextureY0, float srcTextureX1, float srcTextureY1,
	//	int srcTextureWidth, int srcTextureHeight,
	//	void* pClientRenderable, int nXDice, int nYDice
	//	), DrawScreenSpaceRectangle, StaticVIndex<113>);
};


class IVModelRender
{
public:
	void ForcedMaterialOverride(IMaterial* newMaterial, OverrideType_t nOverrideType = OVERRIDE_NORMAL, int unk = 0)
	{
		typedef void(__thiscall* ForcedMaterialOverrideFn)(void*, IMaterial*, OverrideType_t, int);
		CallVFunc<ForcedMaterialOverrideFn>(this, 1)(this, newMaterial, nOverrideType, unk);
	}

	bool IsForcedMaterialOverride()
	{
		typedef bool(__thiscall* ForcedMaterialOverrideFn)(void*);
		return CallVFunc<ForcedMaterialOverrideFn>(this, 2)(this);
	}

	bool DrawModelSetup(ModelRenderInfo_t &pInfo, DrawModelState_t *pState, matrix3x4 **ppBoneToWorldOut)
	{
		typedef bool(__thiscall* DrawModelSetupFn)(void*, ModelRenderInfo_t&, DrawModelState_t*, matrix3x4**);
		return CallVFunc<DrawModelSetupFn>(this, 20)(this, pInfo, pState, ppBoneToWorldOut);
	}

	void DrawModelExecute(IMatRenderContext* matctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4* pCustomBoneToWorld)
	{
		typedef void(__thiscall* DrawModelExecuteFn)(void*, IMatRenderContext*, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4*);
		CallVFunc<DrawModelExecuteFn>(this, 21)(this, matctx, state, pInfo, pCustomBoneToWorld);
	}
};

IVModelRender* g_pModelRender;