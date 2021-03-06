
#define	HITGROUP_GENERIC		0
#define	HITGROUP_HEAD			1
#define	HITGROUP_CHEST			2
#define	HITGROUP_STOMACH		3
#define HITGROUP_LEFTARM		4	
#define HITGROUP_RIGHTARM		5
#define HITGROUP_LEFTLEG		6
#define HITGROUP_RIGHTLEG		7
#define HITGROUP_GEAR			10

#define	CONTENTS_SOLID			0x1
#define	CONTENTS_WINDOW			0x2
#define CONTENTS_GRATE			0x8
#define CONTENTS_MOVEABLE		0x4000
#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000
#define	CONTENTS_MONSTER		0x2000000
#define	CONTENTS_DEBRIS			0x4000000
#define CONTENTS_HITBOX			0x40000000

#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define	MASK_AWALL					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define	MASK_AUTOWALL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
#define MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)

#define SURF_HITBOX		0x8000	// surface is part of a hitbox

class CBaseTrace
{
public:
	Vector3			startpos;
	Vector3			endpos;
	cplane_t		plane;

	float			fraction;

	int				contents;
	unsigned short	dispFlags;

	bool			allsolid;
	bool			startsolid;

	CBaseTrace() {}
};

class CGameTrace : public CBaseTrace
{
public:
	bool                    DidHitWorld() const;
	bool                    DidHitNonWorldEntity() const;
	int                     GetEntityIndex() const;
	inline bool             DidHit() { return fraction < 1.0f || allsolid || startsolid; }
	bool					IsVisible() const;

public:

	float                   fractionleftsolid;
	csurface_t              surface;
	int                     hitgroup;
	short                   physicsbone;
	unsigned short          worldSurfaceIndex;
	IClientEntity*          m_pEnt;
	int                     hitbox;

	CGameTrace() { }
	//CGameTrace(const CGameTrace& vOther);
};
typedef CGameTrace trace_t;

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(void *pEntity, int contentsMask) = 0;
	virtual TraceType_t	GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter
{
public:
	bool ShouldHitEntity(void* pEntityHandle, int contentsMask)
	{
		return pEntityHandle != pSkip;
	}
	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip;
};

class CTraceFilterSkipEntity : public ITraceFilter {
public:
	void *m_skip;

	CTraceFilterSkipEntity( IHandleEntity *pEntityHandle ) {
		m_skip = pEntityHandle;
	}

	virtual bool ShouldHitEntity( void *pEntityHandle, int /*contentsMask*/ )  {
		return !( pEntityHandle == m_skip );
	}

	virtual TraceType_t GetTraceType() const {
		return TraceType_t::TRACE_EVERYTHING;
	}
};

class CTraceFilterEntitiesOnly : public ITraceFilter
{
public:
	bool ShouldHitEntity(void* pEntityHandle, int contentsMask)
	{
		return pEntityHandle != pSkip;
	}
	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_ENTITIES_ONLY;
	}

	void* pSkip;
};

class IEngineTrace
{
public:
	int GetPointContents(const Vector3& vecAbsPosition, UINT nMask, IClientEntity** ppEntity = NULL)
	{
		typedef int(__thiscall* OriginalFn)(void*, const Vector3&, UINT, IClientEntity**);
		return CallVFunc<OriginalFn>(this, 0)(this, vecAbsPosition, nMask, ppEntity);
	}

	void ClipRayToEntity(const Ray_t &ray, unsigned int fMask, IClientEntity* pEnt, trace_t *pTrace)
	{
		typedef void(__thiscall* GetPointContentsFn)(void*, const Ray_t&, unsigned int, IClientEntity*, trace_t*);
		return CallVFunc<GetPointContentsFn>(this, 3)(this, ray, fMask, pEnt, pTrace);
	}

	void TraceRay(const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) throw()
	{
		typedef void(__thiscall* TraceRayFn)(void*, const Ray_t&, unsigned int, ITraceFilter*, trace_t*);
		return CallVFunc<TraceRayFn>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
	}
};

IEngineTrace* g_pEngineTrace;
