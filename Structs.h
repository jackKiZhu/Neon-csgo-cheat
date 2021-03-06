#include "CHC.h"
class model_t
{
public:
	void*   fnHandle;               //0x0000 
	char    szName[260];            //0x0004 
	__int32 nLoadFlags;             //0x0108 
	__int32 nServerCount;           //0x010C 
	__int32 type;                   //0x0110 
	__int32 flags;                  //0x0114 
	Vector3 vecMins;                //0x0118 
	Vector3 vecMaxs;                //0x0124 
	float   radius;                 //0x0130 
	char    pad[0x1C];              //0x0134
};//Size=0x0150

struct mstudiobone_t
{
	int sznameindex;

	inline char* pszName(void) const
	{
		return ((char *)this) + sznameindex;
	}

	int parent; // parent bone
	int bonecontroller[6]; // bone controller index, -1 == none

						   // default values
	Vector3 pos;
	Vector4 quat;
	Vector3 rot;
	// compression scale
	Vector3 posscale;
	Vector3 rotscale;

	matrix3x4 poseToBone;
	Vector4 qAlignment;
	int flags;
	int proctype;
	int procindex; // procedural rule
	mutable int physicsbone; // index into physically simulated bone
	inline void* pProcedure() const
	{
		if (procindex == 0)
			return NULL;
		else
			return (void *)(((BYTE *)this) + procindex);
	};
	int surfacepropidx; // index into string tablefor property name
	inline char* pszSurfaceProp(void) const
	{
		return ((char *)this) + surfacepropidx;
	}

	inline int GetSurfaceProp(void) const
	{
		return surfacepropLookup;
	}

	int contents; // See BSPFlags.h for the contents flags
	int surfacepropLookup; // this index must be cached by the loader, not saved in the file
	int unused[7]; // remove as appropriate
};


struct mstudiobbox_t
{
	int		bone;
	int		group;
	Vector3	bbmin;
	Vector3	bbmax;
	int		hitboxnameindex;
	int		pad[3];
	float	m_flRadius;
	int		pad2[4];

	char* getHitboxName()
	{
		if (hitboxnameindex == 0)
			return "";

		return ((char*)this) + hitboxnameindex;
	}
};

struct mstudiohitboxset_t
{
	int					sznameindex;
	inline char * const	pszName(void) const { return ((char *)this) + sznameindex; }
	int					numhitboxes;
	int					hitboxindex;
	inline mstudiobbox_t *pHitbox(int i) const { return (mstudiobbox_t*)(((unsigned char*)this) + hitboxindex) + i; };
};

struct mstudioposeparamdesc_t
{
	int					sznameindex;
	inline char * const pszName(void) const { return ((char *)this) + sznameindex; }
	int					flags;	// ????
	float				start;	// starting value
	float				end;	// ending value
	float				loop;	// looping range, 0 for no looping, 360 for rotations, etc.
};

#define  Assert( _exp )										((void)0)
struct studiohdr_t
{
	int id;
	int version;

	long checksum; // this has to be the same in the phy and vtx files to load!

	inline const char* pszName(void) const
	{
		return name;
	}

	char name[64];

	int length;

	Vector3 eyeposition; // ideal eye position

	Vector3 illumposition; // illumination center

	Vector3 hull_min; // ideal movement hull size
	Vector3 hull_max;

	Vector3 view_bbmin; // clipping bounding box
	Vector3 view_bbmax;

	int flags;

	int numbones; // bones
	int boneindex;

	inline mstudiobone_t* pBone(int i) const
	{
		Assert(i >= 0 && i < numbones);
		return (mstudiobone_t *)((DWORD)this + boneindex) + i;
	};
	int RemapSeqBone(int iSequence, int iLocalBone) const; // maps local sequence bone to global bone
	int RemapAnimBone(int iAnim, int iLocalBone) const; // maps local animations bone to global bone

	int numbonecontrollers; // bone controllers
	int bonecontrollerindex;
	
