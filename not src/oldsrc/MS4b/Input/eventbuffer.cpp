#include "eventbuffer.h"
#include <Game\game.h>

namespace GS {
namespace EventNS {


	EventDictionary::EventDictionary()
	{
		for(int i = 0; i < SIZEOFEVENTS; ++i)
			m_events[i] = EventDictionaryEntry(0,0,0);
		//this->m_events.ensureCapacity(65536); // 65,536 is UNSIGNED SHORT!
	}

	EventDictionary::~EventDictionary()
	{
	}

	_UINT32 EventDictionary::init(GS::Game * const a_rpGame)
	{
		m_rpGame = a_rpGame;
		return 0;
	}

	void EventDictionary::addEntry(EventDictionaryEntry a_newEntry)
	{
		if(m_events[a_newEntry.m_eventIndexID].m_sizeOfEventData == 0)
			m_events[a_newEntry.m_eventIndexID] = a_newEntry;
		else
		{
			/// THIS CASE SHOULD NEVER BE HIT
		}
	}

	EventDictionaryEntry* EventDictionary::getEntryByIndex(const _USHORT & a_index)
	{
		return &m_events[a_index];
	}

	EventDictionaryEntry* EventDictionary::getEntryByFunction(const EventFunction & a_eventFunc)
	{
		for(int i = 0; i < SIZEOFEVENTS; ++i)
			if(m_events[i].m_eventFunc == a_eventFunc)
				return &m_events[i];

		return 0;
	}

	_UINT32 EventBuffer::init(GS::Game * const a_rpGame, const _UINT32 & a_size)
	{
		m_rpGame = a_rpGame;
		m_size = a_size;
		m_startReader = 0;
		m_endWriter = 0;
		m_elements = new char[a_size];
		return 0;
	}

	void EventBuffer::shutdown()
	{
		delete [] m_elements;
	}

	void* EventBuffer::readbytes(const _UINT32 & a_numBytes)
	{
		if(isEmpty())
			return 0;

		void* returnable = &m_elements[m_startReader];

		for(int i = 0; i < (int)a_numBytes; ++i)
		{
			m_startReader = ((m_startReader++) % m_size);
			if(m_startReader == m_endWriter)
				return 0;
		}
		return returnable;
	}

	void EventBuffer::writebytes(_CHAR* const a_elements, const _UINT32 & a_numBytes)
	{
		for(int i = 0; i < (int)a_numBytes; ++i)
		{
			if(isFull())
				return;

			m_elements[m_endWriter] = a_elements[i];
			m_endWriter = ((m_endWriter++) % m_size);
		}
	}
};
};