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

namespace GS {
namespace Utilities {

class ChunkManager
{
public:

#ifdef TEST_ENABLED
public:
#else
private:
#endif
	_UINT32		m_numChunks;
	_UINT32		m_sizeOfChunk;
	void * 		m_pChunk;
	Frame ** 	m_pFramesInRelation;
public:	
	ChunkManager(){}
	~ChunkManager(){}
	
	_INT32 init( const _UINT32 a_numChunks = NUMCHUNKS, const _UINT32 a_sizeOfChunk = SIZECHUNK);
	void shutdown();

	Frame * createFrame(const _INT64 a_name);
	Frame * getFrame( const _INT64 a_name);
	void destroyFrame ( const _INT64 a_name);
	void destroyFrame ( Frame * const a_pFrame );

};

};
};

#endif
