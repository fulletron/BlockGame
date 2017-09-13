#ifndef __COMMCLIENT_WINDOWS_H_
#define __COMMCLIENT_WINDOWS_H_

#include "../definitions_types.h"
#include "icommclient.h"

namespace GS {
namespace Utilities {
	
#ifdef USING_GLFW
class CommClient_Windows : public ICommClient
{
public:
	CommClient_Windows();
	~CommClient_Windows();

	virtual _UINT32 init(void);
	virtual _UINT32 shutdown(void);
	
selective:
	//_INT32 server_fd;
};

typedef CommClient_Windows CommClient;
#endif

};
};

#endif