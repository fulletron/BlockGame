#include "buffer.h"

#include "allocator.h"

namespace GS {
namespace Server {

//////////////////////////////////////////////////////////////////////////////////////////////////
// BUFFER
//////////////////////////////////////////////////////////////////////////////////////////////////

Buffer::Buffer(
	Allocator &allocator,
	size_t size)
	: m_operation(0),
	m_sequenceNumber(0),
	m_allocator(allocator),
	m_ref(1),
	m_size(size),
	m_used(0)
{
	memset(this, 0, sizeof(OVERLAPPED));
	empty();
}

WSABUF * Buffer::getWSABUF() const
{
	return const_cast<WSABUF*>(&m_wsabuf);
}

size_t Buffer::getUsed() const
{
	return m_used;
}

size_t Buffer::getSize() const
{
	return m_size;
}

const BYTE * Buffer::getBuffer() const
{
	return &m_buffer[0];
}

void Buffer::empty()
{
	m_wsabuf.buf = reinterpret_cast<char *>(m_buffer);
	m_wsabuf.len = m_size;

	m_used = 0;
}

void * Buffer::operator new(size_t objectSize, size_t bufferSize)
{
	void * pMem = new char[objectSize + bufferSize];
	return pMem;
}

void Buffer::operator delete(void * pObject, size_t /* bufferSize */)
{
	delete[] pObject;
}

void Buffer::use(size_t dataUsed)
{
	m_used += dataUsed;
}

Buffer * Buffer::splitBuffer(size_t bytesToRemove)
{
	Buffer * pNewBuffer = m_allocator.allocate();

	pNewBuffer->addData(m_buffer, bytesToRemove);

	m_used -= bytesToRemove;

	memmove(m_buffer, m_buffer + bytesToRemove, m_used);

	return pNewBuffer;
}

Buffer * Buffer::allocateNewBuffer() const
{
	return m_allocator.allocate();
}

void Buffer::consumeAndRemove(size_t bytesToRemove)
{
	m_used -= bytesToRemove;
	memmove(m_buffer, m_buffer + bytesToRemove, m_used);
}

void Buffer::setupZeroByteRead()
{
	m_wsabuf.buf = reinterpret_cast<char*>(m_buffer);
	m_wsabuf.len = 0;
}

void Buffer::setupRead()
{
	if (m_used == 0)
	{
		m_wsabuf.buf = reinterpret_cast<char*>(m_buffer);
		m_wsabuf.len = m_size;
	}
	else
	{
		m_wsabuf.buf = reinterpret_cast<char*>(m_buffer)+m_used;
		m_wsabuf.len = m_size - m_used;
	}
}

void Buffer::setupWrite()
{
	m_wsabuf.buf = reinterpret_cast<char*>(m_buffer);
	m_wsabuf.len = m_used;

	m_used = 0;
}

void Buffer::addData(
	const char * const pData,
	size_t dataLength)
{
	if (dataLength > m_size - m_used)
	{
		DEBUG_OUT("Not enough space in buffer.");
	}

	memcpy(m_buffer + m_used, pData, dataLength);

	m_used += dataLength;
}

void Buffer::addData(
	const BYTE * const pData,
	size_t dataLength)
{
	addData(reinterpret_cast<const char *>(pData), dataLength);
}

void Buffer::addData(
	BYTE data)
{
	addData(&data, 1);
}

void Buffer::addRef()
{
	::InterlockedIncrement(&m_ref);
}

void Buffer::release()
{
	if (m_ref == 0)
	{
		// Error! double release
		DEBUG_OUT("m_ref is already 0");
	}

	if (0 == ::InterlockedDecrement(&m_ref))
	{
		m_sequenceNumber = 0;
		m_operation = 0;
		m_used = 0;

		m_allocator.__release(this);
	}
}

size_t Buffer::getOperation() const
{
	return m_operation;
}

void Buffer::setOperation(size_t operation)
{
	m_operation = operation;
}

size_t Buffer::getSequenceNumber() const
{
	return m_sequenceNumber;
}

void Buffer::setSequenceNumber(size_t sequenceNumber)
{
	m_sequenceNumber = sequenceNumber;
}


};
};