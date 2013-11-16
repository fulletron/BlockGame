#ifndef __LIBRARY_H_
#define __LIBRARY_H_

#include <Game\definitions.h>

namespace GS { class Game;
namespace LibraryNS {

	class IEntry 
	{
		public:
			virtual void shutdown() = 0;
	};

	typedef IEntry*(*EntryInitFunction)(GS::Game *);

	class Library 
	{
		public:
			typedef _GSREFMAP(_UINT64, IEntry *) EntryRefMap;

		private:
			GS::Game *				m_rpGame;
			EntryRefMap				m_entries;

		public:

			Library()
				: m_rpGame(0)
			{}
			~Library(){}

			_UINT32 init(GS::Game * const a_rpGame);
			void shutdown();

			IEntry *	getEntry(_UINT64 a_key);
			IEntry *	addEntry(_UINT64 a_key, IEntry * entryToAdd);
			void		remEntry(_UINT64 a_key);
	};
};
};

#endif