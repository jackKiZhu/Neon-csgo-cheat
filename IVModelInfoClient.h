#include "IMaterial.h"

struct virtualmodel_t
{
	/*
	void AppendSequences(int group, const studiohdr_t *pStudioHdr);
	void AppendAnimations(int group, const studiohdr_t *pStudioHdr);
	void AppendAttachments(int ground, const studiohdr_t *pStudioHdr);
	void AppendPoseParameters(int group, const studiohdr_t *pStudioHdr);
	void AppendBonemap(int group, const studiohdr_t *pStudioHdr);
	void AppendNodes(int group, const studiohdr_t *pStudioHdr);
	void AppendTransitions(int group, const studiohdr_t *pStudioHdr);
	void AppendIKLocks(int group, const studiohdr_t *pStudioHdr);
	void AppendModels(int group, const studiohdr_t *pStudioHdr);
	void UpdateAutoplaySequences(const studiohdr_t *pStudioHdr);

	virtualgroup_t *pAnimGroup(int animation) { return &m_group[m_anim[animation].group]; }; // Note: user must manage mutex for this
	virtualgroup_t *pSeqGroup(int sequence) { return &m_group[m_seq[sequence].group]; }; // Note: user must manage mutex for this
	*/

	/*CThreadFastMutex m_Lock;

	CUtlVector< virtualsequence_t > m_seq;
	CUtlVector< virtualgeneric_t > m_anim;
	CUtlVector< virtualgeneric_t > m_attachment;
	CUtlVector< virtualgeneric_t > m_pose;
	CUtlVector< virtualgroup_t > m_group;
	CUtlVector< virtualgeneric_t > m_node;
	CUtlVector< virtualgeneric_t > m_iklock;
	CUtlVector< unsigned short > m_autoplaySequences;*/
};

class IVModelInfoClient
{
public:
	model_t* GetModel(int index)
	{
		typedef model_t*(__thiscall* GetModelFn)(void*, int);
		return CallVFunc<GetModelFn>(this, 1)(this, index);
	}

	int	GetModelIndex(const char* name)
	{
		typedef int(__thiscall* GetModelIndexFn)(void*, const char*);
		return CallVFunc<GetModelIndexFn>(this, 2)(this, name);
	}

	const char* GetModelName(const model_t* model)
	{
		typedef const char* (__thiscall* GetModelNameFn)(void*, const model_t*);
		return CallVFunc<GetModelNameFn>(this, 3)(this, model);
	}

	int GetModelMaterialCount(const model_t* model)
	{
		typedef int(__thiscall* GetModelNameFn)(void*, const model_t* model);
		return CallVFunc<GetModelNameFn>(this, 16)(this, model);
	}

	void GetModelMaterials(const model_t *model, int count, IMaterial** ppMaterials)
	{
		typedef void(__thiscall* GetModelNameFn)(void*, const model_t *model, int count, IMaterial** ppMaterials);
		return CallVFunc<GetModelNameFn>(this, 19)(this, model, count, ppMaterials);
	}

	virtualmodel_t* GetVirtualModel(const studiohdr_t *pStudioHdr)
	{
		typedef virtualmodel_t* (__thiscall* GetVirtualModelFn)(void*, const studiohdr_t*);
		return CallVFunc<GetVirtualModelFn>(this, 25)(this, pStudioHdr);
	}

	studiohdr_t* GetStudioModel(const model_t* mod)
	{
		typedef studiohdr_t* (__thiscall* GetStudiomodelFn)(void*, const model_t*);
		return CallVFunc<GetStudiomodelFn>(this, 32)(this, mod);
	}
};

IVModelInfoClient* g_pModelInfo;