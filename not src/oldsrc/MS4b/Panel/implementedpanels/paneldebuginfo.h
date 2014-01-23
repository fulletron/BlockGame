#ifndef __PANELDEBUGINFO_H_
#define __PANELDEBUGINFO_H_

#include <Panel\base\panel.h>
#include "..\..\Entity\entity.h"

namespace GS {
namespace ResourceNS { class ShaderProgramResource; class MeshResource;};
namespace PanelNS {

	class LayerDebugInfoList  : public PanelBase
	{
	protected:
		static const int TESTNUMREPS = 1;

	public:
		_DOUBLE m_time;
		_UINT32 m_fps;
		LayerDebugInfoList(){}

		static LayerDebugInfoList * Construct(GS::Game * const a_pG, GS::PanelNS::Panel * const a_rpPanel);
		void								update(const _DOUBLE &) override;

	};

	class PanelDebugInfo : public GS::PanelNS::PanelBase
	{
	protected:
	public:
		/// INSTR :: INITIALIZER LIST NEEDS TO NULL EVERYTHING!
		PanelDebugInfo(){}

		static PanelDebugInfo * Construct(GS::Game * const a_pG, GS::PanelNS::Panel * const a_rpPanel);
		//_UINT32 init(GS::Game * const, Panel * const a_pParentPanel);
	};
};
};

#endif