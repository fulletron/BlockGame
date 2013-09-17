#include "chunkmanager.h"

namespace GS {
namespace Utilities {

_INT32 ChunkManager::init( const _UINT32 a_numChunks, const _UINT32 a_sizeOfChunk )
{
	m_numChunks = a_numChunks;
	m_sizeOfChunk = a_sizeOfChunk;

	m_pChunk = malloc( m_numChunks * m_sizeOfChunk );
	if ( !m_pChunk )
		return 1;

	//
	m_pFramesInRelation = new Frame*[m_numChunks];
	//

	for( _UINT32 i = 0; i < m_numChunks; ++i )
	{
		m_pFramesInRelation[i] = new Frame( (void*) ((_UINT64)m_pChunk + (m_sizeOfChunk * i)) );
	}

	return 0;
}

void ChunkManager::shutdown()
{
	free( m_pChunk );
	for( _UINT32 i = 0; i < m_numChunks; ++i )
	{
		delete m_pFramesInRelation[i];
	}
}

Frame * ChunkManager::createFrame(const _INT64 a_name)
{
	//TODO
	// IN DEBUG, CHECK FOR NAME COLLISIONS
	_UINT32 i;
	for( i = 0; i < m_numChunks; ++i )
	{
		if ( !m_pFramesInRelation[i]->isValid() )
		{
			break;
		}
	}

	// THIS SHOULD BE AN ASSERT
	if( i == m_numChunks )
		return 0;

	if( m_pFramesInRelation[i]->init( a_name ) )
		return 0;

	return m_pFramesInRelation[i]; 
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

void ChunkManager::destroyFrame ( const _INT64 a_name)
{
	for( _UINT32 i = 0; i < m_numChunks; ++i )
	{
		if ( m_pFramesInRelation[i]->getName() == a_name )
		{
			destroyFrame(m_pFramesInRelation[i]);
		}
	}
}

void ChunkManager::destroyFrame ( Frame * const a_pFrame )
{
	a_pFrame->shutdown();
}

};
};
