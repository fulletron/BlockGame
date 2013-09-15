#include "gshandler.h"
#include <string.h>
#include "gsassert.h"

namespace GS {
namespace Utilities {

GSHandler::GSHandler()
{
	m_size = 0;
	m_pData = 0;
}

_INT32 GSHandler::init( Frame * const a_pFrame, const _UINT32 a_size )
{
	m_size = a_size;
	m_pData = a_pFrame->allocate( a_size, Frame::PLACE::TOP );
	memset( m_pData, 0, m_size * sizeof(void *) );

	return 0;
}

void GSHandler::shutdown()
{
	m_pData = 0;
	m_size = 0;
}

_UINT32 GSHandler::insert( void * a_pData )
{
	int i = 0;
	while( m_pData[i] != 0 && i < m_size )
		++i;
	
	//assert(i < m_size);
	if (i >= m_size)
		return -1;

	m_pData[i] = a_pData;
		
	return i;
}

void * GSHandler::get( const _UINT32 a_key )
{
	return m_pData[a_key];
}

void GSHandler::remove( const _UINT32 a_key )
{
	m_pData[a_key] = 0;
}

};
};
