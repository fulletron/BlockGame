#ifndef __RESOURCE_H_
#define __RESOURCE_H_

#include <Utilities/typedefinitions.h>

namespace GS {
namespace Graphics {

class IResource
{
public:
	virtual _UINT64 getName() = 0;
	virtual void assignName( const _UINT64 a_name ) = 0;
	virtual _UINT32 getCount() = 0;
	virtual _UINT32 addCount() = 0;
	virtual _UINT32 remCount() = 0;
};

class Resource : public IResource
{
selective:
	_UINT64 m_name;
	_UINT32 m_count;
public:
	_UINT64 getName(){ return m_name; }

	void assignName( const _UINT64 a_name ) 
	{
		m_name = a_name;
	}

	_UINT32 getCount(){ return m_count; }
	_UINT32 addCount(){ m_count++; return m_count; }
	_UINT32 remCount(){ m_count--; return m_count; }

};

};
};

#endif
