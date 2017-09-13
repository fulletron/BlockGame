#ifndef __RESOURCE_H_
#define __RESOURCE_H_

#include <Graphics/resource/iresource.h>
#include <Utilities/thread/thread.h>

namespace GS {
namespace Resource {

class Resource : public IResource
{
privatized: 
	_BOOL m_isReady;
selective: 
	GS::Thread::GSMutex m_isReadyMutex;
	_UINT64 m_name;
	RType m_type;
	_UINT32 m_count;
	void __setName(_UINT64 a_name){ m_name = a_name; }
	void __setType(RType a_type) { m_type = a_type; }
public:
	_UINT64 getName() const { return m_name; }
	RType getType() const { return m_type; }
	_BOOL isReady()
	{ 
		GSLOCKGUARD(m_isReadyMutex);
		return m_isReady; 
	}

	void setIsReady(_BOOL a_isReady) 
	{
		GSLOCKGUARD(m_isReadyMutex);
		//m_isReadyMutex.lock(); 
		m_isReady = a_isReady;
		//m_isReadyMutex.unlock(); 
	}
	_UINT32 getCount(){ return m_count; }
	_UINT32 addCount(){ m_count++; return m_count; }
	_UINT32 remCount(){ m_count--; return m_count; }
};

};
};

#endif
