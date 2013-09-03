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

#define ALIGNUP( nAddress, nBytes ) ( (((_UINT32)nAddress) + (nBytes)-1) & (~((nBytes)-1)) )

namespace GS {
namespace Utilities {

class ChunkManager
{
public:
private:
	void * 		m_pChunk;
	Frame * 	m_pFramesInRelation[NUMCHUNKS];
public:	
	ChunkManager(){}
	~ChunkManager(){}
	
	_INT32 init();
	void shutdown();

	Frame * createFrame(const _INT64 a_name);
	Frame * getFrame( const _INT64 a_name);
	void destroyFrame ( const _INT64 a_name);
	void destroyFrame ( Frame * const a_pFrame );
};

};
};

#endif
