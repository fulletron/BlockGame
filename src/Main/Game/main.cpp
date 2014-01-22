#include <iostream>

#include <Utilities/typedefinitions.h>
#include <Utilities/utilities.h>
#include <Graphics/graphics.h>

bool g_isRunning = false;

GS::Utilities::ChunkManager g_chunkman;
GS::Graphics::Window g_window;
GS::Utilities::Input g_input;

// TODO ::
// This belongs somewhere else,
// but that somewhere else has not been
// implemented yet
GS::Graphics::Font g_font;


// Shader sources
const GLchar* vertexSource =
    "#version 150 core\n"
    "in vec2 position;"
    "in vec2 texcoord;"
	"in vec4 color;"
    "out vec2 Texcoord;"
	"out vec4 Color;"
    "void main() {"
	"	Color = color;"
    "   Texcoord = texcoord;"
    "   gl_Position = vec4(position, 0.0, 1.0);"
    "}";
const GLchar* fragmentSource =
    "#version 150 core\n"
    "in vec2 Texcoord;"
	"in vec4 Color;"
    "out vec4 outColor;"
    "uniform sampler2D tex;"
    "void main() {"
	"	float temp = texture2D(tex, Texcoord).r;"
	"	outColor = vec4(Color.r, Color.g, Color.b, temp);"
	//"	outColor = vec4(Color.r, Color.r, Color.r, Color.r);"
    "}";

_INT32 initTrashHeap()
{
	GS::Utilities::Frame * pTrash = 0;
	pTrash = g_chunkman.createFrame( FR_TRASH );
	pTrash->setfStop(TOP);
	pTrash->setfStop(BOT);
	return 0;
}

int main()
{
	g_isRunning = true;

	g_chunkman.init();
	initTrashHeap();

	g_window.init();
	g_input.init(&g_window);
	g_font.loadFile( "KaushanScript-Regular.otf", 16 );

	double tt = 0.0;


	/// ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

	GLint ret = 0;
    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &ret);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &ret);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_font.m_texture);

    glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	_CheckForErrors();

	/// [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[


	while( g_isRunning && g_window.isOpen() )
	{
		_CheckForErrors();

		double dt;
		do{ dt = glfwGetTime(); }
		while (dt < 0.016666); // cap the fps

		tt += dt;

		glfwSetTime(0.0);

		float ratio;
		int width, height;

		glfwGetFramebufferSize(g_window.getGLFWwindow(), &width, &height);
			
		ratio = width / (float) height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.22f,0.22f,0.22f,1.0f);

		_CheckForErrors();

		glUseProgram(shaderProgram);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, g_font.m_texture);

		glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);

		_CheckForErrors();

		g_font.renderText("The quick brown fox jumps over the lazy dog.", GS::Graphics::Vector2_t(-800.00f,-300.00f), GS::Graphics::Color4f_t(1.0f, 1.0f, 0.0f, 1.0f) );
		g_font.renderText("The quick brown fox jumps over the lazy dog!@", GS::Graphics::Vector2_t(-800.00f,-400.00f), GS::Graphics::Color4f_t(0.0f, 1.0f, 0.0f, 1.0f) );


		g_window.swapBuffers();

		glfwPollEvents();
	}

	g_window.shutdown();

	return 0;
}
