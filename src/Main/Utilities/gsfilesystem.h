#ifndef __GSFILESYSTEM_H_
#define __GSFILESYSTEM_H_

#include "typedefinitions.h"
// NO MORE BOOST (TOO FAT) #include <boost/filesystem.hpp>
// #include <boost/lexical_cast.hpp>

//typedef boost::filesystem::path _GSPath;
typedef std::string _GSPath;
#define _FS GS::Utilities::FileSystem

namespace GS {
namespace Utilities {
namespace FileSystem {

_GSPath getCurrentFullPath();

std::string loadFile(const char *fname);
_INT32 getFileSize(const char * a_filename);

};
};
};


#endif
