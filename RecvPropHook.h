#pragma once

class RecvPropHook {
private:
	RecvProp* target_property;
	RecvVarProxyFn original_proxy_fn;
public:
	~RecvPropHook() {
		target_property->m_ProxyFn = this->original_proxy_fn;
	}

	const RecvVarProxyFn GetOriginalFunction() {
		return this->original_proxy_fn;
	}

	void SetProxyFunction(const char* DTable, const char* NetVar, RecvVarProxyFn user_proxy_fn) {
		for (ClientClass* pClass = g_pClient->GetAllClasses(); pClass; pClass = pClass->pNextClass) {
			if (!_strcmp(pClass->rtTable->m_pNetTableName, DTable)) {
				RecvTable* pClassTable = pClass->rtTable;

				for (int nIndex = 0; nIndex < pClassTable->m_nProps; nIndex++) {
					RecvProp* pProp = &pClassTable->m_pProps[nIndex];
					if (!pProp)
						continue;

					if (!strcmp(pProp->m_pVarName, NetVar))
					{
						original_proxy_fn = (RecvVarProxyFn)pProp->m_ProxyFn;
						pProp->m_ProxyFn = user_proxy_fn;

						DEVMSG("%s in %s found and hooked successfully!", NetVar, DTable);
						return;
					}
				}
			}
		}

		DEVMSG("ERROR: %s IN %s WASN'T FOUND!", NetVar, DTable);
	}
};