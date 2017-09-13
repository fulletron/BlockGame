#include "optionsscene.h"

// target scenes
#include <Game/scenes/launchscenes/selectscene.h>

namespace GS {
namespace Scene {

_UINT32 OptionsScene::onEnter(GS::Stage::LaunchStage * a_sm)
{
	DEBUG_OUT(__FUNCTION__);

	// using the parent machine, set up the referencer
	m_pRef = a_sm->getReferencer();
	m_pTime = m_pRef->pTime;
	m_pInput = m_pRef->pInput;

	m_sceneTransitioner.init();

	// Regardless of where i'm coming from, i want to transition in for
	m_sceneTransitioner.armForTransitionFrom(0.5);

	return 0;
}

_UINT32 OptionsScene::onUpdate(GS::Stage::LaunchStage * a_sm)
{
	if (!areResourcesReady())
	{
	}
	else if (m_sceneTransitioner.overrideUpdate(a_sm, m_pTime->getDeltaTime()))
	{
	}
	else
	{
		if (m_pInput->isPressed(49))
		{
			GS::Scene::SelectScene * pSelectScene = new GS::Scene::SelectScene();
			m_sceneTransitioner.armForTransitionTo(pSelectScene, this, 0.5);
			DEBUG_OUT(" 1 Pressed, Transition to SELECT. ");
		}
	}

	return 0;
}

_UINT32 OptionsScene::onExit(GS::Stage::LaunchStage * a_sm)
{
	DEBUG_OUT(__FUNCTION__);

	return 0;
}


};
};