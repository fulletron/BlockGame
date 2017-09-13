#ifndef __STAGE_H_
#define __STAGE_H_

#include <Utilities/definitions_types.h>

#include <Framework/state/statetransitioner.h>
#include <Framework/actor/iactor.h>
#include <Framework/panel/panel.h>

namespace GS {
namespace Stage {

template <typename MACHINE> class Stage : public GS::State::IState<MACHINE>, public GS::Resource::IResourceRequirer //, public GS::Stage::IHasStageTransitioner
{
selective:
	_VECTOR<GS::Panel::IPanel *> m_panels;

	/*
	* This is a subset of the actors in m_panels. The actors
	* listed are REQUIRED before the stage will begin to
	* transition in.
	*/
	_VECTOR<GS::Actor::IActor *> m_requiredActors;

	GS::State::StateTransitioner<MACHINE> m_stateTransitioner;

selective:
	//template <typename MACHINE>
	virtual _UINT32 __performStageSubscriptions(_VECTOR<GS::Actor::IActor *> * a_requiredActors, _VECTOR<GS::Panel::IPanel *> * a_panels)
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

	virtual _UINT32 __createActorsAndPanels(_VECTOR<GS::Actor::IActor *> * this_requiredActors, _VECTOR<GS::Panel::IPanel *> * this_panels)
	{
		DEBUG_OUT_RED(__FUNCTION__);
		DEBUG_OUT_RED("SHOULD NOT BE HERE DERIVED CLASS UNDEFINED");
		return -1;
	}


public:
	virtual _UINT32 onEnter(MACHINE * a_sm)
	{
		DEBUG_OUT(__FUNCTION__);

		// Creates all of the actors and panels
		__createActorsAndPanels(&m_requiredActors, &m_panels);

		// Subscribe to all of the resources needed
		__performStageSubscriptions(&m_requiredActors, &m_panels);

		m_stateTransitioner.armForTransitionFrom(1.0);

		return 0;
	}

	virtual _UINT32 onUpdate(MACHINE * a_sm)
	{
		if (m_stateTransitioner.overrideUpdate(a_sm, this))
			return 0;

		// UPDATE ALL PANELS, ALL ACTORS WITH STUFF

		// HANDLE INPUT

		//if (g_pInput->isPressed(50))
		//{
		//GS::Transition::TransRecipe transOut(
		//GS::Transition::TransDirection::TRANS_RIGHT,
		//GS::Transition::TransEffect::TRANS_FADE,
		//0.25);
		//GS::Transition::TransRecipe transIn(
		//GS::Transition::TransDirection::TRANS_LEFT,
		//GS::Transition::TransEffect::TRANS_FADE,
		//0.25);
		//Test2Stage * pNextState = new Test2Stage();
		//m_stageTransitioner.armForTransitions(transOut, pNextState, pNextState, transIn);
		//	DEBUG_OUT(" Button Pushed ");
		//}
		return 0;
	}

	virtual _UINT32 onExit(MACHINE * a_sm)
	{
		DEBUG_OUT(__FUNCTION__);

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

	virtual _BOOL areResourcesReady()
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

	virtual std::string whoAmI() const
	{
		DEBUG_OUT_RED(__FUNCTION__);
		DEBUG_OUT_RED("SHOULD NOT BE HERE DERIVED CLASS UNDEFINED");
		return "Stage";
	}


//	virtual void setTransitionersRecipe(const GS::Transition::TransStatus & a_transWhich, GS::Transition::TransRecipe a_recipe)
//	{
//		m_stageTransitioner.setRecipe(a_transWhich, a_recipe);
//	}

//	virtual GS::Transition::ITransitioner * getTransitioner()
//	{
//		return &m_stageTransitioner;
//	}

};

};
};

#endif