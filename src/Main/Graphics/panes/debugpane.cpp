#include "debugpane.h"
#include <Graphics/reslib.h>

#include <Graphics/panes/fpscounterpaneasset.h>
#include <Graphics/panes/testannouncementpaneasset.h>
#include <Game/brain.h> // TODO :: REMOVE! ONCE SINGLETON IS NO LONGER USED

extern GS::Graphics::ResourceLibrary g_lib;

namespace GS {
namespace Graphics {

_INT32 DebugPane::__postInit()
{
	initBlueprints( Vec4D<float>(0.00f,-0.00f,1.00f,1.00f) );

	// LINK ALL THE THINGS
	IPaneAsset * fpsPaneAsset = new FPSCounterPaneAsset();
	fpsPaneAsset->init(this);
	m_paneAssets.push_back(fpsPaneAsset);

	// KYLE :: TODO
	//IPaneAsset * backgroundPictureAsset = new BackgroundPictureAsset();
	//backgroundPictureAsset->init(this);
	//m_paneAssets.push_back(backgroundPictureAsset);

	IPaneAsset * testAnnouncementAsset = new TestAnnouncementPaneAsset();
	testAnnouncementAsset->init(this);
	m_paneAssets.push_back(testAnnouncementAsset);

	return 0;
}

void DebugPane::__preShutdown()
{
	
}

void DebugPane::__draw( GS::Graphics::IDimensionable * const a_dims )
{

}

_BOOL DebugPane::__isDirty() const
{
	return false;
}


};
};
