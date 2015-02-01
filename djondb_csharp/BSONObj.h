#pragma once

#include "djondb_client.h"

typedef BSONObj I_BSONObj;

#include "BSONArrayObj.h"

namespace Djondb {

	public ref class BSONObj
	{
	public:
		BSONObj()
		  : _internal(new I_BSONObj())
		{
		}

		BSONObj(I_BSONObj* obj)
		  : _internal(obj)
		{
		}

		virtual ~BSONObj(void);

		void add(System::String^ name, __int32 i);

		void add(System::String^ name, double d);
		void add(System::String^ name, __int64 l);
		void add(System::String^ name, System::String^ str);
		void add(System::String^ name, BSONObj^ obj);
		void add(System::String^ name, Djondb::BSONArrayObj<BSONObj^>^ arr);
		void add(System::String^ name, bool b);

		virtual bool has(System::String^ sName);

		virtual bool getBoolean(System::String^ sName);
		virtual __int32 getInt(System::String^ sName);
		virtual double getDouble(System::String^ sName);
		virtual __int64 getLong(System::String^ sName);
		const System::String^ getString(System::String^ sName);
		virtual BSONObj^ getBSON(System::String^ sName);
		virtual BSONArrayObj<BSONObj^>^ getBSONArray(System::String^ sName);

		virtual BSONObj^ select(System::String^ sel);
		virtual BSONObj^ select(System::String^ sel, bool includeKey);

		virtual System::String^ toChar();

		virtual __int32 length();

		virtual bool operator ==(BSONObj^ obj);
		virtual bool operator !=(BSONObj^ obj);

		I_BSONObj* ptr();
	private:
		I_BSONObj* _internal;
	};

};