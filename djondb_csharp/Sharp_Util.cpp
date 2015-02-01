#include "StdAfx.h"
#include "Sharp_Util.h"
#include <vcclr.h>
#include <stdlib.h>

Sharp_Util::Sharp_Util(void)
{
}


Sharp_Util::~Sharp_Util(void)
{
}

char* Sharp_Util::ConvertToChar(System::String^ str) {
	pin_ptr<const __wchar_t> cstr = PtrToStringChars(str);
	size_t sizeInBytes = (str->Length + 1) * 2;
	char* ch = (char*)malloc(sizeInBytes);
	size_t convertedChars = 0;
	wcstombs_s(&convertedChars, ch, sizeInBytes, cstr, sizeInBytes);

	return ch;
}

System::String^ Sharp_Util::ConvertToString(const char* c) {
	System::String^ str = gcnew System::String(c);

	return str;
}