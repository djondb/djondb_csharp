#include "StdAfx.h"
#include "BSONArrayObj.h"
#include "BSONObj.h"

#include "Sharp_Util.h"

generic <class T>
Djondb::BSONArrayObj<T>::BSONArrayObj()
{
	_internal = new I_BSONArrayObj();
}

generic <class T>
Djondb::BSONArrayObj<T>::BSONArrayObj(I_BSONArrayObj* arr)
{
	_internal = arr;
}

generic <class T>
Djondb::BSONArrayObj<T>::~BSONArrayObj()
{
	delete _internal;
}

generic <class T>
__int32 Djondb::BSONArrayObj<T>::length() {
	return _internal->length();
}

generic <class T>
void Djondb::BSONArrayObj<T>::add(Djondb::BSONObj^ obj) {
	try {
		I_BSONObj* bson = obj->ptr();

		_internal->add(*bson);
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

generic <class T>
void Djondb::BSONArrayObj<T>::addAll(Djondb::BSONArrayObj<T>^ arr) {
	try {
		_internal->addAll(*arr->ptr());
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

generic <class T>
Djondb::BSONObj^ Djondb::BSONArrayObj<T>::get(__int32 index)  {
	try {
		I_BSONObj* ibson = _internal->get(index);

		Djondb::BSONObj^ res = gcnew Djondb::BSONObj(ibson);

		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

generic <class T>
System::String^ Djondb::BSONArrayObj<T>::toChar() {
	try {
		char* cres = _internal->toChar();

		System::String^ res = Sharp_Util::ConvertToString(cres);

		free(cres);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

generic <class T>
Djondb::BSONArrayObj<T>^ Djondb::BSONArrayObj<T>::select(System::String^ select)  {
	try {
		char* cselect = Sharp_Util::ConvertToChar(select);

		I_BSONArrayObj* bres = _internal->select(cselect);

		Djondb::BSONArrayObj<T>^ res = gcnew Djondb::BSONArrayObj<T>(bres);

		free(cselect);
		return res;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	}
}

