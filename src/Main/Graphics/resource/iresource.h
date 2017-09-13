#ifndef __IRESOURCE_H_
#define __IRESOURCE_H_

#include <Utilities/definitions_types.h>

#include <Utilities/thread/thread.h>

namespace GS {
namespace Resource {

	const enum RType 
	{
		UNKNOWN = 0,
		TEXTURE,
		MESH,
		SHADERPROGRAM,
		SHADER,
	};

class IResource
{
selective:
	virtual void __setName(_UINT64) = 0;
	virtual void __setType(RType) = 0;
public:
	virtual _UINT64 getName() const = 0;
	virtual RType getType() const = 0;
	virtual _BOOL isReady() = 0;
	virtual void setIsReady(_BOOL a_isReady) = 0;
//	virtual void assignName(const _UINT64 a_name) = 0;
	virtual _UINT32 getCount() = 0;
	virtual _UINT32 addCount() = 0;
	virtual _UINT32 remCount() = 0;
};
/*
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
*/
/*
#define IMPLEMENT_IRESOURCE \
	privatized: \
		_BOOL m_isReady; \
	selective: \
		GS::Thread::GSMutex m_isReadyMutex; \
		_UINT64 m_name; \
		RType m_type; \
		_UINT32 m_count; \
		void __setName(_UINT64 a_name){ m_name = a_name; } \
		void __setType(RType a_type) {m_type = a_type;} \
	public: \
		_UINT64 getName() const { return m_name; } \
		RType getType() const { return m_type; } \
		_BOOL isReady() { return m_isReady; } \
		void setReady(_BOOL a_ready) { m_isReadyMutex.lock(); m_isReady = a_ready; m_isReadyMutex.unlock(); } \
		_UINT32 getCount(){ return m_count; } \
		_UINT32 addCount(){ m_count++; return m_count; } \
		_UINT32 remCount(){ m_count--; return m_count; }
*/

};
};

typedef GS::Resource::RType RESTYPE;

#endif
