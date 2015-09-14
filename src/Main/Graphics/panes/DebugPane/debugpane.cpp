#include "debugpane.h"
#include <Graphics/reslib.h>

#include <Graphics/Panes/DebugPane/fpscounterpasset.h>
#include <Graphics/Panes/DebugPane/testannouncementpasset.h>
#include <Graphics/Panes/DebugPane/bkgpicpasset.h>
#include <Game/brain.h> // TODO :: REMOVE! ONCE SINGLETON IS NO LONGER USED

extern GS::Graphics::ResourceLibrary g_lib;

namespace GS {
namespace Graphics {

_INT32 DebugPane::__postInit()
{
	initBlueprints( Vec4D<float>(0.00f,-0.00f,1.00f,1.00f) );

	// LINK ALL THE THINGS, FROM BACK TO FRONT
	IPaneAsset * backgroundPictureAsset = new BkgPicPasset();
	backgroundPictureAsset->init(this);
	m_paneAssets.push_back(backgroundPictureAsset);

	IPaneAsset * testAnnouncementAsset = new TestAnnouncementPasset();
	testAnnouncementAsset->init(this);
	m_paneAssets.push_back(testAnnouncementAsset);

	IPaneAsset * fpsPaneAsset = new FPSCounterPasset();
	fpsPaneAsset->init(this);
	m_paneAssets.push_back(fpsPaneAsset);

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