	int numhitboxsets;
	int hitboxsetindex;

	// Look up hitbox set by index
	mstudiohitboxset_t* pHitboxSet(int i) const
	{
		Assert(i >= 0 && i < numhitboxsets);
		return (mstudiohitboxset_t *)(((BYTE *)this) + hitboxsetindex) + i;
	};

	// Calls through to hitbox to determine size of specified set
	inline mstudiobbox_t* pHitbox(int i, int set) const
	{
		mstudiohitboxset_t const* s = pHitboxSet(set);
		if (!s)
			return NULL;

		return s->pHitbox(i);
	};

	// Calls through to set to get hitbox count for set
	inline int iHitboxCount(int set) const
	{
		mstudiohitboxset_t const* s = pHitboxSet(set);
		if (!s)
			return 0;

		return s->numhitboxes;
	};

	// file local animations? and sequences
	//private:
	int numlocalanim; // animations/poses
	int localanimindex; // animation descriptions

	int numlocalseq; // sequences
	int localseqindex;
	
	//public:
	bool SequencesAvailable() const
	{
		return true;
	}

	int GetNumSeq() const;
	int iRelativeAnim(int baseseq, int relanim) const; // maps seq local anim reference to global anim index
	int iRelativeSeq(int baseseq, int relseq) const; // maps seq local seq reference to global seq index

													 //private:
	mutable int activitylistversion; // initialization flag - have the sequences been indexed?
	mutable int eventsindexed;
	//public:
	int GetSequenceActivity(int iSequence);
	void SetSequenceActivity(int iSequence, int iActivity);
	int GetActivityListVersion(void);
	void SetActivityListVersion(int version) const;
	int GetEventListVersion(void);
	void SetEventListVersion(int version);

	// raw textures
	int numtextures;
	int textureindex;

	// raw textures search paths
	int numcdtextures;
	int cdtextureindex;

	inline char* pCdtexture(int i) const
	{
		return (((char *)this) + *((int *)(((BYTE *)this) + cdtextureindex) + i));
	};

	// replaceable textures tables
	int numskinref;
	int numskinfamilies;
	int skinindex;

	inline short* pSkinref(int i) const
	{
		return (short *)(((BYTE *)this) + skinindex) + i;
	};

	int numbodyparts;
	int bodypartindex;

	// added 02.12.2017
	int numlocalattachments;
	int localattachmentindex;
	int numlocalnodes;
	int localnodeindex;
	int localnodenameindex;
	int numflexdesc;
	int flexdescindex;
	int numflexcontrollers;
	int flexcontrollerindex;
	int numflexrules;
	int flexruleindex;
	int numikchains;
	int ikchainindex;
	int nummouths;
	int mouthindex;
	int numlocalposeparameters;
	int localposeparamindex;

	inline mstudioposeparamdesc_t *pLocalPoseParameter(int i) const { Assert(i >= 0 && i < numlocalposeparameters); return (mstudioposeparamdesc_t *)(((BYTE *)this) + localposeparamindex) + i; };

	int surfacepropindex;
	int keyvalueindex;
	int keyvaluesize;
	int numlocalikautoplaylocks;
	int localikautoplaylockindex;
	float mass;
	int contents;
	int numincludemodels;
	int includemodelindex;
	mutable void *virtualModel;
	int szanimblocknameindex;
	int numanimblocks;
	int animblockindex;
	mutable void *animblockModel;
	int bonetablebynameindex;
	void *pVertexBase;
	void *pIndexBase;
	BYTE constdirectionallightdot;
	BYTE rootLOD;
	BYTE numAllowedRootLODs;
	BYTE unused[1];
	int unused4;
	int numflexcontrollerui;
	int flexcontrolleruiindex;
	float flVertAnimFixedPointScale;
	int unused3[1];
	int studiohdr2index;
	int unused2[1];
};

