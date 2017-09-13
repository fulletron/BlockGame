#include "selectstage.h"

// Target states

#include "Utilities/input/iinput.h"
extern GS::Utilities::IInput * g_pInput;

namespace GS {
namespace Stage {

SelectStage::SelectStage()
{
}

SelectStage::~SelectStage()
{
}

	/*
_UINT32 SelectStage::onEnter(OverStage * a_sm)
{
	DEBUG_OUT( __FUNCTION__ );

	// Creates all of the actors and panels
	__createActorsAndPanels(&m_requiredActors, &m_panels);

	// Subscribe to all of the resources needed
	__performStageSubscriptions(&m_requiredActors, &m_panels);

	return 0;
}

_UINT32 SelectStage::onUpdate(OverStage * a_sm)
{
	if (m_stageTransitioner.overrideUpdate(a_sm, this))
		return 0;

	if (g_pInput->isPressed(50))
	{
//		GS::Transition::TransRecipe transOut(
//			GS::Transition::TransDirection::TRANS_RIGHT,
//			GS::Transition::TransEffect::TRANS_FADE,
//			0.25);
//		GS::Transition::TransRecipe transIn(
//			GS::Transition::TransDirection::TRANS_LEFT,
//			GS::Transition::TransEffect::TRANS_FADE,
//			0.25);
//		Test2Stage * pNextState = new Test2Stage();
//		m_stageTransitioner.armForTransitions(transOut, pNextState, pNextState, transIn);

		DEBUG_OUT(" Button Pushed ");
	}
	return 0;
}

_UINT32 SelectStage::onExit(OverStage * a_sm)
{
	DEBUG_OUT( __FUNCTION__ );

	// The required actors list doesn't have any actors that exist solely with it. Just 
	// clear it out.
	m_requiredActors.clear();

	// Tell all of the actors in all of the panels to unsubscribe
	// Go through the list of panels
	for (_VECTOR<GS::Panel::IPanel *>::iterator panel_iter = m_panels.begin(); panel_iter < m_panels.end();)
	{
		_VECTOR<GS::Actor::IActor *> * pActors = (*panel_iter)->getActors();
		for (_VECTOR<GS::Actor::IActor *>::iterator actor_iter = pActors->begin(); actor_iter < pActors->end();)
		{
			(*actor_iter)->performUnsubscriptions(); // UNSUBSCRIBE!
			actor_iter++;
		}
		panel_iter++;
	}
	return 0;
}

_BOOL SelectStage::areResourcesReady()
{
	// Go through the list of required resources and make sure they exist, and they are ready
	for (_VECTOR<GS::Actor::IActor *>::iterator iter = m_requiredActors.begin(); iter < m_requiredActors.end();)
	{
		if ((*iter)->areResourcesReady())
			iter++;
		else
			return false;
	}
	return true;
}

_UINT32 SelectStage::__performStageSubscriptions(_VECTOR<GS::Actor::IActor *> * a_requiredActors, _VECTOR<GS::Panel::IPanel *> * a_panels)
{
	// BEFORE WE SUBSCRIBE, WE NEED TO TELL THE ACTORS ABOUT THEIR PRIORITY STATUS. THIS IS BECAUSE, DURING THEIR OWN SUBSCRIPTION PROCESS,
	// THEY WILL LOOK AT THEIR OWN FLAGGED PRIORITY AND TELL THE LIBRARY ABOUT IT.
	for (_VECTOR<GS::Actor::IActor *>::iterator actor_iter = a_requiredActors->begin(); actor_iter < a_requiredActors->end();)
	{
		(*actor_iter)->setSubscriptionPriority(true);
		actor_iter++;
	}

	// Tell all of the actors in all of the panels to subscribe
	// Go through the list of panels
	for (_VECTOR<GS::Panel::IPanel *>::iterator panel_iter = m_panels.begin(); panel_iter < m_panels.end();)
	{
		_VECTOR<GS::Actor::IActor *> * pActors = (*panel_iter)->getActors();
		for (_VECTOR<GS::Actor::IActor *>::iterator actor_iter = pActors->begin(); actor_iter < pActors->end();)
		{
			(*actor_iter)->performSubscriptions();
			actor_iter++;
		}
		panel_iter++;
	}
	return 0;
}
*/

_UINT32 SelectStage::__createActorsAndPanels(_VECTOR<GS::Actor::IActor *> * this_requiredActors, _VECTOR<GS::Panel::IPanel *> * this_panels)
{
	GS::Actor::IActor * test_actor = new GS::Actor::TestActor();

	// Create all of the panels for this stage
	GS::Panel::IPanel * test_panel = new GS::Panel::TestPanel();

	// push all of the actors into their appropriate panels.
	test_panel->getActors()->push_back(test_actor);

	// push all of the created panels into the stages list of panels
	this_panels->push_back(test_panel);

	// Tell the stage which actors are REQUIRED before the stage can
	// transition in.
	this_requiredActors->push_back(test_actor);

	return 0;
}

};
};