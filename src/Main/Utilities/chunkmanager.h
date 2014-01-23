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
#include "chunkptr.h"

namespace GS {
namespace Utilities {

class ChunkManager
{
selective:
	_UINT32		m_numChunks;
	_UINT32		m_sizeOfChunk;

	_UINT32		m_usedChunks;

	_BYTE * 	m_pChunk;
	Frame ** 	m_pFramesInRelation;

public:	
	ChunkManager(){}
	~ChunkManager(){}
	
	/**
	* Initializes the Chunk Manager.
	* The function mallocs a block of memory
	* and then uses new to create an array
	* of Frame *.
	*
	* @param const _UINT32 a_numChunks
	*	number of frames to create/manage
	* @param const _UINT32 a_sizeOfChunk
	*	size in bytes of each individual
	*	frame.
	*
	* @return 0 on success, 
	* @return ERROR_NUMBER on failure.
	**/
	_INT32 init( 
		const _UINT32 a_numChunks = NUMCHUNKS, 
		const _UINT32 a_sizeOfChunk = SIZECHUNK );

	/**
	* Destroys the Chunk Manager.
	* Tells every chunk (frame) to shutdown,
	* frees the entire block. then deletes
	* the array of Frame *.
	**/
	void shutdown();

	/**
	* Creates a frame at the next available
	* chunk slot, unless the frame trying to
	* be created already exists.
	*
	* @param const _INT64 a_name
	*	The unique name of the frame.
	*
	* @return Frame *
	*	0 on FAILURE TO CREATE
	*	0 on ALREADY EXISTS
	*	& if SUCCESSFULLY CREATED
	**/
	Frame * createFrame( const _INT64 a_name );

	/**
	* Gets a frame by name that already exists.
	*
	* @param const _INT64 a_name
	*	The unique name of the frame.
	*
	* @return Frame *
	*	0 on FAILURE TO FIND THE FRAME
	*	& if SUCCESSFULLY FOUND
	**/
	Frame * getFrame( const _INT64 a_name );

	/**
	* Destroys a frame by name. After destroying
	* the frame, it takes the furthest frame in the
	* chunk vector and moves it to freshly deleted
	* spot, using __compress
	*
	* @param const _INT64 a_name
	*	The unique name of the frame.
	*
	* @return bool
	*	FALSE if it couldn't find the frame
	*	TRUE if it succeeded
	**/
	bool destroyFrame ( const _INT64 a_name );

	/**
	* Updates an invalid chunk pointer.
	* Whenever a frame is deleted, a new frame slides
	* into it's old spot, invalidating all pointers
	* pointing to those spots. the ChunkPtr class
	* keeps track of when what it's pointing to has
	* been moved, and will correct itself to point
	* at the new correct location.
	*
	* @param ChunkPtr a_cpIn
	*	The pointer that needs to be updated
	*
	* @return ChunkPtr
	*	The new, updated ChunkPtr
	**/
	ChunkPtr getNewChunkPtr( ChunkPtr a_cpIn ); // fpermissive if const
	
	/**
	* Replaces New/Malloc
	* Allocates memory in the chunk manager
	*
	* @param Frame * const a_pFrame
	*	The frame that the memory will be allocated within
	* @param _INT32 a_sizeInBytes
	*	How much memory to allocate in bytes
	* @param GS::Utilities::Frame::PLACE & a_place
	*	Allocate from the TOP or BOT of the frame stack
	*
	* @return ChunkPtr
	*	The ChunkPtr to the newly allocated memory
	**/
	ChunkPtr allocate( 
		Frame * const a_pFrame, 
		const _INT32 a_sizeInBytes, 
		const GS::Utilities::Frame::PLACE & a_place );

	/**
	* Replaces New/Malloc
	* Allocates memory in the chunk manager
	* THIS FUNCTION SIMPLY GETS THE NAME OF THE FRAME
	* AND CALLS THE OTHER ALLOCATE FUNCTION!
	*
	* @param const _INT64 a_frame
	*	The frame name that the memory will be allocated within
	* @param _INT32 a_sizeInBytes
	*	How much memory to allocate in bytes
	* @param GS::Utilities::Frame::PLACE & a_place
	*	Allocate from the TOP or BOT of the frame stack
	*
	* @return ChunkPtr
	*	The ChunkPtr to the newly allocated memory
	**/
	ChunkPtr allocate( 
		const _INT64 a_frame, 
		const _INT32 a_sizeInBytes, 
		const GS::Utilities::Frame::PLACE & a_place );

selective:
	void __compress( const _INT64 a_name, const _UINT32 a_slot );
	//ChunkPtr __getFrameChunkPtr( const _INT64 a_name );
	//ChunkPtr __getFrameChunkPtr( Frame * const a_pFrame );
};

};
};

#endif
