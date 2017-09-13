#ifndef __CLIENT_H_
#define __CLIENT_H_

#include <Framework\client\iclient.h>

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

class Client : public IClient
{
public:

	virtual _UINT32 handleInboundMessages()
	{
		return 0;
	}

	/*
	* Add a single message to the outbound list
	*/
	virtual _UINT32 prepareOutboundMessage(_UINT32 a_msg)
	{
		return 0;
	}

	/*
	* Give all the messages in the outbound list to NET or Serverlist
	*/
	virtual _UINT32 sendOutboundMessages()
	{
		return 0;
	}
};

};
};

#endif