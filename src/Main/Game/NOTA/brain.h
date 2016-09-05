#ifndef __BRAIN_H_
#define __BRAIN_H_

#include <Utilities/typedefinitions.h>
#include <Game/fpscounter.h>

namespace GS { 

namespace Game {

class Brain
{
selective:
	Brain(Brain const&);              // Don't Implement
	void operator=(Brain const&); // Don't implement

	FPSCounter m_fpsCounter;

public:
	Brain(){}
	~Brain(){}
	/**
	* Tells the game to clean up
	*/ 
	void shutdown();

	/**
	* Determines how to handle input for the PaneAsset
	*/
	//_BOOL handleInput();

	/**
	* Updates all game logic by a_dt
	*/
	void update(const _DOUBLE a_dt);

	/**
	* Init the brain
	*/
	_INT32 init ();

	/**
	* TEMPORARY SINGLETON USE FOR CRAPPY BUT EASILY UNDERSTOOD
	* METHOD OF GETTING BRAIN STUFF FOR THE PANELS
	*/
    static Brain& getInstance()
    {
        static Brain    instance; // Guaranteed to be destroyed.
                                // Instantiated on first use.
        return instance;
    }

public:
	FPSCounter * const getFpsCounter() { return &m_fpsCounter; }
};

}
};

#endif
