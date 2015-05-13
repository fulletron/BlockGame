#ifndef __RENDERER_H_
#define __RENDERER_H_

#include <Graphics/openglincludes.h>

namespace GS {
namespace Graphics {

class Renderer
{

#ifdef TEST_ENABLED
public:
#else
private:
#endif

public:
	void render();
};

};
};

#endif