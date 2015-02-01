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
	I_BSONObj* bson = obj->ptr();

	_internal->add(*bson);
}

generic <class T>
void Djondb::BSONArrayObj<T>::addAll(Djondb::BSONArrayObj<T>^ arr) {
	_internal->addAll(*arr->ptr());
}

generic <class T>
Djondb::BSONObj^ Djondb::BSONArrayObj<T>::get(__int32 index)  {
	I_BSONObj* bson = _internal->get(index);

	Djondb::BSONObj^ res = gcnew Djondb::BSONObj(bson);

	return res;
}

generic <class T>
System::String^ Djondb::BSONArrayObj<T>::toChar() {
	char* cres = _internal->toChar();

	System::String^ res = Sharp_Util::ConvertToString(cres);

	free(cres);
	return res;
}

generic <class T>
Djondb::BSONArrayObj<T>^ Djondb::BSONArrayObj<T>::select(System::String^ select)  {
	char* cselect = Sharp_Util::ConvertToChar(select);

	I_BSONArrayObj* bres = _internal->select(cselect);

	Djondb::BSONArrayObj<T>^ res = gcnew Djondb::BSONArrayObj<T>(bres);

	free(cselect);
	return res;
}

