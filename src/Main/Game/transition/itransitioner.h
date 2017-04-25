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

};
};

#endif