#include "debugpane.h"
#include <Graphics/reslib.h>

#include <Game/fpscounter.h>

extern GS::Graphics::ResourceLibrary g_lib;

namespace GS {
namespace Game {

_INT32 DebugPane::__postInit()
{
	//initPaneBlues( 0, Vec4D<float>(0.00f,-0.00f,0.50f,0.50f) );
	initPaneBlues( 0, Vec4D<float>(0.00f,-0.00f,1.00f,1.00f) );

	// FPS COUNTER!
	FPSCounter * fpsCounter = new FPSCounter();
	fpsCounter->init();
	m_paneAssets.push_back(fpsCounter);
	
	return 0;
}

void DebugPane::__preShutdown()
{
	
}

};
};
