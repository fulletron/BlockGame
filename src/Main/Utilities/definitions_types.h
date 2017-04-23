#ifndef __DEFINITIONS_TYPES_H_
#define __DEFINITIONS_TYPES_H_

typedef double							_DOUBLE;
typedef long							_LONG;
typedef float							_FLOAT;
typedef bool							_BOOL;
#define _SIZET size_t
//typedef size_t							_SIZET;

#include <new>

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

union _UNION8 {
	_CHAR		asChar;
	_UCHAR		asUChar;
	_BYTE		asByte;
	_SHORT		asShort;
	_USHORT		asUShort;
	_INT32		asInt32;
	_INT64		asInt64;
	_UINT32		asUInt32;
	_UINT64		asUInt64;
	_DOUBLE		asDouble;
	_LONG		asLong;
	_FLOAT		asFloat;
	_BOOL		asBool;
};

#define RC(NEW_TYPE,CASTABLE_VALUE) reinterpret_cast<NEW_TYPE>(CASTABLE_VALUE)
#define STATIC_CAST(NEW_TYPE,CASTABLE_VALUE) static_cast<NEW_TYPE>(CASTABLE_VALUE)

#include <vector>
#define _VECTOR std::vector

#include <cassert> // KYLE :: TODO :: WIN32 ONLY?
//#define GS_ASSERT(BOOL_WE_WANT, BOOL_TO_TEST,RET) assert(BOOL_WE_WANT == BOOL_TO_TEST)
#define GS_ASSERT(BOOL_WE_WANT, BOOL_TO_TEST,RET) if( BOOL_WE_WANT != BOOL_TO_TEST ) return RET;

template<typename T>
class _VEC2D
{
public:
	T x;
	T y;
	
	_VEC2D(){}
	_VEC2D(T a_x, T a_y) : x(a_x), y(a_y){}
};

template<typename T>
class _VEC3D
{
public:
	T x;
	T y;
	T z;
	
	_VEC3D(){}
	_VEC3D(T a_x, T a_y, T a_z) : x(a_x), y(a_y), z(a_z){}
};

template<typename T>
class _VEC4D
{
public:
	union
	{
		T pos_x;
		T col_r;
	};

	union
	{
		T pos_y;
		T col_g;
	};

	union
	{
		T pos_z;
		T box_width;
		T col_b;
	};

	union
	{
		T a;
		T box_height;
	};
	
	_VEC4D(){}
	_VEC4D(T a_x, T a_y, T a_z, T a_a) : pos_x(a_x), pos_y(a_y), pos_z(a_z), a(a_a){}
};



// IF IM TESTING THINGS, PROTECTED THINGS BECOME
// PUBLIC!!!!!!!!
#ifdef TEST_ENABLED
#define selective public
#else
#define selective protected
#endif

#ifdef TEST_ENABLED
#define privatized public
#else
#define privatized private
#endif

// KYLE :: NOT WELL PLACED, BUT IT WORKS
#define DEBUG_OUTPUT_ENABLED

#ifdef DEBUG_OUTPUT_ENABLED
#define DEBUG_OUT(x) std::cout << x << std::endl;
#else
#define DEBUG_OUT(x) ;
#endif

#endif
