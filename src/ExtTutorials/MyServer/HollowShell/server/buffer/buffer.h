#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "../../definitions_types.h"
#include <mutex>
#include "nodelist.h"
#include "opaqueuserdata.h"

namespace GS {
namespace Server {

class Allocator;
class InOrderBufferList;

/*
*
*/
class Buffer : public OVERLAPPED, public Node, public OpaqueUserData
{
public:
	friend class Allocator;

	/*
	* returns the m_wsabuf
	*/
	WSABUF *getWSABUF() const;

	/*
	* returns m_used
	*/
	size_t getUsed() const;

	/*
	* returns m_size
	*/
	size_t getSize() const;

	/*
	* returns the address of the actual data
	* that exists at the end of the buffer class
	* ( where the data lives )
	*/
	const BYTE *getBuffer() const;

	/*
	* adjusts where m_wsabuf.buf is pointing, and
	* m_wsabuf.len size for ZERO.
	*/
	void setupZeroByteRead();

	/*
	* adjusts where m_wsabuf.buf is pointing, and
	* m_wsabuf.len size for whatever m_used is.
	*/
	void setupRead();

	/*
	* adjusts where m_wsabuf.buf is pointing, and
	* m_wsabuf.len size for m_used, then sets m_used to 0.
	*/
	void setupWrite();

	/*
	* Adds data to the current end (m_used) of the buffer.
	*/
	void addData(
		const char * const pData,
		size_t dataLength);

	/*
	* Adds data to the current end (m_used) of the buffer.
	*/
	void addData(
		const BYTE * const pData,
		size_t dataLength);

	/*
	* adds one byte of data to the end of the buffer.
	*/
	void addData(BYTE data);

	/*
	* adds dataUsed to the m_used;
	*/
	void use(
		size_t dataUsed);

	/*
	* This splits the buffer at the bytesToRemove mark,
	* and returns the first portion.
	*/
	Buffer * splitBuffer(
		size_t bytesToRemove);

	/*
	* returns m_allocator.allocate();
	*/
	Buffer * allocateNewBuffer() const;

	/*
	* splits the buffer without saving the second portion.
	*/
	void consumeAndRemove(
		size_t bytesToRemove);

	/*
	* sets m_used to 0, and sets the m_wsabuf buf and len to the buffer data at the end.
	* other than used 0, i don't understand how this empties.
	*/
	void empty();


	void addRef();
	/*
	* get rid of the data in this buffer.
	*/
	void release();

	size_t getOperation() const;
	void setOperation(size_t op);

	size_t getSequenceNumber() const;
	void setSequenceNumber(
		size_t sequenceNumber);

selective:
	size_t m_operation;
	size_t m_sequenceNumber;

	WSABUF m_wsabuf;

	Allocator & m_allocator;

	long m_ref;
	const size_t m_size;
	size_t m_used;

privatized:
	/*
	* returns a new void * char array of size objSize+bufferSize
	*/
	static void *operator new(size_t objSize, size_t bufferSize);

	/*
	* deletes the [] object
	*/
	static void operator delete(void *pObj, size_t bufferSize);

	Buffer(
		Allocator &m_allocator,
		size_t size);

	// No copies do not implement
	Buffer(const Buffer &rhs);
	Buffer &operator=(const Buffer &rhs);

selective:
	BYTE m_buffer[0]; // start of the actual buffer, must be last
};

};
};

#endif