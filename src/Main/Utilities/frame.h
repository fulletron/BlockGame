#ifndef __FRAME_H_
#define __FRAME_H_

/** FRAME
 * The Frame is a double sided stack that can be allocated to. In
 * addition, the frame can set an "fStop" at any point during its
 * continuously growing allocation, and then revert back to that
 * "fStop", thus allowing previously allocated memory to be
 * overwritten. This is for speed!
 */

#include "typedefinitions.h"

static const int MAX_FSTOPS = 4;

namespace GS {
namespace Utilities {

class Frame
{
public:
	typedef enum {
	BOT = 0,
	TOP = 1,
	} PLACE;

selective:
	_BYTE * m_pMemBlock;
	_BYTE * m_pCurrentLoc[2];

	// actual stacks may be faster
	// but i want to avoid memory
	// allocation for now
	_BYTE * m_pfStop[2][MAX_FSTOPS];

	_INT64 m_name;
	_UINT32 m_size;

public:
	/**
	* Constructor requires a starting address and a size
	* Every frame requires this information, and this information never 
	* changes throughout the duration of the program.
	*
	* @param _BYTE * a_pAddress
	*	The starting address of the frame
	* @param _UINT32 a_size
	*	The size of the frame
	**/
	Frame(_BYTE * a_pAddress, const _UINT32 a_size );
	~Frame(){};

	/**
	* Initializes the Frame
	* At this point we already have the starting address as well as the
	* size. This frame correctly sets where the current allocation
	* pointers are, as well as the name of the frame.
	* of Frame *.
	*
	* @param const _UINT64 a_name
	*	The name of the frame
	*
	* @return 0 on success, 
	* @return ERROR_NUMBER on failure.
	**/
	_INT32 init( const _INT64 a_name);

	/**
	* Allocates to the frame
	* Using the corresponding m_pCurrentLoc, the frame reserves a
	* portion of its memory block for the memory needed by the caller. 
	* Normally, a _TChunkPtr<> is returned.
	*
	* @param const _INT64 a_sizeInBytes
	*	How much memory to allocate
	* @param const PLACE & a_place
	*	Alocate from the TOP or BOT of the frame?
	*
	* @return & on success, 
	* @return 0 on failure.
	**/
	_BYTE * allocate( const _INT32 a_sizeInBytes, const PLACE & a_place );

	/**
	* Sets an fStop
	* An fStop is a "Frame Stop", or a marked location in the memory
	* within the frame's block, that can be erased back to.
	*
	* @param const PLACE & a_place
	*	The TOP or BOT of the frame to place an fStop
	*
	* @return TRUE on success, 
	* @return FALSE when there are already the maximum number of fStops.
	**/
	bool setfStop(const PLACE & a_place);

	/**
	* Frees an fStop
	* Resets the m_pCurrentLoc pointer back to the last marked location. 
	* Any subsequent allocations will overwrite old values.
	*
	* @param const PLACE & a_place
	*	The TOP or BOT of the frame to place an fStop
	*
	* @return & on success, 
	* @return 0 on failure.
	**/
	_BYTE * freefStop (const PLACE & a_place);

	/* Sets the frame data and the frame's chunk's data to zero */
	void shutdown();

	/* Returns the name of this frame */
	_INT64 getName() const {return m_name;}

	/* Returns a pointer to the beginning of this frame */
	_BYTE* const getMemBlock() const { return m_pMemBlock; }

	/**
	* Copies another frame's data and block data.
	* KYLE :: TODO ::
	* MADE THE CHUNK MANAGER A FRIEND OR SOMETHING,
	* BECAUSE THIS FUNCTION IS ONLY USED BY THE CHUNK MANAGER,
	* AND IS DANGEROUS TO USE OUTSIDE OF THAT ONE INSTANCE.
	* PERHAPS UNDO!
	* FUNCTION IS DEFINED LIKE A PRIVATE FOR WARNING
	*
	* @param Frame * const a_pFromFrame
	*	The frame being copied FROM
	**/
	void __copyFrame( Frame * const a_pFromFrame );

selective:
	void __offsetfStops(const _INT64 a_offset);
	bool __isValid();
	void __zerofStops(const PLACE & a_place);
	void __copyfStops( Frame * a_pFromFrame );
};

};
};

static const GS::Utilities::Frame::PLACE BOT = GS::Utilities::Frame::PLACE::BOT;
static const GS::Utilities::Frame::PLACE TOP = GS::Utilities::Frame::PLACE::TOP;

#endif
