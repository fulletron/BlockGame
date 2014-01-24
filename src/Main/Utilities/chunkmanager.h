#ifndef __CHUNKMANAGER_H_
#define __CHUNKMANAGER_H_ 

/** CHUNKMANAGER
 * The chunkmanager allocates a large continuous block of memory
 * at the start of the program, and then divides the large block
 * into smaller equally sized chunks (each chunk is a frame,
 * defined in frame.h). These chunks can be prepared and 
 * destroyed simultaneously. The goal is to completely replace 
 * new, malloc, delete, and free, as well as maximize cache
 * performance.
 */ 

#include "typedefinitions.h"
#include "frame.h"
#include "gsinvestor.h"
#include "chunkptr.h"

namespace GS {
namespace Utilities {

class ChunkManager
{
#ifdef TEST_ENABLED
public:
#else
protected:
#endif
	_UINT32		m_numChunks;
	_UINT32		m_sizeOfChunk;

	_UINT32		m_usedChunks;

	_BYTE * 	m_pChunk;
	Frame ** 	m_pFramesInRelation;

public:	
	ChunkManager(){}
	~ChunkManager(){}
	
	_INT32 init( 
		const _UINT32 a_numChunks = NUMCHUNKS, 
		const _UINT32 a_sizeOfChunk = SIZECHUNK );

	void shutdown();

	Frame * createFrame( const _INT64 a_name );
	Frame * getFrame( const _INT64 a_name );
	bool destroyFrame ( const _INT64 a_name );

	ChunkPtr getNewChunkPtr( ChunkPtr a_cpIn ); // fpermissive if const
	ChunkPtr getFrameChunkPtr( const _INT64 a_name );
	ChunkPtr getFrameChunkPtr( Frame * const a_pFrame );

	ChunkPtr allocate( 
		const _INT64 a_frame, 
		const _INT32 a_sizeInBytes, 
		const GS::Utilities::Frame::PLACE & a_place );

	ChunkPtr allocate( 
		Frame * const a_pFrame, 
		const _INT32 a_sizeInBytes, 
		const GS::Utilities::Frame::PLACE & a_place );

protected:
	void __compress( const _INT64 a_name, const _UINT32 a_slot );
};

};
};

#endif
