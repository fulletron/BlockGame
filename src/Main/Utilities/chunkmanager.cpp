#include "chunkmanager.h"

namespace GS {
namespace Utilities {

_INT32 ChunkManager::init( /* const _INT32 a_byteAlignment */ )
{
	m_pChunk = malloc( NUMCHUNKS * SIZECHUNK );
	if ( !m_pChunk )
		return 1;

	for( int i = 0; i < NUMCHUNKS; ++i )
	{
		m_pFramesInRelation[i] = new Frame( (void*) ((_UINT64)m_pChunk + (SIZECHUNK * i)) );
	}

	return 0;
}

void ChunkManager::shutdown()
{
	free( m_pChunk );
	for( int i = 0; i < NUMCHUNKS; ++i )
	{
		delete m_pFramesInRelation[i];
	}
}

Frame * ChunkManager::createFrame(const _INT64 a_name)
{
	//TODO
	// IN DEBUG, CHECK FOR NAME COLLISIONS
	int i;
	for( i = 0; i < NUMCHUNKS; ++i )
	{
		if ( !m_pFramesInRelation[i]->isValid() )
		{
			break;
		}
	}

	// THIS SHOULD BE AN ASSERT
	if( i == NUMCHUNKS )
		return 0;

	if( m_pFramesInRelation[i]->init( a_name ) )
		return 0;

	return m_pFramesInRelation[i]; 
}

Frame * ChunkManager::getFrame( const _INT64 a_name)
{
	for( int i = 0; i < NUMCHUNKS; ++i )
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
	for( int i = 0; i < NUMCHUNKS; ++i )
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
