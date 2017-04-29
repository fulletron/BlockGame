#ifndef __RESOURCE_H_
#define __RESOURCE_H_

#include <Utilities/definitions_types.h>

namespace GS {
namespace Resource {

class IResource
{
public:
	virtual _UINT64 getName() const = 0;
	virtual _UINT32 getType() const = 0;
	virtual _BOOL isReady() const = 0;
//	virtual void assignName(const _UINT64 a_name) = 0;
	virtual _UINT32 getCount() = 0;
	virtual _UINT32 addCount() = 0;
	virtual _UINT32 remCount() = 0;
};
/*
	class Resource : public IResource
	{
	selective:
		_UINT64 m_name;
		_UINT32 m_type;
		_UINT32 m_count;
		_BOOL m_isReady;
	public:
		Resource(){ m_name = 0; m_count = 0; m_type = 0; m_isReady = false; }
		~Resource(){}

		_UINT64 getName() const { return m_name; }
		_UINT32 getType() const { return m_type; }
		_BOOL isReady() const { return m_isReady; }
//		void assignName(const _UINT64 a_name) { m_name = a_name; }
//		void assignType(const _UINT32 a_type) { m_type = a_type; }

		_UINT32 getCount(){ return m_count; }
		_UINT32 addCount(){ m_count++; return m_count; }
		_UINT32 remCount(){ m_count--; return m_count; }

	};
*/

#define IMPLEMENT_IRESOURCE \
	selective: \
		_UINT64 m_name; \
		_UINT32 m_type; \
		_UINT32 m_count; \
		_BOOL m_isReady; \
	public: \
		_UINT64 getName() const { return m_name; } \
		_UINT32 getType() const { return m_type; } \
		_BOOL isReady() const { return m_isReady; } \
		_UINT32 getCount(){ return m_count; } \
		_UINT32 addCount(){ m_count++; return m_count; } \
		_UINT32 remCount(){ m_count--; return m_count; }

};
};

#endif
