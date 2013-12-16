#include <iostream>

#include <Utilities/typedefinitions.h>
#include <Utilities/utilities.h>
#include <Graphics/graphics.h>

bool g_isRunning = false;

GS::Utilities::ChunkManager g_chunkman;
GS::Graphics::Window g_window;
GS::Utilities::Input g_input;

int main()
{
	g_isRunning = true;

	g_chunkman.init();
	g_window.init();
	g_input.init(&g_window);

	while( g_isRunning && g_window.isOpen())
	{
		double dt;
		do{ dt = glfwGetTime(); }
		while (dt < 0.16666);

		glfwSetTime(0.0);

		float ratio;
		int width, height;

		glfwGetFramebufferSize(g_window.getGLFWwindow(), &width, &height);
			
		ratio = width / (float) height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.6f, -0.4f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.6f, -0.4f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.6f, 0.f);
		glEnd();

		g_window.swapBuffers();

		glfwPollEvents();
	}

	g_window.shutdown();

	return 0;
}
