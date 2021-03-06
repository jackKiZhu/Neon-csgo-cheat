typedef void*	(*CreateClientClassFn)(int entnum, int serialNum);
class ClientClass
{
public:
	CreateClientClassFn m_pCreateFn;
	void *m_pCreateEventFn;
	char* szName;
	RecvTable* rtTable;
	ClientClass* pNextClass;
	int iClassID;
};
