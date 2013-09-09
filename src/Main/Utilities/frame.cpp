#include <assert.h>
#include <string.h>
#include "frame.h"

namespace GS {
namespace Utilities {

Frame::Frame(void * a_pAddress)
{
	m_pMemBlock = a_pAddress;
	shutdown();
}

void Frame::__zerofStops(const PLACE & a_place)
{
	for( int i = 0; i < MAX_FSTOPS - 1; ++i )
		m_pfStop[a_place][i] = 0;
}

bool Frame::setfStop(const PLACE & a_place)
{
	if( !m_pfStop[a_place][MAX_FSTOPS - 1] )
	{
		for( int i = 0; i < MAX_FSTOPS - 1; ++i )
			m_pfStop[a_place][i+1] = m_pfStop[a_place][i];

		m_pfStop[a_place][0] = m_pCurrentLoc[a_place];
		return true;
	}
	return false;
}

bool Frame::freefStop(const PLACE & a_place)
{
	// pop fStop
	if( m_pfStop[a_place][0] )
	{
		PLACE::BOT;
		
		if( a_place == PLACE::BOT )
		{
			memset( m_pfStop[a_place][0], 0, (_UINT64)m_pCurrentLoc[a_place] - (_UINT64)m_pfStop[a_place][0] );
		}
		else
		{
			memset( m_pCurrentLoc[a_place], 0, (_UINT64)m_pfStop[a_place][0] - (_UINT64)m_pCurrentLoc[a_place] );
		}

		m_pCurrentLoc[a_place] = m_pfStop[a_place][0];
		
		for( int i = 1; i < MAX_FSTOPS; ++i )
			m_pfStop[a_place][i-1] = m_pfStop[a_place][i];
		m_pfStop[a_place][MAX_FSTOPS - 1] = 0;
		return true;
	}
	return false;
}

void * Frame::allocate( const _INT32 a_sizeInBytes, const PLACE & a_place )
{
	void * pMem = 0;
	if( (_UINT64)m_pCurrentLoc[PLACE::BOT] + a_sizeInBytes > (_UINT64)m_pCurrentLoc[PLACE::TOP] )
		return 0;

	if( a_place == PLACE::TOP )
	{
		m_pCurrentLoc[PLACE::TOP] = (void*)((_UINT64)m_pCurrentLoc[PLACE::TOP] - a_sizeInBytes);
		pMem = m_pCurrentLoc[PLACE::TOP];	
	}
	else
	{
		pMem = m_pCurrentLoc[PLACE::BOT];
		m_pCurrentLoc[PLACE::BOT] = (void*)((_UINT64)m_pCurrentLoc[PLACE::BOT] + a_sizeInBytes);
	}

	return pMem;
}

_INT32 Frame::init(const _INT64 a_name)
{
	m_name = a_name;
	m_pCurrentLoc[PLACE::BOT] = m_pMemBlock;
	m_pCurrentLoc[PLACE::TOP] = (void*) ((_UINT64)m_pMemBlock + SIZECHUNK);
	return 0;
}

void Frame::shutdown()
{
	memset(m_pMemBlock, 0, SIZECHUNK);
	m_name = 0;

	m_pCurrentLoc[PLACE::BOT] = 0;
	m_pCurrentLoc[PLACE::TOP] = 0; 

	__zerofStops(PLACE::BOT);
	__zerofStops(PLACE::TOP);
	// it would be faster to memset,
	// for now do this to excersize
	// functions
	// TODO
	//while(freefStop(PLACE::TOP)){}
	//while(freefStop(PLACE::BOT)){}

	//m_pMemBlock = 0;
}

bool Frame::isValid()
{
	if( m_name ) 
		return true;
	return false;
}

};
};
