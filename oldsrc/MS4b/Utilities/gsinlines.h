#ifndef __GSINLINES_H_
#define __GSINLINES_H_

#if ((defined  (WIN32) || defined(_WIN32)) && !defined(_STDINT))
	#include <stdio.h> 
    #include <direct.h>
    #define GetCurrentDir _getcwd
	#include <string>
#else
	#include <stdio.h> 
    #include <unistd.h>
    #define GetCurrentDir getcwd
	#include <string>
 #endif
 
//#include "..\..\game\definitions.h"
#include <Game\definitions.h>

namespace GS {
namespace UtilitiesNS {
	/// DEFINING THINGS HERE IN A CPP DOESN'T APPEAR TO WORK
	_CHAR * itoa10_prebuf(int val);

	int itoa10(int val, _CHAR* buf);

	inline void AddCharToCharVector(_CHAR* in_array, int a_sizeOfArray, GSVector<_BYTE> * out_addArray)
	{
		for(int i = 0; i < a_sizeOfArray; ++i)
			out_addArray->add((_BYTE)in_array[i]);
	}

	inline void AddNumToCharVector(int a_numToAdd, GSVector<_BYTE> * out_addArray)
	{
		static _CHAR __RESERVEDCOPYSPACE[32];
		int t_size = itoa10(a_numToAdd, __RESERVEDCOPYSPACE);
		AddCharToCharVector(__RESERVEDCOPYSPACE, t_size, out_addArray);
	}

	inline std::string getDirectory()
	{
		_CHAR cCurrentPath[FILENAME_MAX];

		std::string path = "";
		GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
		path.append(cCurrentPath);
		return path;
	}
};
};

#endif