#include "gsfilesystem.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// THIS IS FOR FILESYSTEM.
#ifdef WIN32
#include <windows.h>
#else
// OTHER DEFS
#endif

namespace GS {
namespace Utilities {
namespace FileSystem {

_GSPath getCurrentFullPath()
{
#ifdef WIN32
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
#else
	return "KYLE :: TODO :: IMPLEMENT";
#endif
}

std::string loadFile(const char *fname)
{
        std::ifstream file(fname);
        if(!file.is_open())
        {
			return "";
        }
 
        std::stringstream fileData;
        fileData << file.rdbuf();
        file.close();
 
        return fileData.str();
}

_INT32 getFileSize(const char * a_filename)
{
	std::fstream inFile;
	_UINT32 size = 0;

	inFile.open(a_filename);

	if (!inFile)
		return -1;

	char x;

	while (inFile >> x) {
	  size++;
	}

	return size;
}

};
};
};

