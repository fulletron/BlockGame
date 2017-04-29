#include <iostream>
#include <conio.h>

#include <Utilities/definitions_values.h>

#include <Graphics\window\window.h>
#include <Utilities\input\input.h>
#include <Utilities\time\time.h>

#include "stage/allstage.h"

GS::Graphics::IWindow * g_pIWindow;
GS::Graphics::Window * g_pWindow;

GS::Utilities::ITime * g_pTime;

GS::Utilities::IInput * g_pInput;

int main(int argc, char * argv[])
{
	g_pWindow = new GS::Graphics::Window ();
	g_pIWindow = g_pWindow;
	g_pIWindow->init();

	g_pTime = new GS::Utilities::Time ();
	g_pTime->init();

	g_pInput = new GS::Utilities::Input ();
	g_pInput->init();

	GS::Stage::AllStage * pAllStage = new GS::Stage::AllStage();

	pAllStage->init();

	while (pAllStage->isRunning())
	{
		while (g_pTime->checkDeltaTime() < FPS_CAP_MS){};

		g_pTime->updateInternalValues();

		g_pInput->intake();
		pAllStage->update();
	}

	g_pTime->shutdown();

	g_pInput->shutdown();

	g_pWindow->shutdown();
	delete g_pWindow;

	return 0;
}