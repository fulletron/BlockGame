#ifndef __SELECTSTAGE_H_
#define __SELECTSTAGE_H_

#include <Utilities/definitions_types.h>
#include "../overstage.h"

#include <Framework/stage/stage.h>

namespace GS {
namespace Stage {
/*
class SelectStage : public GS::State::IState<OverStage>, public GS::Stage::IHasStageTransitioner, public GS::Resource::IResourceRequirer
{
	IMPLEMENT_ISTATE(OverStage);
	IMPLEMENT_IHASSTAGETRANSITIONER(OverStage);

public:
	virtual _BOOL areResourcesReady();

selective:
	_VECTOR<GS::Panel::IPanel *> m_panels;

	// This is a subset of the actors in m_panels. The actors
	// listed are REQUIRED before the stage will begin to
	// transition in.
	_VECTOR<GS::Actor::IActor *> m_requiredActors;
public:

selective :
	_UINT32 __performStageSubscriptions(_VECTOR<GS::Actor::IActor *> *, _VECTOR<GS::Panel::IPanel *> *);
//	void __performStageUnsubscriptions(_VECTOR<GS::Panel::IPanel *> * a_panels);

	_UINT32 __createActorsAndPanels(_VECTOR<GS::Actor::IActor *> *, _VECTOR<GS::Panel::IPanel *> *);
};
*/
class SelectStage : public GS::Stage::Stage<OverStage>
{
public:
	SelectStage();
	~SelectStage();

selective :
	virtual _UINT32 __createActorsAndPanels(_VECTOR<GS::Actor::IActor *> *, _VECTOR<GS::Panel::IPanel *> *);
};


};
};

#endif