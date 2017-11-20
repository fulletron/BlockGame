#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#include "../../definitions_types.h"
#include <mutex>
#include "nodelist.h"

namespace GS {
namespace Server {

class Buffer;


class Allocator
{
public:
	friend class Buffer;

	explicit Allocator(size_t bufferSize, size_t maxFreeBuffers);

	/*
	* only exists because i can't get it to build otherwise.
	* KYLE :: TODO
	*/
	//Allocator();

	virtual ~Allocator();

	/*
	* Creates a buffer from the free list,
	* or, if there are no free buffers,
	* creates a new one.
	*/
	Buffer * allocate();

	size_t getBufferSize() const;

selective:
	/*
	* Empties the entire buffer list.
	*/
	void allocatorFlush();


selective:
	// these are supposed to be CONST
	size_t m_bufferSize;
	size_t m_maxFreeBuffers;
	//const size_t m_bufferSize;
	//const size_t m_maxFreeBuffers;

	/*
	* Destroys a specific buffer.
	*/
	void __destroyBuffer(Buffer * pBuffer);

privatized:
	/*
	* deletes a buffer, but stores its husk
	* in the free list.
	*/
	void __release(Buffer * pBuffer);

	virtual void onBufferCreated() {}
	virtual void onBufferAllocated() {}
	virtual void onBufferReleased() {}
	virtual void onBufferDestroyed() {}

	typedef TNodeList<Buffer> BufferList;

	BufferList m_freeList;
	BufferList m_activeList;

	std::mutex m_critLock;

	// No copies do not implement
	Allocator(const Allocator &rhs);
	Allocator &operator=(const Allocator &rhs);
};

};
};

#endif