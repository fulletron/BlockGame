#include <iostream>
#include <conio.h>

#include <Graphics\window\window.h>

GS::Graphics::IWindow * g_pWindow;
bool g_isRunning = false;

int main(int argc, char * argv[])
{
	g_isRunning = true;

	g_pWindow = new GS::Graphics::Window ();

	g_pWindow->init();

	//while (g_isRunning)
	//{
		std::cout << " TEST " << std::endl;
		_getch();
	//}

	g_pWindow->shutdown();
	delete g_pWindow;

	return 0;
}