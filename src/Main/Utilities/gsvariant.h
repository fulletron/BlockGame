#ifndef __GSVARIANT_H_
#define __GSVARIANT_H_

#include "typedefinitions.h"

namespace GS {
namespace Utilities {

struct GSVariant {
	enum TYPE 
	{
		TYPE_UINT32,
		TYPE_UINT64,
		TYPE_INT32,
		TYPE_INT64,
		TYPE_FLOAT,
		TYPE_BYTE,
		TYPE_COUNT,
	};

	TYPE m_type;

	union
	{
		_UINT32 m_as_UINT32;
		_UINT64 m_as_UINT64;
		_INT32 m_as_INT32;
		_INT64 m_as_INT64;
		_FLOAT m_as_FLOAT;
		_BYTE m_as_BYTE;
	};
};

};
};

#endif
