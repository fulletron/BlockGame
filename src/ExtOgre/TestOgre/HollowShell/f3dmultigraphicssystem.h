#include "graphicssystem.h"

namespace OGraphics
{
	class F3DMultiGraphicsSystem : public GraphicsSystem
	{
		virtual Ogre::CompositorWorkspace* setupCompositor();

	public:
		F3DMultiGraphicsSystem(IGameState *gameState) :
			GraphicsSystem(gameState)
		{
		}

		virtual void setupResources(void);
	};

	const char* getWindowTitle(void);

	const double FRAMETIME = 1.0 / 240.0;
};