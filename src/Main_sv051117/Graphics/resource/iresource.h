#ifndef __RESOURCE_H_
#define __RESOURCE_H_

#include <Utilities/definitions_types.h>

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
		RType m_type; \
		_UINT32 m_count; \
		_BOOL m_isReady; \
		void __setName(_UINT64 a_name){ m_name = a_name; } \
		void __setType(RType a_type) {m_type = a_type;} \
	public: \
		_UINT64 getName() const { return m_name; } \
		RType getType() const { return m_type; } \
		_BOOL isReady() const { return m_isReady; } \
		_UINT32 getCount(){ return m_count; } \
		_UINT32 addCount(){ m_count++; return m_count; } \
		_UINT32 remCount(){ m_count--; return m_count; }

};
};

typedef GS::Resource::RType RESTYPE;

#endif
