#ifndef __OPTIONSSCENE_H_
#define __OPTIONSSCENE_H_

#include <Utilities/definitions_types.h>

#include <Framework/state/statetransitioner.h>

#include <Game/stages/mainstages/launchstage.h>

#include <Graphics/resource/iresourcerequirer.h>

#include <Framework/actor/iactor.h>
#include <Framework/panel/panel.h>

namespace GS {
namespace Scene {

class OptionsScene : public GS::State::IState<GS::Stage::LaunchStage>, public GS::Resource::IResourceRequirer
{

selective:
	GS::State::StateTransitioner<GS::Stage::LaunchStage> m_sceneTransitioner;
	GS::Referencer * m_pRef;
	GS::Utilities::ITime * m_pTime;
	GS::Utilities::IInput * m_pInput;

public:
	OptionsScene(){}
	~OptionsScene(){}

	virtual _UINT32 onEnter(GS::Stage::LaunchStage * a_sm);
	virtual _UINT32 onUpdate(GS::Stage::LaunchStage * a_sm);
	virtual _UINT32 onExit(GS::Stage::LaunchStage * a_sm);

	virtual std::string whoAmI() const
	{
		return "OptionsScene";
	}

	virtual GS::State::StateTransitioner<GS::Stage::LaunchStage> * getStateTransitioner() { return &m_sceneTransitioner; }

	virtual _BOOL areResourcesReady()
	{
		return true;
	}

//	void setTimeObject(GS::Utilities::ITime * a_pTime) { m_pTime = a_pTime; }

};

};
};

#endif