typedef unsigned short ModelInstanceHandle_t;
struct ModelRenderInfo_t
{
	Vector3 origin;
	Vector3 angles;
	char pad[0x4];
	void* pRenderable;
	model_t* pModel;
	matrix3x4* pModelToWorld;
	matrix3x4* pLightingOffset;
	Vector3* pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;

	ModelRenderInfo_t()
	{
		pModelToWorld = nullptr;
		pLightingOffset = nullptr;
		pLightingOrigin = nullptr;
	}
};

struct DrawModelState_t
{
	void*					m_pStudioHdr;
	void*			        m_pStudioHWData;
	void*					m_pRenderable;
	const matrix3x4*        m_pModelToWorld;
	void*					m_decals;
	int                     m_drawFlags;
	int                     m_lod;
};


typedef struct player_info_s
{
	DWORD __pad0[2];
	int xuidlow;
	int xuidhigh;
	char name[128];//32
	int userid;
	char steamid[33];//32
	UINT steam3id;
	char friendsname[128];
	bool isfakeplayer;
	bool ishltv;
	DWORD customfiles[4];
	BYTE filesdownloaded;
	int __pad1;
} player_info_t;

//struct CViewSetup
//{
//	char _0x0000[16];
//	__int32 x;
//	__int32 x_old;
//	__int32 y;
//	__int32 y_old;
//	__int32 width;
//	__int32    width_old;
//	__int32 height;
//	__int32    height_old;
//	char _0x0030[128];
//	float fov;
//	float fovViewmodel;
//	Vector3 origin;
//	Vector3 angles;
//	float zNear;
//	float zFar;
//	float zNearViewmodel;
//	float zFarViewmodel;
//	float m_flAspectRatio;
//	float m_flNearBlurDepth;
//	float m_flNearFocusDepth;
//	float m_flFarFocusDepth;
//	float m_flFarBlurDepth;
//	float m_flNearBlurRadius;
//	float m_flFarBlurRadius;
//	float m_nDoFQuality;
//	__int32 m_nMotionBlurMode;
//	char _0x0104[68];
//	__int32 m_EdgeBlur;
//};
class CViewSetup {
public:
	int x;
	int oldX;
	int y;
	int oldY;
	int width;
	int oldWidth;
	int height;
	int oldHeight;

	bool m_bOrtho;
	float m_OrthoLeft;
	float m_OrthoTop;
	float m_OrthoRight;
	float m_OrthoBottom;

private:
	char pad1[0x7C];

public:
	float fov;
	float fovViewmodel;
	Vector3 origin;
	QAngle angles;

	float zNear;
	float zFar;
	float zNearViewmodel;
	float zFarViewmodel;

	float m_flAspectRatio;
	float m_flNearBlurDepth;
	float m_flNearFocusDepth;
	float m_flFarFocusDepth;
	float m_flFarBlurDepth;
	float m_flNearBlurRadius;
	float m_flFarBlurRadius;
	int m_nDoFQuality;
	void* m_nMotionBlurMode;

	float m_flShutterTime;
	Vector3 m_vShutterOpenPosition;
	QAngle m_shutterOpenAngles;
	Vector3 m_vShutterClosePosition;
	QAngle m_shutterCloseAngles;

	float m_flOffCenterTop;
	float m_flOffCenterBottom;
	float m_flOffCenterLeft;
	float m_flOffCenterRight;

	bool m_bOffCenter : 1;
	bool m_bRenderToSubrectOfLargerScreen : 1;
	bool m_bDoBloomAndToneMapping : 1;
	bool m_bDoDepthOfField : 1;
	bool m_bHDRTarget : 1;
	bool m_bDrawWorldNormal : 1;
	bool m_bCullFrontFaces : 1;
	bool m_bCacheFullSceneState : 1;
	bool m_bRenderFlashlightDepthTranslucents : 1;
private:
	char pad2[0x40];
};

struct csurface_t
{
	const char		*name;
	short			surfaceProps;
	unsigned short	flags;
};

struct cplane_t
{
	Vector3	normal;
	float	dist;
	BYTE	type;
	BYTE	signbits;
	BYTE	pad[2];
};

