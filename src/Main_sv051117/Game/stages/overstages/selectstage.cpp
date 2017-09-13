#include "selectstage.h"

// Target states

#include "Utilities/input/iinput.h"
extern GS::Utilities::IInput * g_pInput;

namespace GS {
namespace Stage {

_UINT32 SelectStage::onEnter(OverStage * a_sm)
{
	DEBUG_OUT( __FUNCTION__ );
	return 0;
}

_UINT32 SelectStage::onUpdate(OverStage * a_sm)
{
	if (m_stageTransitioner.overrideUpdate(a_sm, this))
		return 0;

	if (g_pInput->isPressed(50))
	{
		/*
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
		*/
		DEBUG_OUT(" Button Pushed ");
	}
	return 0;
}

_UINT32 SelectStage::onExit(OverStage * a_sm)
{
	DEBUG_OUT( __FUNCTION__ );
	return 0;
}

};
};