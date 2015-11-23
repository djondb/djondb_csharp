#pragma once

#include "bsonparser.h"
#include "BSONObj.h"
#include "BSONArrayObj.h"

typedef BSONParser I_BSONParser;

namespace Djondb {

	public ref class BSONParser
	{
	public:
		static Djondb::BSONObj^ parse(System::String^ sbson);
		static Djondb::BSONArrayObj<Djondb::BSONObj^>^ parseArray(System::String^ sbson);

	};

};