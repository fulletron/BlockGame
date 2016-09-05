#include <iostream>
#include <chrono>


#include "Graphics/openglincludes.h"

//#include <Utilities/typedefinitions.h>
//#include <Utilities/utilities.h>
//#include <Graphics/graphics.h>

//#include "testpane.h"
//#include <Graphics/Panes/DebugPane/debugpane.h>
//#include "brain.h"
//#pragma warning( disable : 4005 )
//#include "gl/glew.h"
//#include <SDL/SDL_opengl.h>

//bool g_isRunning = false;

//GS::Graphics::Window g_window;
//GS::Utilities::Input g_input;
//GS::Graphics::ResourceLibrary g_lib;


int main(int argc, char * argv[])
{
	int error = 0;
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	//SDL_Window * window = SDL_CreateWindow("TEST!", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
	SDL_Window * window = SDL_CreateWindow("TEST!", 100, 100, 1920, 1080, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	glewExperimental = true;
	glewInit();
	error = glGetError();

	/////////////////////// BEGIN

	/*
	// VERTEX DECL ///////////////////
	// POS2v, COLOR3v
	float vertices[] = {
		// POSITION,	COLOR,		TEXCOORDS
		-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Vertex 1 (TOP LEFT)
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Vertex 1 (TOP RIGHT)
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Vertex 2 (BOT RIGHT)
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f // Vertex 3 (BOT LEFT)
	};
	*/

	float testval = 1.0f;

	// VERTEX DECL ///////////////////
	// POS2v, COLOR3v
	float vertices[] = {
		// POSITION,	COLOR,		TEXCOORDS
		-testval, testval, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Vertex 1 (TOP LEFT)
		testval, testval, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Vertex 1 (TOP RIGHT)
		testval, -testval, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Vertex 2 (BOT RIGHT)
		-testval, -testval, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f // Vertex 3 (BOT LEFT)
	};


	GLuint vbo;
	glGenBuffers(1, &vbo);
	error = glGetError();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// GL_STATIC_DRAW (NEVER CHANGE), GL_DYNAMIC_DRAW (SOMETIMES), GL_STREAM_DRAW (EVERYTIME)
	error = glGetError();
	//////////////////////////////

	// TEXTURE DECL
	GLuint tex;
	glGenTextures(1, &tex);
	error = glGetError();
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
	error = glGetError();

	// IF GL_CLAMP_TO_BORDER is set
	//float texcolor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, texcolor);
	////////////////////////////////////////////////////////////

	int width, height;
	unsigned char* image =
		//SOIL_load_image( "./Debug/Internal/Resources/Textures/sample.png", &width, &height, 0, SOIL_LOAD_RGBA);
		SOIL_load_image("./Debug/Internal/Resources/Textures/sample3.png", &width, &height, 0, SOIL_LOAD_RGBA);
	error = glGetError();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	error = glGetError();
	SOIL_free_image_data(image);


	// SOURCE FOR SHADERS /////////////////////////////////////
	static const char * srcVert[] =
	{
		"#version 150									\n"
		"in vec2 position;								\n"
		"in vec3 color;									\n"
		"in vec2 texcoord;								\n"
		"out vec3 Color;								\n"
		"out vec2 Texcoord;								\n"
		"												\n"
		"void main()									\n"
		"{												\n"
		"	Texcoord = texcoord;						\n"
		"	Color = color;								\n"
		"	gl_Position = vec4(position, 0.0, 1.0);		\n"
		"}												\n"
	};

	static const char * srcFrag[] =
	{
		"#version 150									\n"
		"in vec3 Color;									\n"
		"in vec2 Texcoord;								\n"
		"out vec4 outColor;								\n"
		"uniform sampler2D tex;							\n"
		"												\n"
		"void main()									\n"
		"{												\n"
		"    outColor = texture(tex, Texcoord) * vec4(Color, 1.0);				\n"
//		"    outColor =  vec4(Color, 1.0);				\n"
		"}												\n"
	};
	//"uniform vec3 triangleColor;					\n"
	// outColor = vec4(triangleColor, 1.0);
	//////////////////////////////////////////////

	// SHADER DECL ///////////////////////////////////
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, srcVert, NULL);
	glCompileShader(vertexShader);
	error = glGetError();
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, srcFrag, NULL);
	glCompileShader(fragmentShader);
	error = glGetError();
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	error = glGetError();
	glBindFragDataLocation(shaderProgram, 0, "outColor");

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	error = glGetError();

	//GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
	//glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);
	///////////////////////////////////////////////////////////////

	GLuint vao;
	glGenVertexArrays(1, &vao);
	error = glGetError();
	glBindVertexArray(vao);
	error = glGetError();

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	error = glGetError();
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
	error = glGetError();
	glEnableVertexAttribArray(posAttrib);
	error = glGetError();

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	error = glGetError();
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	error = glGetError();
	glEnableVertexAttribArray(colAttrib);
	error = glGetError();

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	error = glGetError();
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	error = glGetError();
	glEnableVertexAttribArray(texAttrib);
	error = glGetError();

	GLuint elements[] = { 
		0, 1, 2,
		2, 3, 0 
	};

	GLuint ebo;
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(elements), elements, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	error = glGetError();

	//GLuint vertexBuffer;
	//glGenBuffers(1, &vertexBuffer);
	//printf("%u\n", vertexBuffer);

	///////////////////// END

	//auto t_start = std::chrono::high_resolution_clock::now();

	SDL_Event windowEvent;
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
				break;
			if (windowEvent.type == SDL_KEYUP
				&& windowEvent.key.keysym.sym == SDLK_ESCAPE)
				break;
		}
		//auto t_now = std::chrono::high_resolution_clock::now();
		//float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		//glUniform3f(uniColor, (sin(time*4.0f) + 1.0f)/2.0f, 0.0f, 0.0f);

		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		SDL_GL_SwapWindow(window);
	}

	SDL_Delay(1000);

	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;
}

