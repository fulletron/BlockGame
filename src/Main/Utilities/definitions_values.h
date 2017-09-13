#ifndef __DEFINITIONS_VALUES_H_
#define __DEFINITIONS_VALUES_H_

#include "definitions_types.h"

#ifndef FLT_MAX
#define FLT_MAX							3.402823466e+38F        /* max value */
#endif

#define SCREEN_WIDTH 800
//1920
#define SCREEN_HEIGHT 600
//1080

#define FPS_CAP_MS 0.016666

//#define FPS_CAP_MS -0.016666

//static const float INFINITY = FLT_MAX;
//static const float EPSILON  = 0.001f;
int contextsharetest(void * a_window);
int doThreads(void);

namespace CV8 {
const _INT64 test = 0000000000001;
const _INT64 RES_FONT_KASHSCRIPT_16 = 8243404172493550435; // rftkassc
const _INT64 RES_FONT_KASHSCRIPT_64 = 8243404172493550436; // rftkassc
const _INT64 RES_SP_FBDRAW = 999;
const _INT64 RES_SP_FONTDRAW = 1001;
const _INT64 RES_SP_TEXRECTDRAW = 998;
const _INT64 RES_SH_BASEFONTVS = 1002;
const _INT64 RES_SH_BASEFONTFS = 1003;
const _INT64 RES_SH_BASEFBVS = 1004;
const _INT64 RES_SH_BASEFBFS = 1005;
const _INT64 RES_SH_TEXRECTVS = 1006;
const _INT64 RES_SH_TEXRECTFS = 1007;
const _INT64 RES_TEX_PANEBKG = 3001;
const _INT64 RES_TEX_FADEBAR = 3002;
const _INT64 RES_MSH_RECT = 5001;
const _INT64 RES_MSH_SCREEN = 5002;
//const _INT64 FRAME001 = 100001;
//const _INT64 FRAME002 = 100002;
//const _INT64 FRAME003 = 100003;
//const _INT64 FRAME004 = 100004;
//const _INT64 FRAME_TRASH = 100005;
//const _INT64 FRAME_SMALLRES = 100006;

namespace TEX {
const _INT64 PANEBKG = 3001;
const _INT64 FADEBAR = 3002;
};
};

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

#endif
