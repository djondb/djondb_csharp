#include "StdAfx.h"
#include "DjondbCursor.h"

Djondb::DjondbCursor::DjondbCursor(djondb::DjondbCursor* cursor)
{
	_internal = cursor;
	_current = nullptr;
}

Djondb::DjondbCursor::~DjondbCursor(void)
{
	delete(_internal);
}

bool Djondb::DjondbCursor::next() {
	bool res = _internal->next();

	if (res) {
		I_BSONObj* iBson = _internal->current();

		_current = gcnew Djondb::BSONObj(iBson);
	}
	return res;
}

bool Djondb::DjondbCursor::previous() {
	bool res = _internal->previous();

	if (res) {
		I_BSONObj* iBson = _internal->current();

		_current = gcnew Djondb::BSONObj(iBson);
	}
	return res;
}

Djondb::BSONObj^ Djondb::DjondbCursor::current() {
	return _current;
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