#ifndef __TRANSITION_H_
#define __TRANSITION_H_

#include <Utilities\definitions_types.h>

#ifdef DEBUG_OUTPUT_ENABLED
#include <iostream>
#endif

namespace GS {
namespace Transition {
const enum TransStatus {
	TRANS_STA_UNKNOWN = 0,
	TRANS_IN = 1,
	TRANS_OUT = 2,
	TRANS_UPDATE = 3
};
/*
const enum TransDirection {
	TRANS_DIR_UNKNOWN = 0,
	TRANS_UP = 1,
	TRANS_DOWN = 2,
	TRANS_LEFT = 3,
	TRANS_RIGHT = 4,
	TRANS_NODIR = 5
};

const enum TransEffect {
	TRANS_EFF_UNKNOWN = 0,
	TRANS_FADE = 1,
	TRANS_NOFADE = 2
};

struct TransRecipe
{
	TransDirection dir;
	TransEffect eff;
	_DOUBLE duration;
	TransRecipe()
	{
		dir = TRANS_DIR_UNKNOWN;
		eff = TRANS_EFF_UNKNOWN;
		duration = 0.0;
	}
	TransRecipe(TransDirection a_dir, TransEffect a_eff, _DOUBLE a_dur)
	{
		dir = a_dir;
		eff = a_eff;
		duration = a_dur;
	}
};
*/

};
};

#endif