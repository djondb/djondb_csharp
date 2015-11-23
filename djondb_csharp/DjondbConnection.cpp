#include "StdAfx.h"
#include "DjondbConnection.h"
#include "Sharp_Util.h"
//#include "DjondbException.h"

using namespace Djondb;

Djondb::DjondbConnection::DjondbConnection(djondb::DjondbConnection* connection)
{
	_internal = connection;
}

Djondb::DjondbConnection::~DjondbConnection() 
{
	delete _internal;
}

bool Djondb::DjondbConnection::open() {
	return _internal->open();
}

void Djondb::DjondbConnection::close() {
	return _internal->close();
}

void Djondb::DjondbConnection::beginTransaction() {
	_internal->beginTransaction();
}

void Djondb::DjondbConnection::commitTransaction() {
	_internal->commitTransaction();
}

void Djondb::DjondbConnection::rollbackTransaction() {
	_internal->rollbackTransaction();
}


bool Djondb::DjondbConnection::isOpen() {
	return _internal->isOpen();
}

bool Djondb::DjondbConnection::insert(System::String^ db, System::String^ ns, System::String^ json) {
	try {
		char* cdb = Sharp_Util::ConvertToChar(db);
		char* cns = Sharp_Util::ConvertToChar(ns);
		char* cjson = Sharp_Util::ConvertToChar(json);

		bool res = _internal->insert(cdb, cns, cjson);

		free(cdb);
		free(cns);
		free(cjson);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

bool Djondb::DjondbConnection::insert(System::String^ db, System::String^ ns,  BSONObj^ obj) {
	try {
		char* cdb = Sharp_Util::ConvertToChar(db);
		char* cns = Sharp_Util::ConvertToChar(ns);
		I_BSONObj* bson = obj->ptr();

		bool res = _internal->insert(cdb, cns, *bson);

		free(cdb);
		free(cns);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

DjondbCursor^ Djondb::DjondbConnection::find(System::String^ db, System::String^ ns) {
	try {
		char* cdb = Sharp_Util::ConvertToChar(db);
		char* cns = Sharp_Util::ConvertToChar(ns);

		djondb::DjondbCursor* cur = _internal->find(cdb, cns);

		Djondb::DjondbCursor^ res = gcnew Djondb::DjondbCursor(cur);

		free(cdb);
		free(cns);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

DjondbCursor^ Djondb::DjondbConnection::find(System::String^ db, System::String^ ns,  BSONObj^ options) {
	try {
		char* cdb = Sharp_Util::ConvertToChar(db);
		char* cns = Sharp_Util::ConvertToChar(ns);
		I_BSONObj* boptions = options->ptr();

		djondb::DjondbCursor* cur = _internal->find(cdb, cns, *boptions);

		Djondb::DjondbCursor^ res = gcnew Djondb::DjondbCursor(cur);

		free(cdb);
		free(cns);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

DjondbCursor^ Djondb::DjondbConnection::find(System::String^ db, System::String^ ns, System::String^ filter) {
	try {
		char* cdb = Sharp_Util::ConvertToChar(db);
		char* cns = Sharp_Util::ConvertToChar(ns);
		char* cfilter = Sharp_Util::ConvertToChar(filter);

		djondb::DjondbCursor* cur = _internal->find(cdb, cns, cfilter);

		Djondb::DjondbCursor^ res = gcnew Djondb::DjondbCursor(cur);

		free(cdb);
		free(cns);
		free(cfilter);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

DjondbCursor^ Djondb::DjondbConnection::find(System::String^ db, System::String^ ns, System::String^ filter,  BSONObj^ options) {
	try {
		char* cdb = Sharp_Util::ConvertToChar(db);
		char* cns = Sharp_Util::ConvertToChar(ns);
		char* cfilter = Sharp_Util::ConvertToChar(filter);
		I_BSONObj* boptions = options->ptr();

		djondb::DjondbCursor* cur = _internal->find(cdb, cns, cfilter, *boptions);

		Djondb::DjondbCursor^ res = gcnew Djondb::DjondbCursor(cur);

		free(cdb);
		free(cns);
		free(cfilter);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

DjondbCursor^ Djondb::DjondbConnection::find(System::String^ db, System::String^ ns, System::String^ select, System::String^ filter) {
	try {
		char* cdb = Sharp_Util::ConvertToChar(db);
		char* cns = Sharp_Util::ConvertToChar(ns);
		char* cselect = Sharp_Util::ConvertToChar(select);
		char* cfilter = Sharp_Util::ConvertToChar(filter);

		djondb::DjondbCursor* cur = _internal->find(cdb, cns, cselect, cfilter);

		Djondb::DjondbCursor^ res = gcnew Djondb::DjondbCursor(cur);

		free(cdb);
		free(cns);
		free(cfilter);
		free(cselect);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

DjondbCursor^ Djondb::DjondbConnection::find(System::String^ db, System::String^ ns, System::String^ select, System::String^ filter,  BSONObj^ options) {
	try {
		char* cdb = Sharp_Util::ConvertToChar(db);
		char* cns = Sharp_Util::ConvertToChar(ns);
		char* cselect = Sharp_Util::ConvertToChar(select);
		char* cfilter = Sharp_Util::ConvertToChar(filter);
		I_BSONObj* boptions = options->ptr();

		djondb::DjondbCursor* cur = _internal->find(cdb, cns, cselect, cfilter, *boptions);

		Djondb::DjondbCursor^ res = gcnew Djondb::DjondbCursor(cur);

		free(cdb);
		free(cns);
		free(cfilter);
		free(cselect);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

bool Djondb::DjondbConnection::update(System::String^ db, System::String^ ns, System::String^ json) {
	try {
		char* cdb = Sharp_Util::ConvertToChar(db);
		char* cns = Sharp_Util::ConvertToChar(ns);
		char* cjson = Sharp_Util::ConvertToChar(json);

		bool res = _internal->update(cdb, cns, cjson);

		free(cdb);
		free(cns);
		free(cjson);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

bool Djondb::DjondbConnection::update(System::String^ db, System::String^ ns,  BSONObj^ bson) {
	try {
		char* cdb = Sharp_Util::ConvertToChar(db);
		char* cns = Sharp_Util::ConvertToChar(ns);
		I_BSONObj* bbson = bson->ptr();

		bool res = _internal->update(cdb, cns, *bbson);

		free(cdb);
		free(cns);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

bool Djondb::DjondbConnection::remove(System::String^ db, System::String^ ns, System::String^ id, System::String^ revision) {
	try {
		char* cdb = Sharp_Util::ConvertToChar(db);
		char* cns = Sharp_Util::ConvertToChar(ns);
		char* cid = Sharp_Util::ConvertToChar(id);
		char* crevision = Sharp_Util::ConvertToChar(revision);

		bool res = _internal->remove(cdb, cns, cid, crevision);

		free(cdb);
		free(cns);
		free(cid);
		free(crevision);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

DjondbCursor^ Djondb::DjondbConnection::executeQuery(System::String^ query) {
	try {
		char* cquery = Sharp_Util::ConvertToChar(query);

		djondb::DjondbCursor* cur = _internal->executeQuery(cquery);

		Djondb::DjondbCursor^ res = gcnew Djondb::DjondbCursor(cur);

		free(cquery);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

bool Djondb::DjondbConnection::executeUpdate(System::String^ query) {
	try {
		char* cquery = Sharp_Util::ConvertToChar(query);

		bool res = _internal->executeUpdate(cquery);

		free(cquery);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

void Djondb::DjondbConnection::releaseCursor(DjondbCursor^ cursor) {
	try {
		_internal->releaseCursor(cursor->ptr());
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}


bool Djondb::DjondbConnection::dropNamespace(System::String^ db, System::String^ ns) {
	try {
		char* cdb = Sharp_Util::ConvertToChar(db);
		char* cns = Sharp_Util::ConvertToChar(ns);

		bool res = _internal->dropNamespace(cdb, cns);

		free(cdb);
		free(cns);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

System::Collections::Generic::List<System::String^>^ Djondb::DjondbConnection::dbs() {
	try {
		System::Collections::Generic::List<System::String^>^ res = gcnew System::Collections::Generic::List<System::String^>();

		std::vector<std::string>* vdbs = _internal->dbs();
		for (std::vector<std::string>::iterator it = vdbs->begin(); it != vdbs->end(); it++) {
			std::string db = *it;

			res->Add(Sharp_Util::ConvertToString(db.c_str()));
		}

		delete (vdbs);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

System::Collections::Generic::List<System::String^>^ Djondb::DjondbConnection::namespaces(System::String^ db) {
	try {
		char* cdb = Sharp_Util::ConvertToChar(db);
		System::Collections::Generic::List<System::String^>^ res = gcnew System::Collections::Generic::List<System::String^>();

		std::vector<std::string>* vns = _internal->namespaces(cdb);
		for (std::vector<std::string>::iterator it = vns->begin(); it != vns->end(); it++) {
			std::string ns = *it;

			res->Add(Sharp_Util::ConvertToString(ns.c_str()));
		}

		delete (vns);
		free(cdb);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}


System::String^ Djondb::DjondbConnection::host() {
	try {
		char* chost = _internal->host();

		System::String^ res = Sharp_Util::ConvertToString(chost);
		free(chost);

		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}


