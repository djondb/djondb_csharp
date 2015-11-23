#include "StdAfx.h"
#include "BsonParser.h"
#include "Sharp_Util.h"

Djondb::BSONObj^ Djondb::BSONParser::parse(System::String^ sbson) {
	char* cbson = Sharp_Util::ConvertToChar(sbson);

	try {
		I_BSONObj* cbobj = I_BSONParser::parse(cbson);

		Djondb::BSONObj^ result = gcnew Djondb::BSONObj(cbobj);

		return result;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	} finally {
		free(cbson);
	}
}

Djondb::BSONArrayObj<Djondb::BSONObj^>^ Djondb::BSONParser::parseArray(System::String^ sbson) {
	char* cbson = Sharp_Util::ConvertToChar(sbson);

	try {
		I_BSONArrayObj* cbobj = I_BSONParser::parseArray(std::string(cbson));

		Djondb::BSONArrayObj<Djondb::BSONObj^>^ result = gcnew Djondb::BSONArrayObj<Djondb::BSONObj^>(cbobj);

		free(cbson);

		return result;
	} catch (std::exception& e) {
		System::String^ message = Sharp_Util::ConvertToString(e.what());
		throw gcnew System::Exception(message);
		//		throw gcnew Djondb::DjondbException(e.what());
	} finally {
		free(cbson);
	}
}