struct Ray_t
{
	VectorAligned   m_Start;
	VectorAligned   m_Delta;
	VectorAligned   m_StartOffset;
	VectorAligned   m_Extents;

	const   matrix3x4* m_pWorldAxisTransform;

	bool    m_IsRay;
	bool    m_IsSwept;

	Ray_t() : m_pWorldAxisTransform(0) { }

	void Init(Vector3& start, Vector3& end)
	{
		m_Delta = end - start;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.Set();
		m_pWorldAxisTransform = 0;
		m_IsRay = true;

		m_StartOffset.Set();
		m_Start = start;
	}

	void Init(Vector3& start, Vector3& end, Vector3& mins, Vector3& maxs)
	{
		m_Delta = end - start;

		m_pWorldAxisTransform = 0;
		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents = maxs - mins;
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.LengthSqr() < 1e-6);

		m_StartOffset = mins + maxs;
		m_StartOffset *= 0.5f;
		m_Start = start - m_StartOffset;
		m_StartOffset *= -1.0f;
	}
};



class CUserCmd
{
public:
	CUserCmd()
	{
		memset(this, 0, sizeof(*this));
	};
	virtual ~CUserCmd() {};

	CRC32_t GetChecksum() {
		CRC32_t crc;
		CRC32_Init(&crc);

		CRC32_ProcessBuffer(&crc, &command_number, sizeof(command_number));
		CRC32_ProcessBuffer(&crc, &tick_count, sizeof(tick_count));
		CRC32_ProcessBuffer(&crc, &viewangles, sizeof(viewangles));
		CRC32_ProcessBuffer(&crc, &aimdirection, sizeof(aimdirection));
		CRC32_ProcessBuffer(&crc, &forwardmove, sizeof(forwardmove));
		CRC32_ProcessBuffer(&crc, &sidemove, sizeof(sidemove));
		CRC32_ProcessBuffer(&crc, &upmove, sizeof(upmove));
		CRC32_ProcessBuffer(&crc, &buttons, sizeof(buttons));
		CRC32_ProcessBuffer(&crc, &impulse, sizeof(impulse));
		CRC32_ProcessBuffer(&crc, &weaponselect, sizeof(weaponselect));
		CRC32_ProcessBuffer(&crc, &weaponsubtype, sizeof(weaponsubtype));
		CRC32_ProcessBuffer(&crc, &random_seed, sizeof(random_seed));
		CRC32_ProcessBuffer(&crc, &mousedx, sizeof(mousedx));
		CRC32_ProcessBuffer(&crc, &mousedy, sizeof(mousedy));

		CRC32_Final(&crc);
		return crc;
	}

	int     command_number;     // 0x04 For matching server and client commands for debugging
	int     tick_count;         // 0x08 the tick the client created this command
	QAngle  viewangles;         // 0x0C Player instantaneous view angles.
	Vector3  aimdirection;       // 0x18
	float   forwardmove;        // 0x24
	float   sidemove;           // 0x28
	float   upmove;             // 0x2C
	int     buttons;            // 0x30 Attack button states
	char    impulse;            // 0x34
	int     weaponselect;       // 0x38 Current weapon id
	int     weaponsubtype;      // 0x3C
	int     random_seed;        // 0x40 For shared random functions
	short   mousedx;            // 0x44 mouse accum in x from create move
	short   mousedy;            // 0x46 mouse accum in y from create move
	bool    hasbeenpredicted;   // 0x48 Client only, tracks whether we've predicted this command at least once
	char    pad_0x4C[0x18];     // 0x4C Current sizeof( usercmd ) =  100  = 0x64
};

class CVerifiedUserCmd
{
public:
	CUserCmd m_cmd;
	CRC32_t  m_crc;
};

class C_BasePlayer;

struct GlowObjectDefinition_t
{
	GlowObjectDefinition_t() { memset(this, 0, sizeof(*this)); }

