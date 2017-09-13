#include "selectscene.h"

// Target scene
#include <Game/scenes/launchscenes/optionsscene.h>

namespace GS {
namespace Scene {

_UINT32 SelectScene::onEnter(GS::Stage::LaunchStage * a_sm)
{
	DEBUG_OUT(__FUNCTION__);

	// using the parent machine, set up the referencer
	m_pRef = a_sm->getReferencer();
	m_pTime = m_pRef->pTime;
	m_pInput = m_pRef->pInput;

	m_sceneTransitioner.init();

	// 3 second fade in from nothing,
	// 1/2 second fade in from anything.
	if (std::strcmp(m_sceneTransitioner.getPreviousStateName().c_str(), "") == 0)
		m_sceneTransitioner.armForTransitionFrom(3.0);
	else
		m_sceneTransitioner.armForTransitionFrom(0.5);

	return 0;
}

_UINT32 SelectScene::onUpdate(GS::Stage::LaunchStage * a_sm)
{
	if (!areResourcesReady())
	{
	}
	else if (m_sceneTransitioner.overrideUpdate(a_sm, m_pTime->getDeltaTime()))
	{
	}
	else
	{
		if (m_pInput->isPressed(50))
		{
			GS::Scene::OptionsScene * pOptionsScene = new GS::Scene::OptionsScene();
			m_sceneTransitioner.armForTransitionTo(pOptionsScene, this, 0.5);
			DEBUG_OUT(" 2 Pressed, Transition to OPTIONS. ");
		}
	}

	return 0;
}

_UINT32 SelectScene::onExit(GS::Stage::LaunchStage * a_sm)
{
	DEBUG_OUT(__FUNCTION__);

	return 0;
}

};
};