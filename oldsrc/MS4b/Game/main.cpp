#include <Graphics\openglincludes.h>
#include "game.h"
#include "definitions.h"
#include "inlines.h"

int main()
{
	GS::Game g;

	DBC(g.init(), "FAILED:: COULD NOT INIT GAME");
	glfwSetTime(0.0);
	while(g.isRunning() && glfwGetWindowParam( GLFW_OPENED ))
	{
		g.render();
		g.input();

		_DOUBLE dt = glfwGetTime();
		glfwSetTime(0.0);

		g.update(dt);
	}

	g.shutdown();

	return 0;
}