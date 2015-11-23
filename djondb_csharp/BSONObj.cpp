#include "StdAfx.h"
#include "BSONObj.h"

#include "Sharp_Util.h"

using namespace Djondb;

/*
Djondb::BSONObj::BSONObj(void)
{
_internal = new I_BSONObj();
}

Djondb::BSONObj::BSONObj(I_BSONObj* obj) {
_internal = obj;
}
*/

Djondb::BSONObj::~BSONObj(void)
{
	if (_internal) delete _internal;
}

void Djondb::BSONObj::add(System::String^ sName, __int32 i) {
	try {
		char* name = Sharp_Util::ConvertToChar(sName);
		_internal->add(name, i);

		free(name);
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

void Djondb::BSONObj::add(System::String^ sName, double d) {
	try {
		char* name = Sharp_Util::ConvertToChar(sName);
		_internal->add(name, d);

		free(name);
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

void Djondb::BSONObj::add(System::String^ sName, __int64 l) {
	try {
		char* name = Sharp_Util::ConvertToChar(sName);
		_internal->add(name, l);

		free(name);
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

void Djondb::BSONObj::add(System::String^ sName, System::String^ str) {
	try {
		char* name = Sharp_Util::ConvertToChar(sName);
		char* cstr = Sharp_Util::ConvertToChar(str);

		_internal->add(name, cstr);
		free(cstr);
		free(name);
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

void Djondb::BSONObj::add(System::String^ sName, BSONObj^ obj) {
	try {
		System::Console::WriteLine("test");
		char* name = Sharp_Util::ConvertToChar(sName);

		_internal->add(name, *obj->ptr());

		free(name);
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}


void Djondb::BSONObj::add(System::String^ sName, BSONArrayObj<BSONObj^>^ arr) {
	try {
		char* name = Sharp_Util::ConvertToChar(sName);
		_internal->add(name, *arr->ptr());

		free(name);
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

void Djondb::BSONObj::add(System::String^ sName, bool b) {
	try {
		System::Console::WriteLine("add bool");
		char* name = Sharp_Util::ConvertToChar(sName);
		_internal->add(name, b);

		free(name);
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

bool Djondb::BSONObj::has(System::String^ sName) {
	try {
		char* name = Sharp_Util::ConvertToChar(sName);
		bool res = _internal->has(name);

		free(name);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

bool Djondb::BSONObj::getBoolean(System::String^ sName){
	try {
		char* name = Sharp_Util::ConvertToChar(sName);
		bool res = _internal->getBoolean(name);

		free(name);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

__int32 Djondb::BSONObj::getInt(System::String^ sName){
	try {
		char* name = Sharp_Util::ConvertToChar(sName);
		__int32 res = _internal->getInt(name);

		free(name);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

double Djondb::BSONObj::getDouble(System::String^ sName){
	try {
		char* name = Sharp_Util::ConvertToChar(sName);
		double res = _internal->getDouble(name);

		free(name);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

__int64 Djondb::BSONObj::getLong(System::String^ sName){
	try {
		char* name = Sharp_Util::ConvertToChar(sName);
		__int64 res = _internal->getLong(name);

		free(name);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

const System::String^ Djondb::BSONObj::getString(System::String^ sName){
	try {
		char* name = Sharp_Util::ConvertToChar(sName);
		std::string cres = _internal->getString(name);
		System::String^ res = Sharp_Util::ConvertToString(cres.c_str());

		free(name);

		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

Djondb::BSONArrayObj<Djondb::BSONObj^>^ Djondb::BSONObj::getBSONArray(System::String^ name) {
	try {
		char* cname = Sharp_Util::ConvertToChar(name);
		I_BSONArrayObj* arr = _internal->getBSONArray(cname);

		BSONArrayObj<Djondb::BSONObj^>^ res = gcnew BSONArrayObj<Djondb::BSONObj^>(arr);

		free(cname);

		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

Djondb::BSONObj^ Djondb::BSONObj::getBSON(System::String^ sName) {
	try {
		char* name = Sharp_Util::ConvertToChar(sName);
		I_BSONObj* ibson = _internal->getBSON(name);

		free(name);

		Djondb::BSONObj^ res = gcnew Djondb::BSONObj(ibson);

		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

Djondb::BSONObj^ Djondb::BSONObj::select(System::String^ sel) {
	try {
		char* cSel = Sharp_Util::ConvertToChar(sel);

		I_BSONObj* iBson = _internal->select(cSel);

		Djondb::BSONObj^ res = gcnew Djondb::BSONObj(iBson);

		free(cSel);

		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

Djondb::BSONObj^ Djondb::BSONObj::select(System::String^ sel, bool includeKey) {
	try {
		char* cSel = Sharp_Util::ConvertToChar(sel);

		I_BSONObj* iBson = _internal->select(cSel, includeKey);

		Djondb::BSONObj^ res = gcnew Djondb::BSONObj(iBson);

		free(cSel);

		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

System::String^ Djondb::BSONObj::toChar() {
	try {
		char* data = _internal->toChar();
		System::String^ str = Sharp_Util::ConvertToString(const_cast<const char*>(data));

		free(data);

		return str;

	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}
__int32 Djondb::BSONObj::length() {
	return _internal->length();
}

bool Djondb::BSONObj::operator ==(Djondb::BSONObj^ obj) {
	I_BSONObj* iObj = obj->_internal;
	I_BSONObj* iThis = this->_internal;

	return *iObj == *iThis;
}

bool Djondb::BSONObj::operator !=(Djondb::BSONObj^ obj) {
	I_BSONObj* iObj = obj->_internal;
	I_BSONObj* iThis = this->_internal;

	return *iObj != *iThis;
}

I_BSONObj* Djondb::BSONObj::ptr() {
	return _internal;
}

List<System::String^>^ Djondb::BSONObj::properties() {
	List<System::String^>^ result = gcnew List<System::String^>();

	I_BSONObj* iObj = this->_internal;

	for (I_BSONObj::const_iterator i = iObj->begin(); i != iObj->end(); i++) {
		std::string propName = i->first;

		System::String^ str = Sharp_Util::ConvertToString(propName.c_str());
		result->Add(str);
	}

	return result;
}

const System::Object^ Djondb::BSONObj::get(System::String^ propName) {
	const System::Object^ result = nullptr();

	I_BSONObj* iObj = this->_internal;

	char* cSel = Sharp_Util::ConvertToChar(propName);

	BSONContent* content = iObj->get(cSel);
	switch (content->type()) {
	case INT_TYPE:
		result = getInt(propName);
		break;
	case DOUBLE_TYPE:
		result = getDouble(propName);
		break;
	case LONG_TYPE:
		result = getLong(propName);
		break;
	case PTRCHAR_TYPE:
	case STRING_TYPE:
		result = getString(propName);
		break;
	case BSON_TYPE:
		result = getBSON(propName);
		break;

	case BSONARRAY_TYPE:
		result = getBSONArray(propName);
		break;

	case LONG64_TYPE: 
		result = getLong(propName);
		break;
	case BOOL_TYPE:
		result = getBoolean(propName);
		break;
	}

	free(cSel);

	return result;
}
