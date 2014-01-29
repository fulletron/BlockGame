#ifndef __TYPEDEFINITIONS_H_
#define __TYPEDEFINITIONS_H_

#ifndef FLT_MAX
#define FLT_MAX							3.402823466e+38F        /* max value */
#endif

//#define FPS_CAP_MS 0.016666
#define FPS_CAP_MS -0.016666

//static const float INFINITY = FLT_MAX;
//static const float EPSILON  = 0.001f;

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

// This may be in the wrong spot
static const _UINT32 NUMCHUNKS = 24;
static const _UINT32 SIZECHUNK = 20480000;
static const _UINT32 NUM_VARIANTS_PER_MSG = 8;
static const _UINT32 NUM_INVESTORS = 16;

_INT64 CV8(char * a_name);

#define RC(x,y) reinterpret_cast<x>(y)
#define SC(x,y) static_cast<x>(y)

inline _BYTE* INALIGNUP( _BYTE* a_pAddress, _UINT32 a_sizeInBytes)
{
	int nBytes = 0;

	if(a_sizeInBytes >= 8)
		nBytes = 8;
	else if(a_sizeInBytes >= 4)
		nBytes = 4;
	else if(a_sizeInBytes >= 2)
		nBytes = 2;
	else
		nBytes = 1;

	_UINT64 address = reinterpret_cast<_UINT64>(a_pAddress);
	_UINT64 remainder = address % nBytes;

	return reinterpret_cast<_BYTE *>( address + remainder );
}

inline _BYTE* INALIGNDOWN( _BYTE* a_pAddress, _UINT32 a_sizeInBytes)
{
	int nBytes = 0;

	if(a_sizeInBytes >= 8)
		nBytes = 8;
	else if(a_sizeInBytes >= 4)
		nBytes = 4;
	else if(a_sizeInBytes >= 2)
		nBytes = 2;
	else
		nBytes = 1;

	_UINT64 address = reinterpret_cast<_UINT64>(a_pAddress);
	_UINT64 remainder = address % nBytes;

	return reinterpret_cast<_BYTE *>( address - remainder );
}

template<typename T>
class Vec2D
{
public:
	T x;
	T y;
	
	Vec2D(){}
	Vec2D(T a_x, T a_y) : x(a_x), y(a_y){}
};

template<typename T>
class Vec3D
{
public:
	T x;
	T y;
	T z;
	
	Vec3D(){}
	Vec3D(T a_x, T a_y, T a_z) : x(a_x), y(a_y), z(a_z){}
};

template<typename T>
class Vec4D
{
public:
	T x;
	T y;
	T z;
	T a;
	
	Vec4D(){}
	Vec4D(T a_x, T a_y, T a_z, T a_a) : x(a_x), y(a_y), z(a_z), a(a_a){}
};


#define FR_BASE CV8("basefram")
#define FR_TRASH CV8("trash000")

// IF IM TESTING THINGS, PROTECTED THINGS BECOME
// PUBLIC!!!!!!!!
#ifdef TEST_ENABLED
#define selective public
#else
#define selective protected
#endif

namespace GS {
namespace Utilities {

};
};

#endif
