#pragma once

class CMaterialReference
{
public:
	IMaterial* m_pMaterial;

	void Shutdown()
	{
		if (m_pMaterial)
		{
			m_pMaterial->DecrementReferenceCount();
			m_pMaterial = NULL;
		}
	}
	void Init(IMaterial* pMaterial)
	{
		if (m_pMaterial != pMaterial)
		{
			Shutdown();
			m_pMaterial = pMaterial;
			if (m_pMaterial)
			{
				m_pMaterial->IncrementReferenceCount();
			}
		}
	}
	operator IMaterial*() { return m_pMaterial; }
	operator IMaterial*() const { return m_pMaterial; }
	operator IMaterial const*() const { return m_pMaterial; }
	IMaterial* operator->() { return m_pMaterial; }
};