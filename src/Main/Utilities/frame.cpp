#include <assert.h>
#include <string.h>
#include "frame.h"

namespace GS {
namespace Utilities {

Frame::Frame(_BYTE * a_pAddress, const _UINT32 a_size)
{
	m_pMemBlock = a_pAddress;
	m_size = a_size;
	shutdown();
}

void Frame::__zerofStops(const PLACE & a_place)
{
	for( int i = 0; i < MAX_FSTOPS; ++i )
		m_pfStop[a_place][i] = 0;
}

void Frame::offsetfStops(const _INT64 a_offset)
{
	for( int i = 0; i < 2; ++i )
		for( int j = 0; j < MAX_FSTOPS; ++j )
			if(m_pfStop[i][j])
			{
				m_pfStop[i][j] += a_offset;
			}
}

bool Frame::setfStop(const PLACE & a_place)
{
	if( !m_pfStop[a_place][MAX_FSTOPS - 1] )
	{
		for( int i = MAX_FSTOPS-1; i > 0; --i )
			m_pfStop[a_place][i] = m_pfStop[a_place][i-1];

		m_pfStop[a_place][0] = m_pCurrentLoc[a_place];
		return true;
	}
	return false;
}

_BYTE * Frame::freefStop(const PLACE & a_place)
{
	// pop fStop
	if( m_pfStop[a_place][0] )
	{
		if( a_place == PLACE::BOT )
		{
			memset( m_pfStop[a_place][0], 0, m_pCurrentLoc[a_place] - m_pfStop[a_place][0] );
		}
		else
		{
			memset( m_pCurrentLoc[a_place], 0, m_pfStop[a_place][0] - m_pCurrentLoc[a_place] );
		}

		m_pCurrentLoc[a_place] = m_pfStop[a_place][0];
		
		for( int i = 1; i < MAX_FSTOPS; ++i )
			m_pfStop[a_place][i-1] = m_pfStop[a_place][i];
		m_pfStop[a_place][MAX_FSTOPS - 1] = 0;
		return m_pCurrentLoc[a_place];
	}
	return 0;
}

_BYTE * Frame::allocate( const _INT32 a_sizeInBytes, const PLACE & a_place )
{
	_BYTE * pMem = 0;
	
	if( a_place == TOP )
	{
		_BYTE * pUnProspectiveLoc = m_pCurrentLoc[TOP] - a_sizeInBytes;
		_BYTE * pProspectiveLoc = INALIGNDOWN(pUnProspectiveLoc, a_sizeInBytes);

		if( pProspectiveLoc < m_pCurrentLoc[BOT] )
			return 0;

		m_pCurrentLoc[TOP] = pMem = pProspectiveLoc;	
	}
	else
	{
		_BYTE * pUnProspectiveLoc = m_pCurrentLoc[BOT];
		_BYTE * pProspectiveLoc = INALIGNUP(pUnProspectiveLoc, a_sizeInBytes);

		if( pProspectiveLoc  + a_sizeInBytes > m_pCurrentLoc[TOP] )
			return 0;

		pMem = pProspectiveLoc;
		m_pCurrentLoc[BOT] = pMem + a_sizeInBytes;
	}
	 
	return pMem;
}

_INT32 Frame::init(const _INT64 a_name)
{
	m_name = a_name;
	m_pCurrentLoc[BOT] = m_pMemBlock;
	m_pCurrentLoc[TOP] = m_pMemBlock + m_size;
	return 0;
}

void Frame::shutdown()
{
	memset(m_pMemBlock, 0, m_size );
	m_name = 0;

	m_pCurrentLoc[BOT] = 0;
	m_pCurrentLoc[TOP] = 0; 

	__zerofStops(BOT);
	__zerofStops(TOP);
}

void Frame::copyFrame( Frame * a_pFromFrame )
{
	// Find the difference between the two memory blocks
	// the DIFF value is valid to currentLocs and fstops
	_BYTE * pFrom = RC( _BYTE *, a_pFromFrame->getMemBlock() );
	_BYTE * pTo = RC( _BYTE *, m_pMemBlock );
	_INT64 diff = pFrom - pTo;

	_BYTE * pMemBlock = m_pMemBlock;
	memcpy( m_pMemBlock, a_pFromFrame->getMemBlock(), m_size );

	m_pCurrentLoc[TOP] = a_pFromFrame->m_pCurrentLoc[TOP] - diff;

	m_pCurrentLoc[BOT] = a_pFromFrame->m_pCurrentLoc[BOT] - diff;

	__copyfStops( a_pFromFrame );

	offsetfStops(-diff);

	m_name = a_pFromFrame->getName();

	m_pMemBlock = pMemBlock;
}

void Frame::__copyfStops( Frame * a_pFromFrame )
{
	for( int i = 0; i < 2; ++i )
		for( int j = 0; j < MAX_FSTOPS; ++j )
			m_pfStop[i][j] = a_pFromFrame->m_pfStop[i][j];
}

bool Frame::isValid()
{
	if( m_name ) 
		return true;
	return false;
}

};
};
