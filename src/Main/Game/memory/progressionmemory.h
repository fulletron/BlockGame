#ifndef __PROGRESSIONMEMORY_H_
#define __PROGRESSIONMEMORY_H_

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



// In terms of destiny,
// Character, ship, icon, friends list, roster, clan
// Essentially, everything in the menu
// would be long term memory
// whether or not i've done the daily
// my current selected DESTINATION. !!!!

namespace GS {
namespace Memory {

class ProgressionMemory : public IMemory
{
selective:
	_UINT32 m_character;
	_UINT32 m_sharedStashed;

	// This is destiny based, and will probably not be used.
	_UINT32 m_destination;

	// It is also (greatly) possible that the monsters and area clear 
	// percentages live here. For example, leaving Act1 and going to
	// Act2, but coming back to Act1 in D2. Monsters don't reset.
	// Partial spawn group remnants and positioning is also saved

public:
	/* This destroys any memories */
	virtual void clearMemories();
};

};
};

#endif