#include <iostream>

#include <Utilities/typedefinitions.h>
#include <Utilities/utilities.h>
#include <Graphics/graphics.h>

#include "testpane.h"

bool g_isRunning = false;

// WHENEVER THESE ARE NEEDED, THEY ARE TO BE EXTERNED
// Globals are used for classes that should only
// exist once. In addition, the ChunkManager class
// needs to be accessible from everywhere, as it
// replaces new and malloc

GS::Utilities::ChunkManager g_chunkman;
GS::Graphics::Window g_window;
GS::Utilities::Input g_input;
GS::Graphics::ResourceLibrary g_lib;

int main()
{
	// Init the chunk manager
	g_chunkman.init();
	g_lib.init();

	// build a single "frame" for scoped allocations
	// keep track of the "frame" to truly free it later
	GS::Utilities::Frame * pTrash = 0;
	pTrash = g_chunkman.createFrame( CV8::FRAME_TRASH );

	// Global window and global input, both
	// will only ever exist once
	g_window.init();
	g_input.init();
	
	if ( _CheckForErrors() )
		return -1;

	// For now, the game states do not exist
	// instead, i have this one pane (states are groupings
	// of panes)
	GS::Game::TestPane testPane;
	GS::Game::FPSCounter fpsCounter;
	testPane.init(&fpsCounter);

	// checks for gl and glfw errors!
	if ( _CheckForErrors() )
		return -1;

	// game variable
	g_isRunning = true;

	// total time!
	double tt = 0.0;

	while( g_isRunning && g_window.isOpen() )
	{
		if ( _CheckForErrors() )
			return -1;

		double dt;
		do{ dt = glfwGetTime(); } // TODO :: something more productive
		while (dt < FPS_CAP_MS); // cap the fps

		// gdb update?
		tt += dt;

		glfwSetTime(0.0);

		fpsCounter.update(dt);

		// all of this is placeholder until pane/state are implemeneted

		float ratio;
		int width, height;

		glfwGetFramebufferSize(g_window.getGLFWwindow(), &width, &height);
			
		ratio = width / (float) height;
		glViewport(0, 0, width, height);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.22f,0.22f,0.22f,1.0f);

		testPane.draw();		

		g_window.swapBuffers();
		glfwPollEvents();
	}


	// input has no shutdown
	// g_input.shutdown();
	g_window.shutdown();
	pTrash->shutdown();
	g_chunkman.shutdown();

	return 0;
}
