#ifndef __EVENTBUFFER_H_
#define __EVENTBUFFER_H_

#include <Game\definitions.h>

namespace GS { class Game;
namespace EventNS {

	typedef void(*EventFunction)(GS::Game*const, void*, void*);

	class EventDictionaryEntry
	{
	public:
		_USHORT				m_eventIndexID;
		_UINT32				m_sizeOfEventData;
		EventFunction		m_eventFunc;

		EventDictionaryEntry(){}
		EventDictionaryEntry(_USHORT a_index, _UINT32 a_size, EventFunction a_func){m_eventIndexID = a_index; m_sizeOfEventData = a_size; m_eventFunc = a_func;}
	};

	class EventDictionary
	{
	public:
	protected:
		GS::Game *									m_rpGame;
		EventDictionaryEntry						m_events[SIZEOFEVENTS];

	public:
		EventDictionary();
		~EventDictionary();
		_UINT32 init(GS::Game * const m_rpGame);
		void addEntry(EventDictionaryEntry a_newEntry);
		EventDictionaryEntry* getEntryByIndex(const _USHORT & a_index);
		EventDictionaryEntry* getEntryByFunction(const EventFunction & a_eventFunc);

		/// COMMAND CODES START AT 0000001 AND INCREMENT, AND THUS CAN BE ORGANIZED AS SUCH
	};

	class EventBuffer 
	{
	public:
	protected:
		GS::Game *		m_rpGame;

		_UINT32			m_size;
		_UINT32			m_startReader;
		_UINT32			m_endWriter;
		_CHAR*			m_elements;
	public:
		_UINT32 init(GS::Game * const m_rpGame, const _UINT32 & a_size);
		void shutdown();

		void writebytes(_CHAR* const a_elements, const _UINT32 & numBytes);
		void* readbytes(const _UINT32 & numBytes);

		bool isFull(){bool ret = false; (m_endWriter + 1) % m_size == m_startReader? ret = true: ret = false; return ret;}
		bool isEmpty(){bool ret = false; (m_endWriter==m_startReader)? ret = true: ret = false; return ret;}
	};

};
};

#endif
