#ifndef __PANEL_H_
#define __PANEL_H_

#include <Utilities/typedefinitions.h>

namespace GS {
namespace Graphics {

class Pane {

#ifdef TEST_ENABLED
public:
#else
protected:
#endif
	_BOOL m_dirty;
public:

};

};
};

#endif