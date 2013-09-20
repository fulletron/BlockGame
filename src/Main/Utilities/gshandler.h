#ifndef __GSHANDLER_H_
#define __GSHANDLER_H_

#include "typedefinitions.h"
#include "frame.h"
#include "gsobject.h"

namespace GS {
namespace Utilities {

class GSHandler 
{
public:
private:
	_GSObjectPair * 	m_pData;
	_UINT32 		m_numPairs;

public:
	GSHandler();
	~GSHandler(){}

	_INT32 init( Frame * const a_pFrame, const _UINT32 a_size );
	void shutdown();

	_GSKeyPair insert( GSObject * const a_pObject, const _INT64 a_frameName );
	GSObject * get( const _UINT32 a_key );
	void remove( const _UINT32 a_key );

	bool adjust( const _INT64 a_frameName, const _UINT32 a_adjustment );
};

};
};

#endif
