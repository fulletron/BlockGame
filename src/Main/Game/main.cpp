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

	while( g_isRunning && g_window.isOpen() )
	{

	}
	return 0;
}
