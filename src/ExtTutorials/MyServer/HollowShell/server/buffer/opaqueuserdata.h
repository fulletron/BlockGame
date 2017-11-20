#ifndef __OPAQUEUSERDATA_H__
#define __OPAQUEUSERDATA_H__

#include "../../definitions_types.h"

// KYLE :: TEST :: remove redefines
#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif

namespace GS {
namespace Server {

/*
* a holder for a void* user data using InterlockedExchangePointer 
*/
class OpaqueUserData
{
public:
	unsigned long getUserData() const
	{
		return reinterpret_cast<unsigned long>(getUserPtr());
	}

	void setUserData(unsigned long data)
	{
		setUserPtr(reinterpret_cast<void*>(data));
	}

	void * getUserPtr() const
	{
		return InterlockedExchangePointer(&(const_cast<void*>(m_pUserData)), m_pUserData);
	}

	void setUserPtr(void * pData)
	{
		InterlockedExchangePointer(&m_pUserData, pData);
	}

selective:
	OpaqueUserData()
		: m_pUserData(0)
	{
	}

	~OpaqueUserData()
	{
		m_pUserData = 0;
	}

	void *m_pUserData;

	// No copies do not implement
	OpaqueUserData(const OpaqueUserData &rhs);
	OpaqueUserData &operator=(const OpaqueUserData &rhs);
};

class UserData : public OpaqueUserData
{
	// UserData is a shim class that allows Socket to inherit from two 
	// OpaqueUserData bases without ambiguity
};

class ServerData : public OpaqueUserData
{
	// ServerData is a shim class that allows Socket to inherit from two 
	// OpaqueUserData bases without ambiguity
};

};
};

/*
REGARDING InterlockedExchangePointer:
This function copies the address passed as the second parameter to the first and returns the original 
address of the first.
On a 64-bit system, the parameters are 64 bits and the Target parameter must be aligned on 64-bit 
boundaries; otherwise, the function will behave unpredictably. On a 32-bit system, the parameters 
are 32 bits and the Target parameter must be aligned on 32-bit boundaries.
The interlocked functions provide a simple mechanism for synchronizing access to a variable that is 
shared by multiple threads. This function is atomic with respect to calls to other interlocked 
functions.
This function is implemented using a compiler intrinsic where possible. For more information, see the 
WinBase.h header file and _InterlockedExchangePointer.
This function generates a full memory barrier (or fence) to ensure that memory operations are 
completed in order.

*/

#endif