/*
int main3(int argc, char * argv[])
{
	int error = 0;
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_Window * window = SDL_CreateWindow("TEST!", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	glewExperimental = true;
	glewInit();
	error = glGetError();

	/////////////////////// BEGIN

	// WITHOUT COLOR
	//float vertices[] = {
	//	0.0f, 0.5f, // Vertex 1 (TOP)
	//	0.5f, -0.5f, // Vertex 2 (BOT RIGHT)
	//	-0.5f, -0.5f // Vertex 3 (BOT LEFT)
	//};

	// POS2v, COLOR3v
	float vertices[] = {
		0.0f, 0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1 (TOP)
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2 (BOT RIGHT)
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f // Vertex 3 (BOT LEFT)
	};


	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// GL_STATIC_DRAW (NEVER CHANGE), GL_DYNAMIC_DRAW (SOMETIMES), GL_STREAM_DRAW (EVERYTIME)
	error = glGetError();
	static const char * srcVert[] =
	{
		"#version 150									\n"
		"in vec2 position;								\n"
		"in vec3 color;									\n"
		"out vec3 Color;								\n"
		"												\n"
		"void main()									\n"
		"{												\n"
		"	Color = color;								\n"
		"	gl_Position = vec4(position, 0.0, 1.0);		\n"
		"}												\n"
	};

	static const char * srcFrag[] =
	{
		"#version 150									\n"
		"in vec3 Color;									\n"
		"out vec4 outColor;								\n"
		"												\n"
		"void main()									\n"
		"{												\n"
		"    outColor = vec4(Color, 1.0);				\n"
		"}												\n"
	};
	//"uniform vec3 triangleColor;					\n"
	// outColor = vec4(triangleColor, 1.0);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, srcVert, NULL);
	glCompileShader(vertexShader);
	error = glGetError();
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, srcFrag, NULL);
	glCompileShader(fragmentShader);
	error = glGetError();
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	error = glGetError();
	glBindFragDataLocation(shaderProgram, 0, "outColor");

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	error = glGetError();

	GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
	glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	error = glGetError();
	glBindVertexArray(vao);
	error = glGetError();

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	error = glGetError();
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	error = glGetError();
	glEnableVertexAttribArray(posAttrib);
	error = glGetError();

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	error = glGetError();
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	error = glGetError();
	glEnableVertexAttribArray(colAttrib);
	error = glGetError();

	GLuint elements[] = { 0, 1, 2 };

	GLuint ebo;
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(elements), elements, GL_STATIC_DRAW);

	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	error = glGetError();

	//GLuint vertexBuffer;
	//glGenBuffers(1, &vertexBuffer);
	//printf("%u\n", vertexBuffer);

	///////////////////// END

	//auto t_start = std::chrono::high_resolution_clock::now();

	SDL_Event windowEvent;
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
				break;
			if (windowEvent.type == SDL_KEYUP
				&& windowEvent.key.keysym.sym == SDLK_ESCAPE)
				break;
		}
		//auto t_now = std::chrono::high_resolution_clock::now();
		//float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		//glUniform3f(uniColor, (sin(time*4.0f) + 1.0f)/2.0f, 0.0f, 0.0f);

		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		SDL_GL_SwapWindow(window);
	}

	SDL_Delay(1000);

	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;
}
*/
//int main2()
//{
	// Global window and global input, both
	// will only ever exist once
	//g_window.init();
	//_CheckForErrors();

	//g_lib.init();
	//g_input.init();
	
	//GS_ASSERT ( false, _CheckForErrors(), -1 );

	// For now, the game states do not exist
	// instead, i have this one pane (states are groupings
	// of panes)
	//GS::Graphics::DebugPane debugPane;
	//debugPane.init(0);
	//GS::Game::Brain * brain = &GS::Game::Brain::getInstance();
	//brain->init();
	//s_brain = &brain;
	// checks for gl and glfw errors!
	//if ( _CheckForErrors() )
	//	return -1;
/*
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
		//do{ dt = glfwGetTime(); } // TODO :: something more productive
		//while (0); // cap the fps
		while (dt < FPS_CAP_MS); // cap the fps

		// gdb update?
		tt += dt;

		//glfwSetTime(0.0);

		//fpsCounter.update(dt);
		//brain->update(dt);

		GS_ASSERT(false, _CheckForErrors(), -1);

		// all of this is placeholder until pane/state are implemeneted

		float ratio;
		int width, height;

		/*


		glfwGetFramebufferSize(g_window.getGLFWwindow(), &width, &height);
			
		ratio = width / (float) height;
		glViewport(0, 0, width, height);
		//glBindFramebuffer(GL_FRAMEBUFFER, g_window.getFramebuffer() );
		glBindFramebuffer(GL_FRAMEBUFFER, 0 );
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
*/
		/*

		GS_ASSERT(false, _CheckForErrors(), -1);

		debugPane.update(dt);

		GS_ASSERT(false, _CheckForErrors(), -1);

		debugPane.draw( &g_window );

		GS_ASSERT(false, _CheckForErrors(), -1);
		*//*
		g_window.swapBuffers();
		//glfwPollEvents();

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