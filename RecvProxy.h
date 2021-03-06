
struct CRecvProxyData;
class RecvProp;
class RecvTable;
typedef void(__cdecl *RecvVarProxyFn) (const CRecvProxyData*, void*, void*);

struct DVariant {
	union {
		float m_Float;
		long m_Int;
		char* m_pString;
		void* m_pData;
		float m_Vector[3];
		__int64 m_Int64;
	};

	int	m_Type;
};

struct CRecvProxyData {
	const RecvProp* m_pRecvProp;
	DVariant m_Value;
	int m_iElement;
	int m_ObjectID;
};

enum SendPropType : int {
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY,
	DPT_String,
	DPT_Array,
	DPT_DataTable,
	DPT_Int64,
	DPT_NUMSendPropTypes
};

class RecvProp {
public:
	char* m_pVarName;
	SendPropType m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	const void* m_pExtraData;
	RecvProp* m_pArrayProp;
	void* m_ArrayLengthProxy;
	void* m_ProxyFn;
	void* m_DataTableProxyFn;
	RecvTable* m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char* m_pParentArrayPropName;

	RecvTable* GetDataTable() const
	{
		return m_pDataTable;
	}

	int GetOffset() const
	{
		return m_Offset;
	}

	RecvVarProxyFn GetProxyFn() const
	{
		return (RecvVarProxyFn)m_ProxyFn;
	}

	void SetProxyFn(RecvVarProxyFn fn)
	{
		m_ProxyFn = fn;
	}
};

class RecvTable {
public:
	RecvProp* m_pProps;
	int m_nProps;
	void* m_pDecoder;
	char* m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};