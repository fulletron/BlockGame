#ifndef __PANEL_H_
#define __PANEL_H_

#include <Utilities/definitions_types.h>
#include "../actor/iactor.h"
#include "../../Graphics/idimensionable.h"

namespace GS {
namespace Panel {

class IPanel : public GS::Graphics::IDimensionable
{
public:
	virtual _VECTOR<GS::Actor::IActor *> * getActors() = 0;
	virtual _VEC2D<_FLOAT> * getOffset() = 0;
	virtual _UCHAR getDrawPriority() = 0;

	//virtual _VEC2D<_INT32> getPixelDimensions() const;
};

class TestPanel : public IPanel
{
selective:
	_VECTOR<GS::Actor::IActor *> m_actors;
	//GS::Transition::ITransitioner * m_transitioner;
	_VEC2D<_INT32> m_pixelDimensions;
	_VEC2D<_FLOAT> m_offset;
	_UCHAR m_drawPriority;

public:
	virtual _VECTOR<GS::Actor::IActor *> * getActors() { return &m_actors; }
	//virtual GS::Transition::ITransitioner * getTransitioner() { return m_transitioner; }
	virtual _VEC2D<_FLOAT> * getOffset() { return &m_offset; }
	virtual _UCHAR getDrawPriority() { return m_drawPriority; }

	virtual _VEC2D<_INT32> getPixelDimensions() const { return m_pixelDimensions; }
};

};
};

#endif