#ifndef __TYPEDEFINITIONS_H_
#define __TYPEDEFINITIONS_H_

#define FLT_MAX							3.402823466e+38F        /* max value */

static const float INFINITY =			FLT_MAX;
static const float EPSILON  =			0.001f;

typedef double							_DOUBLE;
typedef long							_LONG;
typedef float							_FLOAT;
typedef bool							_BOOL;

#if ((defined  (WIN32) || defined(_WIN32)) && !defined(_STDINT))
	// On windows, we define the C99 types if they haven't already been included.
	// We don't #include <stdint.h> here because it bleeds out Windows.h, which 
	// is problematic.
	typedef char							_CHAR;
	typedef unsigned char					_UCHAR;
	typedef unsigned char					_BYTE;
	typedef signed short					_SHORT;
	typedef unsigned short					_USHORT;
	typedef signed __int32					_INT32;
	typedef signed __int64					_INT64;
	typedef unsigned __int32				_UINT32;
	typedef unsigned __int64				_UINT64;

	#include <string>
#else
#include <stdint.h>

	typedef int8_t							_CHAR;
	typedef uint8_t							_UCHAR;
	typedef uint8_t							_BYTE;
	typedef int16_t							_SHORT;
	typedef uint16_t						_USHORT;
	typedef int32_t							_INT32;
	typedef uint32_t						_UINT32;
	typedef int64_t							_INT64;
	typedef uint64_t						_UINT64;

	#include <string>

#endif

// This may be in the wrong spot
static const _INT32 NUMCHUNKS = 24;
static const _INT32 SIZECHUNK = 20480000;

namespace GS {
namespace Utilities {



};
};

#endif
