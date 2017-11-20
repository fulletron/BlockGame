#include "allocator.h"

#include "buffer.h"

namespace GS {
namespace Server {

Allocator::Allocator(
	size_t bufferSize,
	size_t maxFreeBuffers)
	: m_bufferSize(bufferSize),
	m_maxFreeBuffers(maxFreeBuffers)
{
}

/*
// THIS IS A BAD CONSTRUCTOR AND WE DONT WANT IT
Allocator::Allocator()
{
	m_bufferSize = 0;
	m_maxFreeBuffers = 0;
	DEBUG_OUT_RED("BAD CONSTRUCTOR.");
}
*/

Allocator::~Allocator()
{
	allocatorFlush();
}

Buffer * Allocator::allocate()
{
	std::lock_guard<std::mutex> lock(m_critLock);

	Buffer * pBuffer = 0;

	if (!m_freeList.empty())
	{
		pBuffer = m_freeList.popNode();
		pBuffer->addRef();
	}
	else
	{
		pBuffer = new(m_bufferSize)Buffer(*this, m_bufferSize);

		if (!pBuffer)
		{
			DEBUG_OUT("ERROR: allocate. out of memory.");
		}

		onBufferCreated();
	}

	m_activeList.pushNode(pBuffer);

	onBufferAllocated();

	return pBuffer;
}

void Allocator::__release(Buffer * pBuffer)
{
	std::lock_guard<std::mutex> lock(m_critLock);

	if (!pBuffer)
	{
		DEBUG_OUT("pBuffer is null.");
	}

	onBufferReleased();

	pBuffer->removeFromList();

	if (m_maxFreeBuffers == 0
		|| m_freeList.count() < m_maxFreeBuffers)
	{
		pBuffer->empty();

		m_freeList.pushNode(pBuffer);
	}
	else
	{
		__destroyBuffer(pBuffer);
	}
}

void Allocator::allocatorFlush()
{
	std::lock_guard<std::mutex> lock(m_critLock);

	while (!m_activeList.empty())
	{
		//lint -e{1933} call to unqualified virtual function
		onBufferReleased();

		__destroyBuffer(m_activeList.popNode());
	}

	while (!m_freeList.empty())
	{
		__destroyBuffer(m_freeList.popNode());
	}
}

void Allocator::__destroyBuffer(Buffer * pBuffer)
{
	delete pBuffer;

	onBufferDestroyed();
}

};
};