#ifndef __SELECTSCENE_H_
#define __SELECTSCENE_H_

#include <Utilities/definitions_types.h>

#include <Framework/state/statetransitioner.h>

#include <Game/stages/mainstages/launchstage.h>

#include <Framework/actor/iactor.h>
#include <Framework/panel/panel.h>

#include <Framework/referencer/referencer.h>

namespace GS {
namespace Scene {

class SelectScene : public GS::State::IState<GS::Stage::LaunchStage>, public GS::Resource::IResourceRequirer
{
selective:
	GS::Referencer * m_pRef;
	GS::Utilities::ITime * m_pTime;
	GS::Utilities::IInput * m_pInput;

	GS::State::StateTransitioner<GS::Stage::LaunchStage> m_sceneTransitioner;

public:
	SelectScene(){}
	~SelectScene(){}

	virtual _UINT32 onEnter(GS::Stage::LaunchStage * a_sm);
	virtual _UINT32 onUpdate(GS::Stage::LaunchStage * a_sm);
	virtual _UINT32 onExit(GS::Stage::LaunchStage * a_sm);

	virtual std::string whoAmI() const
	{
		return "SelectScene";
	}

	virtual GS::State::StateTransitioner<GS::Stage::LaunchStage> * getStateTransitioner() { return &m_sceneTransitioner; }

	virtual _BOOL areResourcesReady()
	{
		return true;
	}

};

};
};

#endif