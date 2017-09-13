#ifndef __LAUNCHSTAGE_H_
#define __LAUNCHSTAGE_H_

//#include <Utilities/definitions_values.h>
#include <Utilities/definitions_types.h>
#include "../mainmachine.h"

#include <Framework/stage/stage.h>

#include <Framework/referencer/referencer.h>

namespace GS {
namespace Stage {

class LaunchStage : public GS::State::IState<MainMachine>, public GS::Resource::IResourceRequirer, public GS::State::IStateMachine<LaunchStage>
{
selective:
	GS::Referencer * m_pRef;
	GS::Utilities::ITime * m_pTime;
	GS::Utilities::IInput * m_pInput;

	GS::State::StateTransitioner<MainMachine> m_stateTransitioner;

	State::IState<LaunchStage> * m_pCurrentScene;

	_VECTOR<GS::Panel::IPanel *> m_panels;

	/*
	* This is a subset of the actors in m_panels. The actors
	* listed are REQUIRED before the stage will begin to
	* transition in.
	*/
	_VECTOR<GS::Actor::IActor *> m_requiredActors;

	virtual _UINT32 __performStageSubscriptions(_VECTOR<GS::Actor::IActor *> * a_requiredActors, _VECTOR<GS::Panel::IPanel *> * a_panels);
	virtual _UINT32 __createActorsAndPanels(_VECTOR<GS::Actor::IActor *> *, _VECTOR<GS::Panel::IPanel *> *);

public:
	LaunchStage();
	~LaunchStage();

	virtual State::IState<LaunchStage> * getState()
	{
		return m_pCurrentScene;
	}

	virtual void changeState(State::IState<LaunchStage> * a_newSubState)
	{
		m_pCurrentScene->onExit(this);
		delete m_pCurrentScene;
		m_pCurrentScene = a_newSubState;
		m_pCurrentScene->onEnter(this);
	}

	virtual _UINT32 onEnter(MainMachine * a_sm);
	virtual _UINT32 onUpdate(MainMachine * a_sm);
	virtual _UINT32 onExit(MainMachine * a_sm);
	virtual std::string whoAmI() const;
	virtual GS::State::StateTransitioner<MainMachine> * getStateTransitioner() { return &m_stateTransitioner; }

	virtual _BOOL areResourcesReady();

	GS::Referencer * getReferencer(){ return m_pRef; }

};


};
};

#endif