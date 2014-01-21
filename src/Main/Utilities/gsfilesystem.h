#ifndef __GSFILESYSTEM_H_
#define __GSFILESYSTEM_H_

#include <boost/filesystem.hpp>

typedef boost::filesystem::path _GSPath;

namespace GS {
namespace Utilities {
namespace FileSystem {

_GSPath getCurrentFullPath();

};
};
};


#endif