	C_BasePlayer* m_pEntity;    //0x0000
	union
	{
		Vector3 m_vGlowColor;           //0x0004
		struct
		{
			float   m_flRed;           //0x0004
			float   m_flGreen;         //0x0008
			float   m_flBlue;          //0x000C
		};
	};
	float   m_flAlpha;                 //0x0010
	uint8_t pad_0014[4];               //0x0014
	float   m_flSomeFloat;             //0x0018
	uint8_t pad_001C[4];               //0x001C
	float   m_flAnotherFloat;          //0x0020
	bool    m_bRenderWhenOccluded;     //0x0024
	bool    m_bRenderWhenUnoccluded;   //0x0025
	bool    m_bFullBloomRender;        //0x0026
	uint8_t pad_0027[5];               //0x0027
	int32_t m_nGlowStyle;              //0x002C
	int32_t m_nSplitScreenSlot;        //0x0030
	int32_t m_nNextFreeSlot;           //0x0034

	bool IsUnused() const { return m_nNextFreeSlot != -2; }
}; //Size: 0x0038 (56)

class CGlowObjectManager
{
public:
	int RegisterGlowObject(C_BasePlayer *pEntity, const Vector3 &vGlowColor, float flGlowAlpha, bool bRenderWhenOccluded, bool bRenderWhenUnoccluded, int nSplitScreenSlot)
	{
		int nIndex;
		if (m_nFirstFreeSlot == -1) {
			nIndex = -1;
		}
		else {
			nIndex = m_nFirstFreeSlot;
			m_nFirstFreeSlot = m_GlowObjectDefinitions[nIndex].m_nNextFreeSlot;
		}

		m_GlowObjectDefinitions[nIndex].m_pEntity = pEntity;
		m_GlowObjectDefinitions[nIndex].m_vGlowColor = vGlowColor;
		m_GlowObjectDefinitions[nIndex].m_flAlpha = flGlowAlpha;
		m_GlowObjectDefinitions[nIndex].m_bRenderWhenOccluded = bRenderWhenOccluded;
		m_GlowObjectDefinitions[nIndex].m_bRenderWhenUnoccluded = bRenderWhenUnoccluded;
		m_GlowObjectDefinitions[nIndex].m_nSplitScreenSlot = nSplitScreenSlot;
		m_GlowObjectDefinitions[nIndex].m_nNextFreeSlot = -2;

		return nIndex;
	}

	void UnregisterGlowObject(int nGlowObjectHandle)
	{
		m_GlowObjectDefinitions[nGlowObjectHandle].m_nNextFreeSlot = m_nFirstFreeSlot;
		m_GlowObjectDefinitions[nGlowObjectHandle].m_pEntity = NULL;
		m_nFirstFreeSlot = nGlowObjectHandle;
	}

	void SetEntity(int nGlowObjectHandle, C_BasePlayer *pEntity)
	{
		m_GlowObjectDefinitions[nGlowObjectHandle].m_pEntity = pEntity;
	}

	void SetColor(int nGlowObjectHandle, const Vector3 &vGlowColor)
	{
		m_GlowObjectDefinitions[nGlowObjectHandle].m_vGlowColor = vGlowColor;
	}

	void SetAlpha(int nGlowObjectHandle, float flAlpha)
	{
		m_GlowObjectDefinitions[nGlowObjectHandle].m_flAlpha = flAlpha;
	}

	void SetRenderFlags(int nGlowObjectHandle, bool bRenderWhenOccluded, bool bRenderWhenUnoccluded)
	{
		m_GlowObjectDefinitions[nGlowObjectHandle].m_bRenderWhenOccluded = bRenderWhenOccluded;
		m_GlowObjectDefinitions[nGlowObjectHandle].m_bRenderWhenUnoccluded = bRenderWhenUnoccluded;
	}

	GlowObjectDefinition_t* m_GlowObjectDefinitions; //0x0000

	int GetSize()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0xC);
	}

	int m_nFirstFreeSlot;                              //0x000C
};