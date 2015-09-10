#ifndef __DEBUGPANE_H_
#define __DEBUGPANE_H_

#include <Graphics/panel.h>
#include <Game/fpscounter.h>

namespace GS {
namespace Graphics {

class DebugPane : public GS::Graphics::Pane
{
selective:
	_INT32 __postInit();
	void __preShutdown();
	void __draw( GS::Graphics::IDimensionable * const a_dimensionable );
	_BOOL __isDirty() const;

public:
	DebugPane(): 
			Pane()
			{}	
};

};
};

#endif
