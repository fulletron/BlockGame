#include "filepath.h"
#include <Graphics\openglincludes.h>

#ifdef _WIN32
#include <Windows.h>
#include <fstream>
#include <sstream>
#endif

namespace GS {
namespace Path {
	
#ifdef USING_GLFW
#ifdef _WIN32
/*
_BOOL getAbsoluteFilepath(_CHAR ** out_buffer, _UINT32 a_bufferSize)
{
	char buffer[MAX_PATH];
	if (GetModuleFileName(NULL, buffer, a_bufferSize))
	{
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		strncpy_s((*out_buffer), a_bufferSize, std::string(buffer).substr(0, pos).c_str(), a_bufferSize);
		return true;
	}
	return false;
}

_UINT32 getMaxPathSize()
{
	return MAX_PATH;
}
*/

const char * FilePath::getAbsoluteFilePath()
{
	return FilePath::getAbsoluteFilePath_str().c_str();
}

std::string FilePath::getAbsoluteFilePath_str()
{
	if (strcmp(m_absoluteFilePath.c_str(), "0") == 0)
	{
		char buffer[MAX_PATH];
		m_absoluteFilePath = new char[];
		if (GetModuleFileName(NULL, buffer, MAX_PATH))
		{
			std::string::size_type pos = std::string(buffer).find_last_of("\\/");
			m_absoluteFilePath = std::string(buffer).substr(0, pos).c_str();
			//			strcpy_s(m_absoluteFilePath, (_UINT32)MAX_PATH, std::string(buffer).substr(0, pos).c_str());
		}
	}
	return m_absoluteFilePath;
}

std::string FilePath::loadFile(const char *fname)
{
	std::ifstream file(fname);
	if (!file.is_open())
	{
		return "";
	}

	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();

	return fileData.str();
}

_INT32 FilePath::getFileSize(const char * a_filename)
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

#endif
#endif

};
};