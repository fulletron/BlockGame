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
	// Global window and global input, both
	// will only ever exist once
	g_window.init();
	_CheckForErrors();

	g_lib.init();
	g_input.init();
	
	GS_ASSERT ( false, _CheckForErrors(), -1 );

	// For now, the game states do not exist
	// instead, i have this one pane (states are groupings
	// of panes)
	//GS::Graphics::DebugPane debugPane;
	//debugPane.init(0);
	//GS::Game::Brain * brain = &GS::Game::Brain::getInstance();
	//brain->init();
	//s_brain = &brain;
	// checks for gl and glfw errors!
	if ( _CheckForErrors() )
		return -1;

	// game variable
	g_isRunning = true;

	// TEST DRAWING OF PICTURE
	GS::Graphics::TextureResource * test_Tex = g_lib.findTextureResource(CV8::TEX::PANEBKG);
	GS::Graphics::ShaderProgramResource * test_TexProg = g_lib.findShaderProgramResource(CV8::RES_SP_TEXRECTDRAW);
	GS::Graphics::MeshResource * test_Mesh = g_lib.findMeshResource(CV8::RES_MSH_SCREEN);

	GLint texloc = glGetUniformLocation(test_TexProg->getProgram(), "tex");
	GLint transloc = glGetUniformLocation(test_TexProg->getProgram(), "trans");

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
		//brain->update(dt);

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
// TEST PIC DRAWING [[[[[[[[[[[[[[[[[[[[[[[[[[[

		glUseProgram(test_TexProg->getProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, test_Tex->getTexture());
		glUniform1i(texloc, 0);

		// BIND ALL THE CRAP
		glBindVertexArray(test_Mesh->getVAO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, test_Mesh->getEBO());
		glUseProgram(test_TexProg->getProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, test_Tex->getTexture());

		glUniform1i(texloc, 0);

		glm::mat4 trans;
		trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f));
		trans = glm::translate(trans, glm::vec3(0.0f * 2.0f, 0.0f * 2.0f, 0.0f));
		glUniformMatrix4fv(transloc, 1, GL_FALSE, glm::value_ptr(trans));

		// THESE NEED TO BE SPECIFIED EVERYTIME
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		_CheckForErrors();

// ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
// TEST FONT DRAWING [[[[[[[[[[[[[[[[[[[[[[[
		std::string test_str = "THIS IS A TEST!";
		_CheckForErrors();
		if ( test_SPR != test_TexProg )
		   glUseProgram(test_SPR->getProgram());
		_CheckForErrors();
		glActiveTexture(GL_TEXTURE0);
		_CheckForErrors();
		glBindTexture(GL_TEXTURE_2D, test_Font->m_texture);
		//glUniform1i( glGetUniformLocation( m_pFontDrawingProg->getProgram(), "tex" ), 0 );
		_CheckForErrors();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		_CheckForErrors();
		GLint transloc2 = glGetUniformLocation(test_SPR->getProgram(), "trans");
		glm::mat4 trans2;
		glUniformMatrix4fv(transloc2, 1, GL_FALSE, glm::value_ptr(trans2));

		_CheckForErrors();

		test_Font->renderText(
			test_str,
			//GS::Graphics::Vector2_t( STATIC_CAST(_FLOAT, -dims.x), STATIC_CAST(_FLOAT, (dims.y-m_pFont->getHeight() ) ) ), 
			GS::Graphics::Vector2_t(0.0f, 0.0f),
			g_window.getPixelDimensions(),
			1.0f,
			GS::Graphics::Color4f_t(0.0f, 1.0f, 1.0f, 1.0f)
			);
		_CheckForErrors();
// ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
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