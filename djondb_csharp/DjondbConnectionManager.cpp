#include "StdAfx.h"
#include "DjondbConnectionManager.h"
#include "DjondbConnection.h";

#include "djondb_client.h";
#include "Sharp_Util.h";

Djondb::DjondbConnection^ Djondb::DjondbConnectionManager::getConnection(System::String^ server) {
	char* serverName = Sharp_Util::ConvertToChar(server);

	djondb::DjondbConnection* con = djondb::DjondbConnectionManager::getConnection(serverName);

	Djondb::DjondbConnection^ connection = gcnew Djondb::DjondbConnection(con);

	free(serverName);
	return connection;
}
