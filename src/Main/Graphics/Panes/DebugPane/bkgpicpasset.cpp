#include <Graphics/reslib.h>

#include <Graphics/Panes/DebugPane/bkgpicpasset.h>
#include <Game/brain.h> // TODO :: REMOVE! ONCE SINGLETON IS NO LONGER USED

extern GS::Graphics::ResourceLibrary g_lib;

namespace GS {
namespace Graphics {

/**
* init the paneasset resources
*/
_INT32 BkgPicPasset::init( Pane * const a_pParent )
{
	m_pParentPane = a_pParent;

	// RELEVANT TO FPS COUNTER ASSET
	m_pTex = g_lib.findTextureResource( CV8::RES_TEX_FADEBAR );
	m_pTexRectProg = g_lib.findShaderProgramResource ( CV8::RES_SP_TEXRECTDRAW );

	return 0;
}


_BOOL BkgPicPasset::isDirty() const
{
	return true;
	//return false;
}

/**
* Tells the PaneAsset to clean up
*/ 
void BkgPicPasset::shutdown()
{
	g_lib.forgetResource( m_pTex );
	g_lib.forgetResource( m_pTexRectProg );
}

/**
* Draws the PaneAsset.
*/
void BkgPicPasset::draw( GS::Graphics::IDimensionable * const a_dims )
{

}

/**
* Updates the PaneAsset by dt.
*/
void BkgPicPasset::update(const _DOUBLE a_dt)
{
	m_timer += a_dt;
}


};
};
