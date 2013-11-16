#ifndef __WORLDPANEL_H_
#define __WORLDPANEL_H_

#include "Panel\base\panel.h"
#include "..\..\Entity\entity.h"

namespace GS {
namespace PanelNS {
	class WorldPanel : public GS::PanelNS::PanelBase
	{
		private:
			// KYLE :: LIST OF PANELS GO HERE~

		public:
			WorldPanel() 
			{}

			_UINT32 init(GS::Game *);
	};
};
};

#endif