#include "testpane.h"
#include <Graphics/reslib.h>

extern GS::Graphics::ResourceLibrary g_lib;

namespace GS {
namespace Game {

_INT32 TestPane::init()
{
	m_pProg = g_lib.findShaderProgramResource( CV8::RES_SP_FONTDRAW );
	m_pFont = g_lib.findFontResource( CV8::RES_FONT_KASHSCRIPT );
	
	return 0;
}

_BOOL TestPane::isDirty()
{
	// KYLE :: TODO:: 
	// THIS FUNCTION CALLS ALL OF getDirty() functions of all the pane objects.
	return false;
}

void TestPane::draw()
{
	// KYLE :: DO MAGIC
}

};
};
