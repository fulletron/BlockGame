#include "library.h"

namespace GS {
namespace LibraryNS {

	_UINT32 Library::init(GS::Game * const a_rpGame)
	{
		m_rpGame = a_rpGame;
		return 0;
	}

	void Library::shutdown()
	{
		_GSVECTOR(_UINT64) t_ids;
		m_entries.gatherIds(&t_ids);
		for(int i = 0; i < t_ids.size(); ++i)
		{
			_UINT64 t_key = t_ids.get(i);
			IEntry * t_pResFile = m_entries.get(t_key);
			if(t_pResFile)
			{
				t_pResFile->shutdown();
				delete t_pResFile;
			}
			while(!m_entries.subtract(t_key)){}
		}
	}

	IEntry * Library::getEntry(_UINT64 a_key)
	{
		return m_entries.get(a_key);
	}

	IEntry * Library::addEntry(_UINT64 a_key, IEntry * entryToAdd)
	{
		if(entryToAdd && !m_entries.add(a_key, entryToAdd))
		{
			entryToAdd->shutdown();
			delete entryToAdd;
			return 0;
		}
		return entryToAdd;
	}

	void Library::remEntry(_UINT64 a_key)
	{
		IEntry * t_pEntry = m_entries.get(a_key);
		if(t_pEntry)
		{
			t_pEntry->shutdown();
			delete t_pEntry;
		}

		m_entries.subtract(a_key);
	}
	
	/*
	template< class T >
	_UINT32 Library::loadResource(_UINT32 a_key, T * a_newResourceFile, ResourceBuilder * a_rb, void * a_extraInfo)
	{
		/// KYLE:: CHECK FOR CURRENT EXISTANCE OF KEY!
		a_newResourceFile = new T(a_rb,a_extraInfo);
		return addEntry(a_key, a_newResourceFile);
	}
	*/

	_UINT32 __initAlwaysAvailableResources()
	{
		/// KYLE:: LOADING RESOURCES GO HERE, AND NEVER COME OUT!
		return 0;
	}

};
};