#ifndef __ITRANSITIONER_H_
#define __ITRANSITIONER_H_

#include <Utilities\definitions_types.h>
#include "transition.h"

namespace GS {
namespace Transition {

class ITransitioner
{
public:
	virtual TransRecipe getCurrentRecipe() const = 0;
	virtual _DOUBLE getCurrentPercentageComplete(const TransStatus &) const = 0;
};

class IHasTransitioner
{
public:
	virtual void setTransitionersRecipe(const TransStatus &, TransRecipe) = 0;
	virtual ITransitioner * getTransitioner() = 0;
};


#define IMPLEMENT_IHASTRANSITIONER(MACHINE) \
selective: \
	StageTransitioner<MACHINE> m_stageTransitioner; \
public: \
virtual void setTransitionersRecipe(const GS::Transition::TransStatus & a_transWhich, GS::Transition::TransRecipe a_recipe) \
{ m_stageTransitioner.setRecipe(a_transWhich, a_recipe); } \
virtual GS::Transition::ITransitioner * getTransitioner() \
{ return &m_stageTransitioner; }

};
};

#endif