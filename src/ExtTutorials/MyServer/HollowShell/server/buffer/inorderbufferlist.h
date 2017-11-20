#ifndef __INORDERBUFFERLIST_H__
#define __INORDERBUFFERLIST_H__

#include "../../definitions_types.h"
#include <mutex>
#include <map>

namespace GS {
namespace Server {

class Buffer;

class InOrderBufferList
{
public:
	/*
	* The passed in mutex becomes the one owned by the class.
	*/
	explicit InOrderBufferList(std::mutex &);

	/*
	* Adds a specific buffer to the InOrderBufferList
	*/
	void addBuffer(Buffer *);

	/*
	* Increments m_next;
	*/
	void processBuffer();

	/*
	* Pulls a buffer out of the buffer list. Increments m_next;
	*/
	Buffer * processAndGetNext();

	/*
	* Pulls a buffer out of the buffer list. Does not increment m_next;
	*/
	Buffer * getNext();

	/*
	*
	*/
	Buffer * getNext(Buffer * pBuffer);

	/*
	* set m_next to 0
	*/
	void reset();

	bool empty() const;


selective:
	size_t m_next;

	typedef std::map<size_t, Buffer *> BufferSequence;

	BufferSequence m_list;

	std::mutex & m_critLock;

};

};
};

#endif