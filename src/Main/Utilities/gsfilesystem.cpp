#include "gsfilesystem.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace GS {
namespace Utilities {
namespace FileSystem {

_GSPath getCurrentFullPath()
{
	_GSPath full_path( boost::filesystem::current_path() );
	return full_path;
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

