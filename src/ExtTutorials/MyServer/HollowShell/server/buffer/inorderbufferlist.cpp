#include "inorderbufferlist.h"

#include "buffer.h"

namespace GS {
namespace Server {

InOrderBufferList::InOrderBufferList(std::mutex & a_lock)
	: m_next(0),
	m_critLock(a_lock)
{
}

void InOrderBufferList::addBuffer(Buffer * pBuffer)
{
	std::lock_guard<std::mutex> lock(m_critLock);

	std::pair<BufferSequence::iterator, bool> result = m_list.insert(BufferSequence::value_type(pBuffer->getSequenceNumber(), pBuffer));

	if (!result.second)
	{
		DEBUG_OUT("UNEXPECTED, element already in map!");
	}
}

Buffer * InOrderBufferList::processAndGetNext()
{
	std::lock_guard<std::mutex> lock(m_critLock);

	m_next++;

	Buffer * pNext = 0;

	BufferSequence::iterator it;

	it = m_list.begin();

	if (it != m_list.end())
	{
		if (it->first == m_next)
		{
			pNext = it->second;

			m_list.erase(it);
		}
		else
		{
			//DEBUG_ONLY(Output(ToString(this) + _T(" PAGN Got buffer  : ") + ToString(it->first) + _T("Want buffer : ") + ToString(m_next)));
			DEBUG_OUT("ERROR? in processAndGetNext");
		}
	}

	return pNext;
}

Buffer * InOrderBufferList::getNext()
{
	std::lock_guard<std::mutex> lock(m_critLock);

	Buffer * pNext = 0;

	BufferSequence::iterator it;

	it = m_list.begin();

	if (it != m_list.end())
	{
		if (it->first == m_next)
		{
			pNext = it->second;

			m_list.erase(it);
		}
		else
		{
			DEBUG_OUT("ERROR. getNext() failed. ");
		}
	}

	return pNext;
};

Buffer * InOrderBufferList::getNext(Buffer * pBuffer)
{
	std::lock_guard<std::mutex> lock(m_critLock);

	if (m_next == pBuffer->getSequenceNumber())
	{
		return pBuffer;
	}

	std::pair<BufferSequence::iterator, bool> result = m_list.insert(BufferSequence::value_type(pBuffer->getSequenceNumber(), pBuffer));

	if (!result.second)
	{
		DEBUG_OUT("ERROR in getNext(). element already in map");
	}

	Buffer * pNext = 0;

	BufferSequence::iterator it;

	it = m_list.begin();

	if (it != m_list.end())
	{
		if (it->first == m_next)
		{
			pNext = it->second;

			m_list.erase(it);
		}
		else
		{
			DEBUG_OUT("ERROR? in getNext(). wrong buffer.");
		}
	}

	return pNext;
}

void InOrderBufferList::processBuffer()
{
	std::lock_guard<std::mutex> lock(m_critLock);

	m_next++;
}

void InOrderBufferList::reset()
{
	m_next = 0;

	if (!m_list.empty())
	{
		DEBUG_OUT("LIST WAS NOT EMPTY UPON RESET");
	}
}


};
};