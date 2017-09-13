#ifndef __FILEPATH_H_
#define __FILEPATH_H_

#include "../definitions_types.h"


#ifdef _WIN32
#include <string>
#endif

namespace GS {
namespace Path {
#ifdef _WIN32
class FilePath
{
private:
	std::string m_absoluteFilePath;

public:
	const char * getAbsoluteFilePath();
	std::string getAbsoluteFilePath_str();

	_INT32 getFileSize(const char *);
	std::string loadFile(const char *);
// singleton impl
public:
	static FilePath& getInstance()
	{
		static FilePath    instance;
		return instance;
	}
private:
	FilePath() 
	{
		m_absoluteFilePath = "0";
	}

	FilePath(FilePath const&);              // Don't Implement.
	void operator=(FilePath const&); // Don't implement
};

#define FILEPATH GS::Path::FilePath::getInstance()
#endif
};
};

#endif