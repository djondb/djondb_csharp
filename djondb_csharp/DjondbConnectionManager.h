#pragma once

#include "DjondbConnection.h";

namespace Djondb {

	public ref class DjondbConnectionManager
	{
	public:
		static DjondbConnection^ getConnection(System::String^ server);
	};

};