#include <iostream>

#define GLEW_STATIC
#include "gl/glew.h"
#include "gl/GL.h"
#pragma warning( disable : 4005 )

#include "GLFW/glfw3.h"
#include "SOIL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ft2build.h"
#include "freetype/freetype.h"
#include "freetype/ftglyph.h"
#include FT_FREETYPE_H

#include <fstream>
#include <sstream>
//#include <Windows.h>

const char * vs = "#version 150\r\n\
in vec2 position;\r\n\
in vec3 color;\r\n\
in vec2 texcoord;\r\n\
out vec3 Color;\r\n\
out vec2 Texcoord;\r\n\
void main()\r\n\
{\r\n\
Texcoord = texcoord;\r\n\
Color = color;\r\n\
gl_Position = vec4(position, 0.0, 1.0);\r\n\
}";

const char * fsNOCOLOR = "#version 150 \r\n\
				  uniform vec3 triangleColor;\r\n\
				  out vec4 outColor;\r\n\
				  void main()\r\n\
				  {\r\n\
				  outColor = vec4(triangleColor,1.0);\r\n\
				  }";

const char * fs = "#version 150 \r\n\
in vec3 Color;\r\n\
in vec2 Texcoord;\r\n\
out vec4 outColor;\r\n\
uniform sampler2D tex;\r\n\
void main()\r\n\
{\r\n\
outColor = texture(tex, Texcoord) * vec4(Color, 1.0); \r\n\
}";

std::string loadFile(const char *fname)
{
	std::ifstream file(fname);
	if (!file.is_open())
	{
		return "";
	}

	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();

	return fileData.str();
}

int main(int argc, char * argv[])
{
	int error = 0;

/// GLFW init
	glfwInit();

/// GLFW window init
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
	//GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	glewInit();

	///
	float vertices[] = {
		//  Position      Color             Texcoords
		-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
	};

	// ELEMENTS
	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0 };

/// VERTEXT BUFFERS?
	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// Shaders
	GLint status = GL_FALSE;
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vs, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fs, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// FRAGMENT SHADER is allowed to write to multiple buffers, but 0 is default && there is only one output.
	glBindFragDataLocation(shaderProgram, 0, "outColor");

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// VAO will save any subsequent glVertexAttrib stuff. Binding it first to write to it. Bind it again to restore whatever was last written.
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Making a link between vertex data and attributes
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(colAttrib);

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));


	// UNIFORMS!
	//GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
	//glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

	// ELEMENT BUFFER
	GLuint ebo;
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// GL TEXTURE SETUP
	GLuint tex;
	glGenTextures(1, &tex);

	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	float color[] = { 1.0f, 0.0f, 0.0f, 0.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	// Black/white checkerboard test image
	//float pixels[] = {
	//	0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
	//};
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);

	// SOIL LOAD
	int width, height;
	unsigned char* image =
		SOIL_load_image("C:\\Projects\\Standalones\\GLFW_Test\\Debug\\Textures\\sample.png", &width, &height, 0, SOIL_LOAD_RGB);
//	SOIL_load_image("sample.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);


	// LOOP
	while (!glfwWindowShouldClose(window))
	{
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	std::cout << "Hello World!" << std::endl;

	return 0;
}

/*
#include <iostream>

#define GLEW_STATIC
#include "gl/glew.h"
#include "gl/GL.h"
#pragma warning( disable : 4005 )

#include "GLFW/glfw3.h"
#include "SOIL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ft2build.h"
#include "freetype/freetype.h"
#include "freetype/ftglyph.h"
#include FT_FREETYPE_H

#include <fstream>
#include <sstream>
//#include <Windows.h>

const char * vs = "#version 150\r\n\
in vec2 position;\r\n\
in vec3 color;\r\n\
out vec3 Color;\r\n\
void main()\r\n\
{\r\n\
Color = color;\r\n\
gl_Position = vec4(position, 0.0, 1.0);\r\n\
}";

const char * fsNOCOLOR = "#version 150 \r\n\
uniform vec3 triangleColor;\r\n\
out vec4 outColor;\r\n\
void main()\r\n\
{\r\n\
outColor = vec4(triangleColor,1.0);\r\n\
}";

const char * fs = "#version 150 \r\n\
in vec3 Color;\r\n\
out vec4 outColor;\r\n\
void main()\r\n\
{\r\n\
outColor = vec4(Color,1.0);\r\n\
}";

std::string loadFile(const char *fname)
{
std::ifstream file(fname);
if (!file.is_open())
{
return "";
}

std::stringstream fileData;
fileData << file.rdbuf();
file.close();

return fileData.str();
}

int main(int argc, char * argv[])
{
int error = 0;

/// GLFW init
glfwInit();

/// GLFW window init
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
//GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen

glfwMakeContextCurrent(window);

glewExperimental = true;
glewInit();

/// defining vertices
float verticesNOCOLOR[] = {
0.0f, 0.5f,
0.5f, -0.5f,
-0.5f, -0.5f
};

/// defining vertices
float verticesTRIANGLE[] = {
0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.0f, 0.0f, 1.0f
};

/// defining vertices
float vertices[] = {
-0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
-0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
};

// ELEMENTS
GLuint elements[] = {
0, 1, 2,
2, 3, 0 };

/// VERTEXT BUFFERS?
GLuint vbo;
glGenBuffers(1, &vbo);

glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// Shaders
GLint status = GL_FALSE;
GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

glShaderSource(vertexShader, 1, &vs, NULL);
glCompileShader(vertexShader);
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fs, NULL);
glCompileShader(fragmentShader);
glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

GLuint shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);

// FRAGMENT SHADER is allowed to write to multiple buffers, but 0 is default && there is only one output.
glBindFragDataLocation(shaderProgram, 0, "outColor");

glLinkProgram(shaderProgram);
glUseProgram(shaderProgram);

// VAO will save any subsequent glVertexAttrib stuff. Binding it first to write to it. Bind it again to restore whatever was last written.
GLuint vao;
glGenVertexArrays(1, &vao);
glBindVertexArray(vao);

// Making a link between vertex data and attributes
GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
glEnableVertexAttribArray(posAttrib);

GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));
glEnableVertexAttribArray(colAttrib);

// UNIFORMS!
//GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
//glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

// ELEMENT BUFFER
GLuint ebo;
glGenBuffers(1, &ebo);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

// LOOP
while (!glfwWindowShouldClose(window))
{
//glDrawArrays(GL_TRIANGLES, 0, 3);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
glfwSetWindowShouldClose(window, GL_TRUE);
glfwSwapBuffers(window);
glfwPollEvents();
}

glfwTerminate();

std::cout << "Hello World!" << std::endl;

return 0;
}
*/

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