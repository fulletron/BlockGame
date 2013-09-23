#include "chunkmanager.h"

namespace GS {
namespace Utilities {

_INT32 ChunkManager::init( const _UINT32 a_numChunks, const _UINT32 a_sizeOfChunk )
{
	m_numChunks = a_numChunks;
	m_sizeOfChunk = a_sizeOfChunk;
	m_usedChunks = 0;

	m_pChunk = static_cast<_BYTE*>(malloc( m_numChunks * m_sizeOfChunk ));
	if ( !m_pChunk )
		return 1;

	
	m_investors.init( NUM_INVESTORS );
	//
	m_pFramesInRelation = new Frame*[m_numChunks];
	//

	for( _UINT32 i = 0; i < m_numChunks; ++i )
	{
		m_pFramesInRelation[i] = new Frame( (m_pChunk + (m_sizeOfChunk * i)), m_sizeOfChunk );
	}

	return 0;
}

void ChunkManager::shutdown()
{
	free( m_pChunk );
	for( _UINT32 i = 0; i < m_numChunks; ++i )
	{
		Frame * pFrame = m_pFramesInRelation[i];
		if( pFrame->isValid() )
			pFrame->shutdown();
		delete pFrame;
	}
}

Frame * ChunkManager::createFrame(const _INT64 a_name)
{
	if( m_pFramesInRelation[m_usedChunks]->init( a_name ) )
		return 0;

	m_usedChunks++;

	return m_pFramesInRelation[m_usedChunks - 1]; 
}

Frame * ChunkManager::getFrame( const _INT64 a_name)
{
	for( _UINT32 i = 0; i < m_numChunks; ++i )
	{
		if ( m_pFramesInRelation[i]->getName() == a_name )
		{
			return m_pFramesInRelation[i];
		}
	}
	
	return 0;
}

bool ChunkManager::destroyFrame ( const _INT64 a_name)
{
	for( _UINT32 i = 0; i < m_numChunks; ++i )
	{
		if ( m_pFramesInRelation[i]->getName() == a_name )
		{
			m_pFramesInRelation[i]->shutdown();
			__compress(a_name, i);
			return true;
		}
	}
	return false;
}

void ChunkManager::addInvestor( GSInvestor * const a_pInvestor )
{
	m_investors.add( a_pInvestor );
}

void ChunkManager::__compress( const _INT64 a_name, const _UINT32 a_slot )
{
	_UINT64 adjust_amount = m_sizeOfChunk * (m_usedChunks - a_slot);
	memcpy( m_pFramesInRelation[a_slot], m_pFramesInRelation[m_usedChunks], m_sizeOfChunk );

	for( _UINT32 i = 0; i < m_investors.getSize(); ++i )
		m_investors.get(i)->readjust(a_name, adjust_amount);

	m_usedChunks--;
}

};
};
