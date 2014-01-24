#include "chunkmanager.h"
#include <Utilities/chunkptr.h>
#include <cstring>

namespace GS {
namespace Utilities {

_INT32 ChunkManager::init( const _UINT32 a_numChunks, const _UINT32 a_sizeOfChunk )
{
	m_numChunks = a_numChunks;
	m_sizeOfChunk = a_sizeOfChunk;
	m_usedChunks = 0;

	m_pChunk = reinterpret_cast<_BYTE*>( malloc( m_numChunks * m_sizeOfChunk ) );
	m_pChunk = INALIGNDOWN(m_pChunk, 8);
	if ( !m_pChunk )
		return 1;

	m_pFramesInRelation = new Frame*[m_numChunks];

	for( _UINT32 i = 0; i < m_numChunks; ++i )
	{
		m_pFramesInRelation[i] = new Frame( (m_pChunk + (m_sizeOfChunk * i)), m_sizeOfChunk );
	}

	return 0;
}

void ChunkManager::shutdown()
{
	for( _UINT32 i = 0; i < m_numChunks; ++i )
	{
		Frame * pFrame = m_pFramesInRelation[i];
		//if( pFrame->isValid() )
		pFrame->shutdown();
		delete pFrame;
	}
	free( m_pChunk );
}

Frame * ChunkManager::createFrame(const _INT64 a_name)
{
	for( _UINT32 i = 0; i < m_usedChunks; ++i )
	{
		if ( m_pFramesInRelation[i]->getName() == a_name )
		{
			return 0;
		}
	}

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
			if( m_usedChunks > 1 )
			{
				__compress(a_name, i);
			}
			m_pFramesInRelation[m_usedChunks-1]->shutdown();
			m_usedChunks--;
			return true;
		}
	}
	return false;
}

ChunkPtr ChunkManager::getNewChunkPtr( ChunkPtr a_cpIn )
{
	// set base values, and one new value.
	ChunkPtr newChunkPtr(a_cpIn.getpData(), a_cpIn.getOwnerFrame(), a_cpIn.getOwnerName());
	Frame * pFrame = getFrame(a_cpIn.getOwnerName());

	newChunkPtr.setpOwnerFrame (pFrame);

	if(!pFrame)
	{
		newChunkPtr.clean();
		return newChunkPtr;
	}

	_BYTE * pFrom = RC( _BYTE *, a_cpIn.getOwnerFrame()->getMemBlock() );
	_BYTE * pTo = RC( _BYTE *, newChunkPtr.getOwnerFrame()->getMemBlock() );

	_INT64 diff = pFrom - pTo;

	// set new value for data
	newChunkPtr.setpData( RC( _BYTE *, RC( _UINT64, a_cpIn.getpData() ) - diff ) );

	// return new value
	return newChunkPtr;
}

ChunkPtr ChunkManager::allocate( const _INT64 a_frame, const _INT32 a_sizeInBytes, const GS::Utilities::Frame::PLACE & a_place )
{
	Frame * pFrame = getFrame( a_frame );
	if( !pFrame )
		pFrame = createFrame( a_frame );

	return ChunkPtr(pFrame->allocate(a_sizeInBytes, a_place), pFrame, a_frame);
}


ChunkPtr ChunkManager::allocate( Frame * const a_pFrame, const _INT32 a_sizeInBytes, const GS::Utilities::Frame::PLACE & a_place )
{
	if( !a_pFrame )
		return ChunkPtr(0,0,0);

	return ChunkPtr(a_pFrame->allocate(a_sizeInBytes, a_place), a_pFrame, a_pFrame->getName());
}

ChunkPtr ChunkManager::getFrameChunkPtr( const _INT64 a_name )
{
	Frame * pFrame = getFrame( a_name );
	if ( pFrame )
		return getFrameChunkPtr( pFrame );

	return ChunkPtr(0,0,0);
}

ChunkPtr ChunkManager::getFrameChunkPtr( Frame * const a_pFrame )
{
	return ChunkPtr( RC(_BYTE*, a_pFrame), a_pFrame, a_pFrame->getName() );
}

void ChunkManager::__compress( const _INT64 a_name, const _UINT32 a_slot )
{
	m_pFramesInRelation[a_slot]->copyFrame(m_pFramesInRelation[m_usedChunks-1]);
}

};
};
