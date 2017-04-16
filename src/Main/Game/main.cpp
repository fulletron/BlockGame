#include <iostream>
#include <conio.h>

#include <Graphics\window\window.h>
#include <Utilities\input\input.h>
#include "overstate/overstate.h"

GS::Graphics::IWindow * g_pIWindow;
GS::Graphics::Window * g_pWindow;


GS::Utilities::IInput * g_pInput;

int main(int argc, char * argv[])
{
	g_pWindow = new GS::Graphics::Window ();
	g_pIWindow = g_pWindow;
	g_pIWindow->init();

	g_pInput = new GS::Utilities::Input ();
	g_pInput->init();

	GS::State::OverState * pOverState = new GS::State::OverState();

	pOverState->init();

	while (pOverState->isRunning())
	{
		g_pInput->intake();
		pOverState->update();
	}

	g_pWindow->shutdown();
	delete g_pWindow;

	return 0;
}