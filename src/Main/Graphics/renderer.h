#ifndef __RENDERER_H_
#define __RENDERER_H_

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