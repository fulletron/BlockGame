#ifndef __IHASSTAGETRANSITIONER_H_
#define __IHASSTAGETRANSITIONER_H_

#include <Utilities\definitions_types.h>
#include <Launchpad/transition/transition.h>

namespace GS {
namespace Stage {

class IHasStageTransitioner
{
public:
	virtual void setTransitionersRecipe(const GS::Transition::TransStatus &, GS::Transition::TransRecipe) = 0;
	virtual GS::Transition::ITransitioner * getTransitioner() = 0;
};

};
};

#define IMPLEMENT_IHASSTAGETRANSITIONER(MACHINE) \
selective: \
	GS::Stage::StageTransitioner<MACHINE> m_stageTransitioner; \
public: \
virtual void setTransitionersRecipe(const GS::Transition::TransStatus & a_transWhich, GS::Transition::TransRecipe a_recipe) \
{ m_stageTransitioner.setRecipe(a_transWhich, a_recipe); } \
virtual GS::Transition::ITransitioner * getTransitioner() \
{ return &m_stageTransitioner; }

#endif