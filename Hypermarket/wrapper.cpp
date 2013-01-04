#include "stdafx.h"
#include "wrapper.h"


Wrapper::Wrapper(void)
{
}


Wrapper::~Wrapper(void)
{
}

using namespace System::Runtime::InteropServices;

string Wrapper::toUnmanagedString(String^ input){
	char* unmanagedoutput = (char*) Marshal::StringToHGlobalAnsi(input).ToPointer();
	string string_output(unmanagedoutput);
	Marshal::FreeHGlobal(IntPtr(unmanagedoutput));
	unmanagedoutput = NULL;
	return string(string_output);
}

char* Wrapper::toUnmanagedFileName(String^ input){
	int i = 0, at = 0;				
	while(at = input->IndexOf('\\',i)){
		if ( at == -1 )
			break;
		i = at+2;
		input = input->Insert(at,gcnew String('\\',1));
	}
	char* unmanagedfilename = (char*) Marshal::StringToHGlobalAnsi(input).ToPointer();
	char* outputfilename = new char[strlen(unmanagedfilename)+1];
	strcpy_s(outputfilename, strlen(unmanagedfilename)+1, unmanagedfilename);
	Marshal::FreeHGlobal(IntPtr(unmanagedfilename));
	unmanagedfilename = NULL;
	return outputfilename;
}