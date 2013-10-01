#include "gshandler.h"
#include <string.h>
//#include "gsassert.h"

namespace GS {
namespace Utilities {

GSHandler::GSHandler()
{
	m_numPairs = 0;
	m_pData = 0;
}

_INT32 GSHandler::init( Frame * const a_pFrame, const _UINT32 a_maximumHandles )
{
	m_numPairs = a_maximumHandles;
	m_pData = reinterpret_cast<GS::Utilities::_GSObjectPair*>(a_pFrame->allocate( 
			a_maximumHandles * sizeof( _GSObjectPair ), 
			Frame::PLACE::TOP 
			));

	memset( m_pData, 0, a_maximumHandles * sizeof( _GSObjectPair ) );

	return 0;
}

void GSHandler::shutdown()
{
	m_pData = 0;
	m_numPairs = 0;
}

_GSKeyPair GSHandler::insert( GSObject * const a_pObject, const _INT64 a_frameName )
{
	_UINT32 i = 0;

	while( (m_pData[i].pGSObject) != 0 && i < m_numPairs )
		++i;
	
	//assert(i < m_size);
	if (i >= m_numPairs)
		return _GSKeyPair( 0, 0 );

	m_pData[i] = _GSObjectPair( a_pObject, a_frameName );
		
	return _GSKeyPair( i, a_frameName );
}

GSObject * GSHandler::get( const _UINT32 a_key )
{
	return m_pData[a_key].pGSObject;
}

void GSHandler::remove( const _UINT32 a_key )
{
	m_pData[a_key].pGSObject = 0;
	m_pData[a_key].ownerFrameName = 0;
}

_UINT32 GSHandler::readjust( const _INT64 a_frameName, const _INT64 a_adjustment )
{
	_UINT32 num_adjusted = 0;
	for( _UINT32 i = 0; i < m_numPairs; ++i )
		if( m_pData[i].ownerFrameName == a_frameName )
		{
			m_pData[i].pGSObject -= a_adjustment;
			num_adjusted++;
		}
	
	return num_adjusted;
}

};
};
