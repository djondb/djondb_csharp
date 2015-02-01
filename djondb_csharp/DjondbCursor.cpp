#include "StdAfx.h"
#include "DjondbCursor.h"

Djondb::DjondbCursor::DjondbCursor(djondb::DjondbCursor* cursor)
{
	_internal = cursor;
}

Djondb::DjondbCursor::~DjondbCursor(void)
{
	delete(_internal);
}

bool Djondb::DjondbCursor::next() {
	return _internal->next();
}

bool Djondb::DjondbCursor::previous() {
	return _internal->previous();
}

Djondb::BSONObj^ Djondb::DjondbCursor::current() {
	I_BSONObj* iBson = _internal->current();

	Djondb::BSONObj^ res = gcnew Djondb::BSONObj(iBson);

	return res;
}

__int32 Djondb::DjondbCursor::length() {
	return _internal->length();
}

void Djondb::DjondbCursor::releaseCursor() {
	_internal->releaseCursor();
}

void Djondb::DjondbCursor::seek(__int32 position) {
	_internal->seek(position);
}

djondb::DjondbCursor* Djondb::DjondbCursor::ptr() {
	return _internal;
}