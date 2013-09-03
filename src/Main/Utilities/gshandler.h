#ifndef __GSHANDLER_H_
#define __GSHANDLER_H_

#include "typedefinitions.h"
#include "frame.h"

namespace GS {
namespace Utilities {

// ONLY EVER USING IT FOR VOID Ps
template<typename DATA_TYPE>
class GSHandler 
{
public:
private:
	DATA_TYPE * m_pData;
	_UINT32 m_size;

public:
	GSHandler();
	~GSHandler(){}

	_INT32 init( Frame * const a_pFrame, const _UINT32 a_size );
	void shutdown();

	_UINT32 insert( DATA_TYPE a_data );
	DATA_TYPE get( const _UINT32 a_key );
	void remove( const _UINT32 a_key );
};

};
};

#endif
