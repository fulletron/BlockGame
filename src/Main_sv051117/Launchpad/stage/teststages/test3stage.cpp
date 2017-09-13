#include "test3stage.h"

// Target state
#include "test2stage.h"

#include "Utilities/input/iinput.h"
extern GS::Utilities::IInput * g_pInput;

namespace GS {
namespace Stage {

_UINT32 Test3Stage::onEnter(AllStage * a_sm)
{
	DEBUG_OUT("TEST3STATE ENTER ");
	return 0;
}

_UINT32 Test3Stage::onUpdate(AllStage * a_sm)
{
	if (m_stageTransitioner.overrideUpdate(a_sm, this))
		return 0;

	if (g_pInput->isPressed(50))
	{
		GS::Transition::TransRecipe transOut(
			GS::Transition::TransDirection::TRANS_RIGHT,
			GS::Transition::TransEffect::TRANS_FADE,
			0.25);
		GS::Transition::TransRecipe transIn(
			GS::Transition::TransDirection::TRANS_LEFT,
			GS::Transition::TransEffect::TRANS_FADE,
			0.25);
		Test2Stage * pNextState = new Test2Stage();
		m_stageTransitioner.armForTransitions(transOut, pNextState, pNextState, transIn);
		DEBUG_OUT("Just Armed to trans from 3 to 2. ");
	}
	return 0;
}

_UINT32 Test3Stage::onExit(AllStage * a_sm)
{
	DEBUG_OUT("TEST3STATE EXIT ");
	return 0;
}

};
};