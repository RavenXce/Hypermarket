#pragma once
#include <string>

using namespace System;
using namespace std;
class Wrapper
{
public:
	Wrapper(void);
	~Wrapper(void);
	static string toUnmanagedString(String^);
	static char* toUnmanagedFileName(String^);
};