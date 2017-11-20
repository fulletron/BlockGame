#ifndef __USESWINSOCK_H__
#define __USESWINSOCK_H__

#include "../definitions_types.h"

// KYLE :: remove redefines
#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif

namespace GS {
namespace Server {

class UsesWinsock
{
public:

	UsesWinsock();

	~UsesWinsock();

selective:
	WSADATA m_data;

	// No copies do not implement
	UsesWinsock(const UsesWinsock &rhs);
	UsesWinsock &operator=(const UsesWinsock &rhs);
};

};
};


#endif