#ifndef __DIRECTORSTATE_H_
#define __DIRECTORSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../characterchosenstate.h"
#include "menu.h"

namespace GS {
namespace State {

class DirectorState : public IState<CharacterChosenState>, IStateMachine<DirectorState>
{
// move to an IMPLEMENT define?
selective:
	Menu * m_pCurrentMenu;
public:
	_BOOL menuIsOpen() { 
		if (m_pCurrentMenu) 
			return true; 
		return false; 
	}

	void menuOpen() 
	{
		if (!m_pCurrentMenu)
		{
			m_pCurrentMenu = new Menu();
			m_pCurrentMenu->onEnter(0);
		}
	}

	void menuClose() 
	{
		if (m_pCurrentMenu)
		{
			m_pCurrentMenu->onExit(0);
			delete m_pCurrentMenu;
			m_pCurrentMenu = 0;
		}
	}

selective:
	_UINT64 m_selectedMission;
public:
	_UINT64 getSelectedMission(){ return m_selectedMission; }
	void setSelectedMission(const _UINT64 & a_id){ m_selectedMission = a_id; }

	IMPLEMENT_ISTATE(CharacterChosenState);
	IMPLEMENT_ISTATEMACHINE(DirectorState);
};

};
};

#endif