#pragma once
ref class Sharp_Util
{
public:
	Sharp_Util(void);
	virtual ~Sharp_Util(void);

	static char* ConvertToChar(System::String^ str);
	static System::String^ ConvertToString(const char* c);

};

