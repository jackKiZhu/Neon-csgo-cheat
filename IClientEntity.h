//#ifndef Netvars_h
//#else
//#include "NetVars.h"
//#endif // !Netvars_h

class IClientEntity;
class IClientUnknown;
class IClientRenderable;
class IClientNetworkable;
class IClientThinkable;
class ICollideable;
class IClientAlphaProperty;
class IHandleEntity;

typedef unsigned long CBaseHandle;
class IHandleEntity
{
public:
	virtual ~IHandleEntity() {}
	virtual void SetRefEHandle(const CBaseHandle &handle) = 0;
	virtual const CBaseHandle& GetRefEHandle() const = 0;
};

class IClientUnknown : public IHandleEntity
{
public:
	virtual ICollideable*              GetCollideable() = 0;
	virtual IClientNetworkable*        GetClientNetworkable() = 0;
	virtual IClientRenderable*         GetClientRenderable() = 0;
	virtual IClientEntity*             GetIClientEntity() = 0;
	virtual IClientEntity*              GetBaseEntity() = 0;
	virtual IClientThinkable*          GetClientThinkable() = 0;
	virtual IClientAlphaProperty*      GetClientAlphaProperty() = 0;
};

typedef unsigned short ClientShadowHandle_t;
typedef unsigned short ClientRenderHandle_t;
typedef unsigned char uint8;
struct RenderableInstance_t
{
	uint8 m_nAlpha;
};
class IClientRenderable
{
public:
	virtual IClientUnknown*            GetClientUnknown() = 0;
	virtual Vector3 const&             GetRenderOrigin(void) = 0;
	virtual Vector3 const&             GetRenderAngles(void) = 0;
	virtual bool                       ShouldDraw(void) = 0;
	virtual int                        GetRenderFlags(void) = 0; // ERENDERFLAGS_xxx
	virtual void                       Unused(void) const {}
	virtual ClientShadowHandle_t       GetShadowHandle() const = 0;
	virtual ClientRenderHandle_t&      RenderHandle() = 0;
	virtual model_t*		           GetModel() const = 0;
	virtual int                        DrawModel(int flags, uint8_t instance) = 0;
	virtual int                        GetBody() = 0; // 10
	virtual void                       GetColorModulation(float* color) = 0;
	virtual bool                       LODTest() = 0;
	virtual bool                       SetupBones(matrix3x4 *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual void                       SetupWeights(const matrix3x4 *pBoneToWorld, int nFlexWeightCount, float *pFlexWeights, float *pFlexDelayedWeights) = 0;
	virtual void                       DoAnimationEvents(void) = 0;
	virtual void* /*IPVSNotify*/       GetPVSNotifyInterface() = 0;
	virtual void                       GetRenderBounds(Vector3& mins, Vector3& maxs) = 0;
	virtual void                       GetRenderBoundsWorldspace(Vector3& mins, Vector3& maxs) = 0;
	virtual void                       GetShadowRenderBounds(Vector3 &mins, Vector3 &maxs, int /*ShadowType_t*/ shadowType) = 0;
	virtual bool                       ShouldReceiveProjectedTextures(int flags) = 0; // 20
	virtual bool                       GetShadowCastDistance(float *pDist, int /*ShadowType_t*/ shadowType) const = 0;
	virtual bool                       GetShadowCastDirection(Vector3 *pDirection, int /*ShadowType_t*/ shadowType) const = 0;
	virtual bool                       IsShadowDirty() = 0;
	virtual void                       MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable*         GetShadowParent() = 0;
	virtual IClientRenderable*         FirstShadowChild() = 0;
	virtual IClientRenderable*         NextShadowPeer() = 0;
	virtual int /*ShadowType_t*/       ShadowCastType() = 0;
	virtual void                       CreateModelInstance() = 0;
	virtual ModelInstanceHandle_t      GetModelInstance() = 0; // 30
	virtual const matrix3x4&		   RenderableToWorldTransform() = 0;
	virtual int                        LookupAttachment(const char *pAttachmentName) = 0;
	virtual   bool                     GetAttachment(int number, Vector3 &origin, Vector3 &angles) = 0;
	virtual bool                       GetAttachment(int number, matrix3x4 &matrix) = 0;
	virtual float*                     GetRenderClipPlane(void) = 0;
	virtual int                        GetSkin() = 0;
	virtual void                       OnThreadedDrawSetup() = 0;
	virtual bool                       UsesFlexDelayedWeights() = 0;
	virtual void                       RecordToolMessage() = 0;
	virtual bool                       ShouldDrawForSplitScreenUser(int nSlot) = 0; // 40
	virtual uint8                      OverrideAlphaModulation(uint8 nAlpha) = 0;
	virtual uint8                      OverrideShadowAlphaModulation(uint8 nAlpha) = 0;
};

class IClientUnknown;
class ClientClass;
class bf_read;

class IClientNetworkable
{
public:
	virtual IClientUnknown*  GetIClientUnknown() = 0;
	virtual void             Release() = 0;
	virtual ClientClass*     GetClientClass() = 0;
	virtual void             NotifyShouldTransmit(int state) = 0;
	virtual void             OnPreDataChanged(int updateType) = 0;
	virtual void             OnDataChanged(int updateType) = 0;
	virtual void             PreDataUpdate(int updateType) = 0;
	virtual void             PostDataUpdate(int updateType) = 0;
private:
	virtual void             _Unknown(void) = 0;
public:
	virtual bool             IsDormant(void) = 0;
	virtual int              GetIndex(void) const = 0;
	virtual void             ReceiveMessage(int classID, bf_read& msg) = 0;
	virtual void*            GetDataTableBasePtr() = 0;
	virtual void             SetDestroyedOnRecreateEntities(void) = 0;
};

class CClientThinkHandlePtr;
typedef CClientThinkHandlePtr* ClientThinkHandle_t;
class IClientThinkable
{
public:
	virtual IClientUnknown*		GetIClientUnknown() = 0;
	virtual void				ClientThink() = 0;
	virtual ClientThinkHandle_t	GetThinkHandle() = 0;
	virtual void				SetThinkHandle(ClientThinkHandle_t hThink) = 0;
	virtual void				Release() = 0;
};
extern std::unordered_map<std::string, std::unordered_map<std::string, size_t>> g_NetVars;
struct SpatializationInfo_t;
class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual void             Release(void) = 0;
	virtual const Vector3    GetAbsOrigin(void) const = 0;
	virtual const QAngle     GetAbsAngles(void) const = 0;

	

	void SetAbsAngles(Vector3 angles){
		using SetAbsAnglesFn = void(__thiscall*)(void*, const QAngle & angles);
		static SetAbsAnglesFn SetAbsAngles = (SetAbsAnglesFn)SetAbsOffset;	
		SetAbsAngles(this, angles);
	}

	void SetModelIndexVirtual(int index)
	{
		typedef void(__thiscall* SetModelIndexFn)(void*, int);
		CallVFunc<SetModelIndexFn>(this, 75)(this, index);
	}

	int GetModelIndex()
	{
		return *(int*)((DWORD)this + 0x258);
	}

	void SetModelIndex(int index)
	{
		*(reinterpret_cast<int*>(uintptr_t(this) + 0x258)) = index;
	}
	Vector3 GetOrigin()
	{
		return *(Vector3*)((DWORD)this + 0x138);
	}

	QAngle Angles()
	{
		return *(Vector3*)((DWORD)this + 0x138);
	}
};