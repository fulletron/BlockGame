#ifndef __DIRECTORSTATE_H_
#define __DIRECTORSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../characterchosenstate.h"
#include "menu.h"

namespace GS {
namespace State {

class DirectorState : public IState<CharacterChosenState>, 
	IStateMachine<DirectorState>, 
	IMenuable
{

selective:
	_UINT64 m_selectedMission;
public:
	_UINT64 getSelectedMission(){ return m_selectedMission; }
	void setSelectedMission(const _UINT64 & a_id){ m_selectedMission = a_id; }

	IMPLEMENT_ISTATE(CharacterChosenState);
	IMPLEMENT_ISTATEMACHINE(DirectorState);
	IMPLEMENT_IMENUABLE;
};

};
};

#endif