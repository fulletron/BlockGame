#ifndef __NET_H_
#define __NET_H_ 

#include "typedefinitions.h"

// TODO :: NET STUFF

class INetObj {
public:
	/**
	* Tell the g_net to send a_msg from a_from. msg data is stored in a_data, 
	* and is of a_size.
	*/
	virtual void sendInstruction( 
		const _UINT32 a_from,
		const _UINT32 a_obj, 
		const _UINT32 a_msg, 
		const _USHORT a_size, 
		void * a_data) = 0; // PERHAPS A STRING? OR THIS FUNCTION WILL
					// SERIALIZE
	
	/**
	* TODO:: KYLE ::
	* This probably doesn't need parameters if i'm doing the ringbuffer way
	* send the msg over the net, store the entire msg in the ringbuffer,
	* extract the first four elements from the ringbuffer (from, object,
	* msg, size), then read for size amount of bytes, store it based on
	* the msg type? don't know. maybe.
	*/
	virtual void performInstruction(  ) = 0;
};

class Net : public INetObj {
selective:

public:
	// Net is either a client or server 
	void init(){}

	void sendInstruction( 
		const _UINT32 a_from,
		const _UINT32 a_obj, 
		const _UINT32 a_msg, 
		const _USHORT a_size, 
		void * a_data) {}
};

#endif
