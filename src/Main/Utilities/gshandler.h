#ifndef __GSHANDLER_H_
#define __GSHANDLER_H_

#include "typedefinitions.h"
#include "frame.h"
#include "gsobject.h"
#include "gsinvestor.h"

namespace GS {
namespace Utilities {

class GSHandler : public GSInvestor 
{
#ifdef TEST_ENABLED
public:
#else
protected:
#endif
	GSObjectPair * 	m_pData;
	_UINT32 		m_numPairs;

public:
	GSHandler();
	~GSHandler(){}

	_INT32 init( Frame * const a_pFrame, const _UINT32 a_size );
	void shutdown();

	GSKeyPair insert( GSObject * const a_pObject, const _INT64 a_frameName );
	GSObject * get( const _UINT32 a_key );
	void remove( const _UINT32 a_key );

	_UINT32 readjust( const _INT64 a_frameName, const _INT64 a_adjustment );
};

};
};

#endif
