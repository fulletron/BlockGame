#ifndef __MENU_H_
#define __MENU_H_

#include <Utilities/typedefinitions.h>
#include "../characterchosenstate.h"

namespace GS {
namespace State {

// NOTE :: The menu state should not live from CharacterChosenState to CharacterChosenState- meaning, it should die 
// when switching from director to flyload and from flyload to play, etc.S

// The Menu class should NOT have to know anything about any state it is being called from. If the menu is closed
// via the menu button, then it is force-quitted from the state that instatiated it. If the menu is dismissed,
// it can be cleaned up at a later point? Cleanup, as in, when "dismiss" is issued, convert it to a menu button press
// which will be caught by the current state to force-quit (hack).
class Menu : public IStateMachine<Menu>
{
	// Implementing these function because I happen to use them, not because I need them.
	//IMPLEMENT_ISTATE(CharacterChosenState);
selective:
	IMenuable * m_pOwner;

public:									
	_INT32 onEnter();
	_INT32 onUpdate();
	_INT32 onExit();

	IMPLEMENT_ISTATEMACHINE(Menu);
};


// move this to its own file.
class IMenuable
{
public:
	virtual _BOOL menuIsOpen() = 0;
	virtual void menuOpen() = 0;
	virtual void menuClose() = 0;
};

};
};

#define IMPLEMENT_IMENUABLE					\
selective:									\
Menu * m_pCurrentMenu;						\
public:										\
	_BOOL menuIsOpen() {					\
		if (m_pCurrentMenu)					\
			return true;					\
		return false;						\
	}										\
	void menuOpen()							\
	{										\
		if (!m_pCurrentMenu)				\
		{									\
			m_pCurrentMenu = new Menu();	\
			m_pCurrentMenu->onEnter();		\
		}									\
	}										\
	void menuClose()						\
	{										\
		if (m_pCurrentMenu)					\
		{									\
			m_pCurrentMenu->onExit();		\
			delete m_pCurrentMenu;			\
			m_pCurrentMenu = 0;				\
		}									\
	}

#endif