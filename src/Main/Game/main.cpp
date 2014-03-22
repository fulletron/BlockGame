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


// TODO ::
// This belongs somewhere else,
// but that somewhere else has not been
// implemented yet (Pane/State/Resource)

GS::Graphics::FontResource g_font;
GS::Graphics::ShaderProgramResource g_fontShaderProgram;

int main()
{
	TestPane testPane;
	// Init the chunk manager
	g_chunkman.init();

	g_lib.init();

	GS::Graphics::ShaderResource * pRes =
		g_lib.findShaderResource( 1 );
	
	// build a single "frame" for scoped allocations
	// keep track of the "frame" to truly free it later
	GS::Utilities::Frame * pTrash = 0;
	pTrash = g_chunkman.createFrame( CV8::FRAME_TRASH );

	// Global window and global input, both
	// will only ever exist once
	g_window.init();
	g_input.init();

	// font and shader loading here because 
	// state & panel is not implemented
	std::string vs = _FS::loadFile( ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Effects/" 
		/ "basicfont.vert").string().c_str() );
	std::string fs = _FS::loadFile( ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Effects/" 
		/ "basicfont.frag").string().c_str() );

	g_font.loadFile( "KaushanScript-Regular.otf", 16 );
	//g_font.loadFile( "KaushanScript-Regular.otf", 16 );
//	g_fontShaderProgram.init(vs.c_str(), fs.c_str() );

	// checks for gl and glfw errors!
	_CheckForErrors();

	// game variable
	g_isRunning = true;

	// total time!
	double tt = 0.0;

	while( g_isRunning && g_window.isOpen() )
	{
		_CheckForErrors();

		double dt;
		do{ dt = glfwGetTime(); } // TODO :: something more productive
		while (dt < FPS_CAP_MS); // cap the fps

		// gdb update?
		tt += dt;

		glfwSetTime(0.0);

		// all of this is placeholder until pane/state are implemeneted

		float ratio;
		int width, height;

		glfwGetFramebufferSize(g_window.getGLFWwindow(), &width, &height);
			
		ratio = width / (float) height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.22f,0.22f,0.22f,1.0f);

		glUseProgram(g_fontShaderProgram.m_shaderProgram);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, g_font.m_texture);
		glUniform1i(glGetUniformLocation(g_fontShaderProgram.m_shaderProgram, "tex"), 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
/*
		for ( int i = 0; i < 100; ++i ){
		g_font.renderText("12000", GS::Graphics::Vector2_t(-800.00f,-300.00f), GS::Graphics::Color4f_t(1.0f, 1.0f, 0.0f, 1.0f) );
		//g_font.renderText("The quick brown fox jumps over the lazy dog!@", GS::Graphics::Vector2_t(-800.00f,-600.00f), GS::Graphics::Color4f_t(0.0f, 1.0f, 0.0f, 1.0f) );
		}
		

		std::string test = "FPS: " + boost::lexical_cast<std::string>(1/dt);
		g_font.renderText(test, GS::Graphics::Vector2_t(-800.00f, 500.00f), GS::Graphics::Color4f_t(0.0f, 1.0f, 1.0f, 1.0f) );

*/
		g_window.swapBuffers();

		glfwPollEvents();
	}

	g_fontShaderProgram.shutdown();
	g_font.shutdown();

	// input has no shutdown
	// g_input.shutdown();
	g_window.shutdown();
	pTrash->shutdown();
	g_chunkman.shutdown();

	return 0;
}
