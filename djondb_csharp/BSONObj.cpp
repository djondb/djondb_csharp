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
	char* name = Sharp_Util::ConvertToChar(sName);
	_internal->add(name, i);

	free(name);
}

void Djondb::BSONObj::add(System::String^ sName, double d) {
	char* name = Sharp_Util::ConvertToChar(sName);
	_internal->add(name, d);

	free(name);
}

void Djondb::BSONObj::add(System::String^ sName, __int64 l) {
	char* name = Sharp_Util::ConvertToChar(sName);
	_internal->add(name, l);

	free(name);
}

void Djondb::BSONObj::add(System::String^ sName, System::String^ str) {
	char* name = Sharp_Util::ConvertToChar(sName);
	char* cstr = Sharp_Util::ConvertToChar(str);

	_internal->add(name, cstr);
	free(cstr);
	free(name);
}

void Djondb::BSONObj::add(System::String^ sName, BSONObj^ obj) {
	char* name = Sharp_Util::ConvertToChar(sName);
	I_BSONObj* iObj = obj->_internal;

	_internal->add(name, iObj);

	free(name);
}


void Djondb::BSONObj::add(System::String^ sName, BSONArrayObj<BSONObj^>^ arr) {
	char* name = Sharp_Util::ConvertToChar(sName);
	_internal->add(name, arr->ptr());

	free(name);
}

void Djondb::BSONObj::add(System::String^ sName, bool b) {
	char* name = Sharp_Util::ConvertToChar(sName);
	_internal->add(name, b);

	free(name);
}

bool Djondb::BSONObj::has(System::String^ sName) {
	char* name = Sharp_Util::ConvertToChar(sName);
	bool res = _internal->has(name);

	free(name);
	return res;
}

bool Djondb::BSONObj::getBoolean(System::String^ sName){
	char* name = Sharp_Util::ConvertToChar(sName);
	bool res = _internal->getBoolean(name);

	free(name);
	return res;
}

__int32 Djondb::BSONObj::getInt(System::String^ sName){
	char* name = Sharp_Util::ConvertToChar(sName);
	__int32 res = _internal->getInt(name);

	free(name);
	return res;
}

double Djondb::BSONObj::getDouble(System::String^ sName){
	char* name = Sharp_Util::ConvertToChar(sName);
	double res = _internal->getDouble(name);

	free(name);
	return res;
}

__int64 Djondb::BSONObj::getLong(System::String^ sName){
	char* name = Sharp_Util::ConvertToChar(sName);
	__int64 res = _internal->getLong(name);

	free(name);
	return res;
}

const System::String^ Djondb::BSONObj::getString(System::String^ sName){
	char* name = Sharp_Util::ConvertToChar(sName);
	std::string cres = _internal->getString(name);
	System::String^ res = Sharp_Util::ConvertToString(cres.c_str());

	free(name);

	return res;
}

Djondb::BSONArrayObj<Djondb::BSONObj^>^ Djondb::BSONObj::getBSONArray(System::String^ name) {
	char* cname = Sharp_Util::ConvertToChar(name);
	I_BSONArrayObj* arr = _internal->getBSONArray(cname);

	BSONArrayObj<Djondb::BSONObj^>^ res = gcnew BSONArrayObj<Djondb::BSONObj^>(arr);

	free(cname);

	return res;
}

Djondb::BSONObj^ Djondb::BSONObj::getBSON(System::String^ sName) {
	char* name = Sharp_Util::ConvertToChar(sName);
	I_BSONObj* ibson = _internal->getBSON(name);

	free(name);

	Djondb::BSONObj^ res = gcnew Djondb::BSONObj(ibson);

	return res;
}

Djondb::BSONObj^ Djondb::BSONObj::select(System::String^ sel) {
	char* cSel = Sharp_Util::ConvertToChar(sel);

	I_BSONObj* iBson = _internal->select(cSel);

	Djondb::BSONObj^ res = gcnew Djondb::BSONObj(iBson);

	free(cSel);

	return res;
}

Djondb::BSONObj^ Djondb::BSONObj::select(System::String^ sel, bool includeKey) {
	char* cSel = Sharp_Util::ConvertToChar(sel);

	I_BSONObj* iBson = _internal->select(cSel, includeKey);

	Djondb::BSONObj^ res = gcnew Djondb::BSONObj(iBson);

	free(cSel);

	return res;
}

System::String^ Djondb::BSONObj::toChar() {
	char* data = _internal->toChar();

	System::String^ str = Sharp_Util::ConvertToString(const_cast<const char*>(data));

	free(data);

	return str;

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
