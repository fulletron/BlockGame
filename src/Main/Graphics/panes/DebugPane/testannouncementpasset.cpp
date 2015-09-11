#include <Graphics/reslib.h>

#include <Graphics/panes/testannouncementpaneasset.h>
#include <Game/brain.h> // TODO :: REMOVE! ONCE SINGLETON IS NO LONGER USED

extern GS::Graphics::ResourceLibrary g_lib;

namespace GS {
namespace Graphics {

/**
* init the paneasset resources
*/
_INT32 TestAnnouncementPaneAsset::init( Pane * const a_pParent )
{
	m_pParentPane = a_pParent;

	// RELEVANT TO FPS COUNTER ASSET
	m_pFadeBar = g_lib.findTextureResource( CV8::RES_TEX_FADEBAR );
	m_pTexRectProg = g_lib.findShaderProgramResource ( CV8::RES_SP_TEXRECTDRAW );

	return 0;
}


_BOOL TestAnnouncementPaneAsset::isDirty() const
{
	return true;
	//return false;
}

/**
* Tells the PaneAsset to clean up
*/ 
void TestAnnouncementPaneAsset::shutdown()
{
	g_lib.forgetResource( m_pFadeBar );
}

/**
* Draws the PaneAsset.
*/
void TestAnnouncementPaneAsset::draw( GS::Graphics::IDimensionable * const a_dims )
{

}

/**
* Updates the PaneAsset by dt.
*/
void TestAnnouncementPaneAsset::update(const _DOUBLE a_dt)
{
	m_timer += a_dt;
}


};
};
