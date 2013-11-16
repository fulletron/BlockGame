#ifndef __LAYERBACKGROUNDTEXT_H_
#define __LAYERBACKGROUNDTEXT_H_

#include <Panel\base\layer.h>

namespace GS {
namespace PanelNS {
	class LayerBackgroundText : public LayerBase
	{
	private:

	public:
		LayerBackgroundText()
		{}

		_UINT32 init(GS::Game * const a_pG);
	};
};
};
#endif