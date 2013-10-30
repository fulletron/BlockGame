#include <iostream>

#include <Graphics/graphics.h>

bool g_isRunning = false;

GS::Graphics::Window g_window;

int main()
{
	g_isRunning = true;

	while( g_isRunning && g_window.isOpen() )
	{

	}
	return 0;
}
