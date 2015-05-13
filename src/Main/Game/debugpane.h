#ifndef __DEBUGPANE_H_
#define __DEBUGPANE_H_

#include <Graphics/panel.h>

namespace GS {
namespace Game {

class DebugPane : public GS::Graphics::Pane
{
selective:
	_INT32 __postInit();
	void __preShutdown();

public:
	DebugPane(): 
			Pane()
			{}	
};

};
};

#endif
