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

#define MAX_FSTOPS 4

namespace GS {
namespace Utilities {

class Frame
{
public:
	typedef enum {
	BOT = 0,
	TOP = 1,
	} PLACE;

#ifdef TEST_ENABLED
public:
#else
private:
#endif
	_BYTE * m_pMemBlock;
	_UINT32 m_size;

	_INT64 m_name;
	_BYTE * m_pCurrentLoc[2];

	// actual stacks may be faster
	// but i want to avoid memory
	// allocation for now
	_BYTE * m_pfStop[2][MAX_FSTOPS];

	void __zerofStops(const PLACE & a_place);
public:
	Frame(_BYTE * a_pAddress, const _UINT32 a_size );
	~Frame(){};

	_INT64 getName() const {return m_name;}

	bool setfStop(const PLACE & a_place);
	bool freefStop (const PLACE & a_place);

	_INT32 init( const _INT64 a_name);
	void shutdown();
	_BYTE * allocate( const _INT32 a_sizeInBytes, const PLACE & a_place );
	bool isValid();
};

};
};

#endif
