#ifndef __INSTANCEMEMORY_H_
#define __INSTANCEMEMORY_H_

#include <Framework/memory/imemory.h>

#include <Utilities\definitions_types.h>

// LONG TERM MEMORY
// Things that persist once throughout the "Play" state has begun
// My inventory
// My Character
// My Progression
// The server might not ever care about this stuff, but in the event
// of ever possibly having "Inspect", keep it an option.
// HGL: possibly inspect
// 40k: inspect at the battlenet menu level, like a win/loss ratio, stats
// CTF: I can't think of a reason for this one.
// WHEN THEN???: Most specifically, the server will care when dedicated serverness is a thing.
// If like a pubg, mostly everything would be short term

// SHORT TERM MEMORY
// Things that die everytime a new area is loaded
// Monsters
// NPC's
// Other Players
// The server will always care about this stuff
// HGL: Most combat elements
// 40k: The map seed, cover, where units/models are
// CTF: Once again, tough


// The server will need a long term memory that holds information regarding all of the players.

// The server will have a short term memory, run probably with its' own thread, per instance.

// The client will need a long term memory of 
// My inventory
// My Character
// My Progression

// The client will need a short term memory of the current instance

namespace GS {
namespace Memory {

class InstanceMemory : public IMemory
{
protected:
	_UINT32 m_world;
	// m_world is a mix of
	//_UINT32 m_seed;
	//_VECTOR<_UINT32> m_setPieces;
	//_VECTOR<_UINT32> m_placables;
	//_VECTOR<_UINT32> m_foliage;
	//_VECTOR<_UINT32> m_weather;

	_UINT32 m_entities;
	// m_entities are things like:
	//_VECTOR<_UINT32> m_pcs;
	//_VECTOR<_UINT32> m_npcs;
	//_VECTOR<_UINT32> m_primitives;
	//_VECTOR<_UINT32> m_decals;

public:
	/* This destroys any memories */
	virtual void clearMemories();
};

};
};

#endif