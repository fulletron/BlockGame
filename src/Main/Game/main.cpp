#include <iostream>

#include <Utilities/typedefinitions.h>
#include <Utilities/utilities.h>
#include <Graphics/graphics.h>

//#include "testpane.h"
#include <Graphics/Panes/DebugPane/debugpane.h>
#include "brain.h"

bool g_isRunning = false;

GS::Graphics::Window g_window;
GS::Utilities::Input g_input;
GS::Graphics::ResourceLibrary g_lib;

int main()
{
	g_lib.init();

	// Global window and global input, both
	// will only ever exist once
	g_window.init();
	g_input.init();
	
	GS_ASSERT ( false, _CheckForErrors(), -1 );

	// For now, the game states do not exist
	// instead, i have this one pane (states are groupings
	// of panes)
	GS::Graphics::DebugPane debugPane;
	debugPane.init(0);
	GS::Game::Brain * brain = &GS::Game::Brain::getInstance();
	brain->init();
	//s_brain = &brain;
	// checks for gl and glfw errors!
	if ( _CheckForErrors() )
		return -1;

	// game variable
	g_isRunning = true;

	// TEST DRAWING OF TEXT
	GS::Graphics::ShaderProgramResource * test_SPR = g_lib.findShaderProgramResource(CV8::RES_SP_FONTDRAW);
	GS::Graphics::FontResource * test_Font = g_lib.findFontResource(CV8::RES_FONT_KASHSCRIPT_16);

	// total time!
	double tt = 0.0;

	while( g_isRunning && g_window.isOpen() )
	{
		GS_ASSERT(false, _CheckForErrors(), -1);

		double dt;
		do{ dt = glfwGetTime(); } // TODO :: something more productive
		//while (0); // cap the fps
		while (dt < FPS_CAP_MS); // cap the fps

		// gdb update?
		tt += dt;

		glfwSetTime(0.0);

		//fpsCounter.update(dt);
		brain->update(dt);

		GS_ASSERT(false, _CheckForErrors(), -1);

		// all of this is placeholder until pane/state are implemeneted

		float ratio;
		int width, height;

		glfwGetFramebufferSize(g_window.getGLFWwindow(), &width, &height);
			
		ratio = width / (float) height;
		glViewport(0, 0, width, height);
		glBindFramebuffer(GL_FRAMEBUFFER, g_window.getFramebuffer() );
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.22f,0.22f,0.52f,1.0f);

		// TEST FONT DRAWING
		std::string test_str = "THIS IS A TEST!";

		glUseProgram(test_SPR->getProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, test_Font->m_texture);
		//glUniform1i( glGetUniformLocation( m_pFontDrawingProg->getProgram(), "tex" ), 0 );

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLint transloc = glGetUniformLocation(test_SPR->getProgram(), "trans");
		glm::mat4 trans;
		glUniformMatrix4fv(transloc, 1, GL_FALSE, glm::value_ptr(trans));

		test_Font->renderText(
			test_str,
			//GS::Graphics::Vector2_t( STATIC_CAST(_FLOAT, -dims.x), STATIC_CAST(_FLOAT, (dims.y-m_pFont->getHeight() ) ) ), 
			GS::Graphics::Vector2_t(0.0f, 0.0f),
			g_window.getPixelDimensions(),
			1.0f,
			GS::Graphics::Color4f_t(0.0f, 1.0f, 1.0f, 1.0f)
			);

		/*

		GS_ASSERT(false, _CheckForErrors(), -1);

		debugPane.update(dt);

		GS_ASSERT(false, _CheckForErrors(), -1);

		debugPane.draw( &g_window );

		GS_ASSERT(false, _CheckForErrors(), -1);
		*/
		g_window.swapBuffers();
		glfwPollEvents();

		GS_ASSERT(false, _CheckForErrors(), -1);
	}


	// input has no shutdown
	// g_input.shutdown();
	g_window.shutdown();

	return 0;
}


/* KYLE :: WORKING WITH OTHER SEGMENT

bool g_isRunning = false;

GS::Graphics::Window g_window;
GS::Utilities::Input g_input;
GS::Graphics::ResourceLibrary g_lib;

int main()
{
	g_lib.init();

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

	return 0;
}

*/