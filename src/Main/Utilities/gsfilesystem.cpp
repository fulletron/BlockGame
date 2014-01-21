#include "gsfilesystem.h"

namespace GS {
namespace Utilities {
namespace FileSystem {

_GSPath getCurrentFullPath()
{
	_GSPath full_path( boost::filesystem::current_path() );
	return full_path;
}

};
};
};

