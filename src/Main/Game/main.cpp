#include <iostream>
#include <conio.h>

#include <Graphics\window\window.h>

GS::Graphics::IWindow * g_window;
bool g_isRunning = false;

int main(int argc, char * argv[])
{
	g_isRunning = true;

#ifdef USING_GLFW
	g_window = new GS::Graphics::Window_GLFW ();
#else
	g_window = 0;
#endif

	g_window->init();

	//while (g_isRunning)
	//{
		std::cout << " TEST " << std::endl;
		_getch();
	//}

	g_window->shutdown();
	delete g_window;

	return 0;
}