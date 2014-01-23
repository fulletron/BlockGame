#ifndef __INLINES_H_
#define __INLINES_H_

#include "definitions.h"
#ifdef _WIN32
#include <Windows.h>
#include <string>
#endif

/// DEBUG_BOX_CHECK
inline _UINT32 DBC(_UINT32 a_x, char* a_outputString)
{
	a_outputString;
#ifdef _WIN32
#ifdef _DEBUG
	if(a_x)
	{
		std::string t_output = "";
		t_output.append(a_outputString);
		t_output.append(". Error Code: ");
		char * buffer = new char[256];
		_itoa_s(a_x, buffer, 64, 10);
		a_x;
		t_output.append(buffer);
		MessageBox(0,t_output.c_str(),"ERROR MESSAGE",MB_OK); 
	}
#endif
#endif
	return a_x;
}

inline _UINT32 DBC(_UINT32 a_x, const char* a_outputString)
{
	a_outputString;
#ifdef _WIN32
#ifdef _DEBUG
	if(a_x)
	{
		std::string t_output = "";
		t_output.append(a_outputString);
		t_output.append(". Error Code: ");
		char * buffer = new char[256];
		_itoa_s(a_x, buffer, 64, 10);
		a_x;
		t_output.append(buffer);
		MessageBoxA(0,t_output.c_str(),"ERROR MESSAGE",MB_OK); 
	}
#endif
#endif
	return a_x;
}

#endif