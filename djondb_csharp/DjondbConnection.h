#pragma once

#include "djondb_client.h";

#include "BSONObj.h"
#include "DjondbCursor.h"

typedef BSONObj I_BSONObj;

namespace Djondb {
	public ref class DjondbConnection
	{
	public:
		DjondbConnection(djondb::DjondbConnection* connection);
		virtual ~DjondbConnection();

		void beginTransaction();
		void commitTransaction();
		void rollbackTransaction();

		bool open();
		void close();
		bool isOpen() ;

		bool insert(System::String^ db, System::String^ ns, System::String^ json);
		bool insert(System::String^ db, System::String^ ns,  BSONObj^ obj);
		DjondbCursor^ find(System::String^ db, System::String^ ns);
		DjondbCursor^ find(System::String^ db, System::String^ ns,  BSONObj^ options);
		DjondbCursor^ find(System::String^ db, System::String^ ns, System::String^ filter);
		DjondbCursor^ find(System::String^ db, System::String^ ns, System::String^ filter,  BSONObj^ options);
		DjondbCursor^ find(System::String^ db, System::String^ ns, System::String^ select, System::String^ filter);
		DjondbCursor^ find(System::String^ db, System::String^ ns, System::String^ select, System::String^ filter,  BSONObj^ options);
		bool update(System::String^ db, System::String^ ns, System::String^ json);
		bool update(System::String^ db, System::String^ ns,  BSONObj^ bson);
		bool remove(System::String^ db, System::String^ ns, System::String^ id, System::String^ revision);
		DjondbCursor^ executeQuery(System::String^ query);
		bool executeUpdate(System::String^ query);
		void releaseCursor(DjondbCursor^ cursor);

		bool dropNamespace(System::String^ db, System::String^ ns);
		System::Collections::Generic::List<System::String^>^ dbs();
		System::Collections::Generic::List<System::String^>^ namespaces(System::String^ db);

		System::String^ host();

	private:
		djondb::DjondbConnection* _internal;
	};

};
