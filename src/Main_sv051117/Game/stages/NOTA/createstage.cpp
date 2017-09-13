#include "createstage.h"

/*
// Target stage
#include "test3stage.h"

#include "Utilities/input/iinput.h"
extern GS::Utilities::IInput * g_pInput;

namespace GS {
namespace Stage {

_UINT32 Test2Stage::onEnter(AllStage * a_sm)
{
	DEBUG_OUT("TEST2STATE ENTER");
	return 0;
}

_UINT32 Test2Stage::onUpdate(AllStage * a_sm)
{
	if (m_stageTransitioner.overrideUpdate(a_sm, this))
		return 0;

	if (g_pInput->isPressed(49))
	{
		GS::Transition::TransRecipe transOut(
			GS::Transition::TransDirection::TRANS_RIGHT,
			GS::Transition::TransEffect::TRANS_FADE,
			0.25);
		GS::Transition::TransRecipe transIn(
			GS::Transition::TransDirection::TRANS_LEFT,
			GS::Transition::TransEffect::TRANS_FADE,
			0.25);
		Test3Stage * pNextState = new Test3Stage();
		m_stageTransitioner.armForTransitions(transOut, pNextState, pNextState, transIn);
		DEBUG_OUT("Armed for transition from 2 to 3.");
	}
	return 0;
}

_UINT32 Test2Stage::onExit(AllStage * a_sm)
{
	DEBUG_OUT("TEST2STATE EXIT ");
	return 0;
}

};
};

*/