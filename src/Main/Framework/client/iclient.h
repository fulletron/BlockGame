#ifndef __ICLIENT_H_
#define __ICLIENT_H_

#include <Utilities\definitions_types.h>

// CLIENT
// Will only ever send messages to the "Server" local queue,
// or to the "Net" object to send out.
// Get seed to build map
// Interpret input (like movement, attacks)
// send that to server
// Keep local track of where the entities are


namespace GS {
namespace Client {

class IClient
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
	* Give all the messages in the outbound list to NET or Serverlist
	*/
	virtual _UINT32 sendOutboundMessages() = 0;
};

};
};

#endif