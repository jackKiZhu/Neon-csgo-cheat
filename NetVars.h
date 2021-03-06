#define Netvars_h

#include <memory>
#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, std::unordered_map<std::string, size_t>> g_NetVars;
namespace NetVarManager // Thanks ph4ge
{
int m_iDumpedProps = 0;
int m_iDumpedTables = 0;

struct netvar_table
{
	std::string               name;
	RecvProp*                 prop;
	uint32_t                  offset;
	std::vector<RecvProp*>    child_props;
	std::vector<netvar_table> child_tables;
};

std::vector<netvar_table> database;
// INTERNAL NETVAR SYSTEM
netvar_table LoadTable( RecvTable* recvTable ) {
	auto table = netvar_table{};

	table.offset = 0;
	table.name = recvTable->m_pNetTableName;

	for( auto i = 0; i < recvTable->m_nProps; ++i ) {
		auto prop = &recvTable->m_pProps[i];

		if( !prop || isdigit( prop->m_pVarName[0] ) )
			continue;
		if( s_strcmp( "baseclass", prop->m_pVarName ) == 0 )
			continue;

		if( prop->m_RecvType == DPT_DataTable && prop->m_pDataTable ) {
			table.child_tables.emplace_back( LoadTable( prop->m_pDataTable ) );
			table.child_tables.back( ).offset = prop->m_Offset;
			table.child_tables.back( ).prop = prop;
			m_iDumpedTables++;
		} else {
			table.child_props.emplace_back( prop );
			m_iDumpedProps++;
		}
	}
	return table;
}

__forceinline uint32_t GetOffset( const netvar_table& table, const char* propName );
__forceinline uint32_t GetOffset( const char* tableName, const char*  propName ) {
	auto result = 0u;
	for( const auto& table : database ) {
		if( table.name == tableName ) {
			result = GetOffset( table, propName );
			if( result != 0 )
				return result;
		}
	}
	
	std::string kek = tableName;
	kek += " ";
	kek += propName;
	kek += " zero";

	Logger::Log( kek.c_str() );
	Logger::Log( "\n" );
	return 0;
}

uint32_t GetOffset( const netvar_table& table, const char* propName ) {
	for( const auto& prop : table.child_props ) {
		if( s_strcmp( prop->m_pVarName, propName ) == 0 ) {
			return table.offset + prop->m_Offset;
		}
	}
	for( const auto& child : table.child_tables ) {
		auto prop_offset = GetOffset( child, propName );
		if( prop_offset != 0 )
			return table.offset + prop_offset;
	}
	for( const auto& child : table.child_tables ) {
		if( s_strcmp( child.prop->m_pVarName, propName ) == 0 ) {
			return table.offset + child.offset;
		}
	}
	return 0;
}

void Dump( ) {
	m_iDumpedProps = 0;
	m_iDumpedTables = 0;

	database.clear( );

	for( auto clientclass = g_pClient->GetAllClasses( );
		clientclass != nullptr;
		clientclass = clientclass->pNextClass ) {
		if( clientclass->rtTable ) {
			m_iDumpedTables++;
			database.emplace_back( LoadTable( clientclass->rtTable ) );
		}
	}
}
};
