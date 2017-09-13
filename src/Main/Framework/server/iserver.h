#ifndef __ISERVER_H_
#define __ISERVER_H_

#include <Utilities\definitions_types.h>

namespace GS {
namespace Server {

class IServer
{
public:
	/*
	* Look through the inbound message list and
	* do that work.
	*/
	virtual _UINT32 handleInboundMessages() = 0;

	/*
	* Add a single message to the outbound list
	*/
	virtual _UINT32 prepareOutboundMessage(_UINT32 a_msg) = 0;

	/*
	* Give all the messages in the outbound list to NET or ClientList
	*/
	virtual _UINT32 sendOutboundMessages() = 0;
};

};
};

#endif