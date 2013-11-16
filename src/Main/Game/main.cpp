#include <iostream>

#include <Utilities/typedefinitions.h>
#include <Utilities/utilities.h>
#include <Graphics/graphics.h>

bool g_isRunning = false;

GS::Graphics::Window g_window;

int main()
{
	GS::Utilities::BT::GSThread test;
	g_isRunning = true;

	g_window.init();

	while( g_isRunning && g_window.isOpen())
	{
			float ratio;
			int width, height;

			glfwGetFramebufferSize(g_window.m_pGLFWwindow, &width, &height);

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

			glfwSwapBuffers(g_window.m_pGLFWwindow);

			glfwPollEvents();
	}

	g_window.shutdown();

	return 0;
}
