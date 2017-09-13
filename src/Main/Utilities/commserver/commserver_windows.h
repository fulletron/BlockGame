#ifndef __COMMSERVER_WINDOWS_H_
#define __COMMSERVER_WINDOWS_H_

#include "../definitions_types.h"
#include "icommserver.h"

namespace GS {
namespace Utilities {
	
#ifdef USING_GLFW
class CommServer_Windows : public ICommServer
{
public:
	CommServer_Windows();
	~CommServer_Windows();

	virtual _UINT32 init(void);
	virtual _UINT32 shutdown(void);
	
selective:
	//_INT32 server_fd;
};

typedef CommServer_Windows CommServer;
#endif

};
};

#endif