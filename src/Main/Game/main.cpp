#include <iostream>

#include <Utilities/typedefinitions.h>
#include <Utilities/utilities.h>
#include <Graphics/graphics.h>

bool g_isRunning = false;

GS::Utilities::ChunkManager g_chunkman;
GS::Graphics::Window g_window;
GS::Utilities::Input g_input;
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
    "}";

int main()
{
	g_isRunning = true;

	g_chunkman.init();
	g_window.init();
	g_input.init(&g_window);
	g_font.init();

	double tt = 0.0;


	/// ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

    //// Create Vertex Array Object
    //GLuint vao;
    //glGenVertexArrays(1, &vao);
    //glBindVertexArray(vao);

    //// Create a Vertex Buffer Object and copy the vertex data to it
    //GLuint vbo;
    //glGenBuffers(1, &vbo);

    //GLfloat vertices[] = {
    ////  Position           Texcoords
    //    -0.5f,  0.5f, 0.0f, 0.0f, // Top-left
    //     0.5f,  0.5f, 1.0f, 0.0f, // Top-right
    //     0.5f, -0.5f, 1.0f, 1.0f, // Bottom-right
    //    -0.5f, -0.5f, 0.0f, 1.0f  // Bottom-left
    //};

    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //// Create an element array
    //GLuint ebo;
    //glGenBuffers(1, &ebo);

    //GLuint elements[] = {
    //    0, 1, 2,
    //    2, 3, 0
    //};

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
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
	_CheckForErrors();

	/*
    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	*/

	/*
	GLuint tee;
    glGenTextures(1, &tee);

    int width, height;
    unsigned char* image;

    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tee );//g_font.m_texture);

    image = SOIL_load_image("./Internal/Resources/Textures/smallpanelbacking.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
	*/
	_CheckForErrors();

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
		while (dt < 0.016666);

		tt += dt;

		glfwSetTime(0.0);

		float ratio;
		int width, height;

		glfwGetFramebufferSize(g_window.getGLFWwindow(), &width, &height);
			
		ratio = width / (float) height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.22f,0.22f,0.22f,1.0f);

		/*
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef((float) tt * 50.f, 0.f, 0.f, 1.f);
		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.6f, -0.4f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.6f, -0.4f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.6f, 0.f);
		glEnd();
		*/

		// DRAW TEXTURE!
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		_CheckForErrors();

		glUseProgram(shaderProgram);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, g_font.m_texture);

		glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);

		_CheckForErrors();

		g_font.RenderText("I Was Spinning Free! WHOA!!", GS::Graphics::Vector2_t(-800.00f,-600.00f));
		//g_font.RenderText("W", GS::Graphics::Vector2_t(0.0f,70.0f));

		g_window.swapBuffers();

		glfwPollEvents();
	}

	g_window.shutdown();

	return 0;
}
