#ifndef __DEFINITIONS_H_
#define __DEFINITIONS_H_

#include "define_gettersetter.h"

#include "..\..\Utilities\gsmap.h"
#include "..\..\Utilities\gsvector.h"
#include "..\..\Utilities\gsreferencemap.h"

// WINDOWS/DX INIT DEFINITIONS
#define WINDOW_TITLE					"TRUSTY CHORDS"
#define WINDOW_NAME						"KYLE'S MONSTER GAME"

#define CHROME_SIZE_TOP					30
#define CHROME_SIZE_LEFT				8

#define SCREEN_WIDTH					1600
#define SCREEN_HEIGHT					1080

#define LOGICAL_HEIGHT					128 // 92 // NORMALL IS 92
#define LOGICAL_HEIGHT_SCALE_NUM		20.24

#define KEYSCALE_ONE					0.6f // SCALE OF ALL SCREEN BASED TEXTURES STARTS HERE-
//#define GLOBAL_3D_SCALE					D3DXVECTOR3(1.0f,1.0f,1.0f)

#define KEYSCALE_WIDTH					1920 // 1920 // MULTIPLY THIS BY ASPECT RATIO
#define KEYSCALE_HEIGHT					1460 // 1460 // MULTIPLY THIS BY ASPECT RATIO

#define MINIMUM_WIDTH					1024
#define MINIMUM_HEIGHT					768

#define FLT_MAX							3.402823466e+38F        /* max value */

#define EYE_HEIGHT						4.0f
#define EYE_FORWARD						1.4f

#define SIZEOFEVENTS					65536
#define USHORTMAX						65535
#define FOCUSVALUE						4000

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

#define DIR_S "/"
#define DIR_IN "Internal/"
#define DIR_RES "Resources/"
#define DIR_FONTS "Fonts/"
#define DIR_TEXTS "Textures/"

#define _GSMAP(x,y) GS::UtilitiesNS::GSMap<x,y>
#define _GSVECTOR(x) GS::UtilitiesNS::GSVector<x>
#define _GSREFMAP(x,y) GS::UtilitiesNS::GSReferenceMap<x,y>

#define _DB256(x) (x/256.0f)

	/*
template <typename T>
typedef struct _RECT
{
    T    left;
    T    top;
    T    right;
    T    bottom;
};
*/

template <typename T>
struct _ARRAYFOUR
{
    T    r;
    T    g;
    T    b;
    T    a;

	_ARRAYFOUR<T>(){}

	_ARRAYFOUR<T>(T r, T g, T b, T a)
		: r(r), g(g), b(b), a(a)
	{}
};

enum ALIGNMENT {
	ALIGN_CENTER = 1,
	ALIGN_LEFT,
	ALIGN_RIGHT,
};


template <typename T>
struct _RECT
{
    T    left;
    T    bottom;
    T    width;
    T    height;

	_RECT<T>(){}

	_RECT<T>(T a_left, T a_bottom, T a_width, T a_height)
		: left(a_left), bottom(a_bottom), width(a_width), height(a_height)
	{}

	void set(const T & a_left, const T & a_bottom, const T & a_width, const T & a_height)
	{
		left = a_left; bottom = a_bottom; width = a_width; height = a_height;
	}
};

typedef struct _2DFLOATVEC {
	float x;
	float y;

	_2DFLOATVEC(){}
	_2DFLOATVEC(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}
	_2DFLOATVEC operator=(const _2DFLOATVEC & a_floatVec)
	{
		x = a_floatVec.x;
		y = a_floatVec.y;
		return *this;
	}
	_2DFLOATVEC operator+=(const _2DFLOATVEC & a_floatVec)
	{
		x += a_floatVec.x;
		y += a_floatVec.y;
		return *this;
	}
} _2DFLOATVEC;

typedef struct _3DFLOATVEC {
	float x;
	float y;
	float z;
	_3DFLOATVEC(){}
	_3DFLOATVEC(float a_x, float a_y, float a_z)
	{
		x = a_x;
		y = a_y;
		z = a_z;
	}
	_3DFLOATVEC operator=(const _3DFLOATVEC & a_floatVec)
	{
		x = a_floatVec.x;
		y = a_floatVec.y;
		z = a_floatVec.z;
		return *this;
	}
	_3DFLOATVEC operator+=(const _3DFLOATVEC & a_floatVec)
	{
		x += a_floatVec.x;
		y += a_floatVec.y;
		z += a_floatVec.z;
		return *this;
	}
} _3DFLOATVEC;

#endif