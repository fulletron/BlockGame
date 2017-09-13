#include <iostream>
#include <conio.h>

#include <Utilities/definitions_values.h>

// MASTER REFERENCER
#include <Framework/referencer/referencer.h>
#include <Game/stages/mainmachine.h>

// BRAIN:::

// LONG TERM MEMORY
// Things that persist once throughout the "Play" state has begun
  // My inventory
  // My Character
  // My Progression
// The server might not ever care about this stuff, but in the event
// of ever possibly having "Inspect", keep it an option.
// HGL: possibly inspect
// 40k: inspect at the battlenet menu level, like a win/loss ratio, stats
// CTF: I can't think of a reason for this one.
// WHEN THEN???: Most specifically, the server will care when dedicated serverness is a thing.
// If like a pubg, mostly everything would be short term

// SHORT TERM MEMORY
// Things that die everytime a new area is loaded
  // Monsters
  // NPC's
  // Other Players
// The server will always care about this stuff
// HGL: Most combat elements
// 40k: The map seed, cover, where units/models are
// CTF: Once again, tough

// CLIENT
// Will only ever send messages to the "Server" local queue,
// or to the "Net" object to send out.
// Get seed to build map
// Interpret input (like movement, attacks)
  // send that to server
// Keep local track of where the entities are

// SERVER
// Will only ever send messages to the "Client" local queue,
// or to the "Net" object to send out.
// Decide a seed to generate a map
// Quests/Objectives of any players subject to the map
// Keep track of enemy health, player information.
// Create/Destroy enemies, send to client
// Decide how the enemies will behave, send to client
// Keep track of which main quest(s)
// Inventory information? (sometimes).

// NET

// SOUNDER

// RENDERER, WORLD
// RENDERER, UI

int main(int argc, char * argv[])
{
	GS::Referencer ref;

	GS::Graphics::Window * pWindow = new GS::Graphics::Window();
	pWindow->init();
	ref.pWindow = pWindow;

	GS::Utilities::ITime * pTime = new GS::Utilities::Time();
	pTime->init();
	ref.pTime = pTime;

	GS::Utilities::Input * pInput = new GS::Utilities::Input();
	pInput->init(pWindow);
	ref.pInput = pInput;

	GS::Backloader::Backloader * pBackloader = new GS::Backloader::Backloader();
	pBackloader->init(pWindow);
	ref.pBackloader = pBackloader;

	GS::Stage::MainMachine * pMainMachine = new GS::Stage::MainMachine();
	pMainMachine->init(&ref);
	ref.pMainMachine = pMainMachine;

	//std::srand(1);
	//DEBUG_OUT(std::rand());
	//DEBUG_OUT(std::rand());
	//DEBUG_OUT(std::rand());

	while (pMainMachine->isRunning())
	{
		while (pTime->checkDeltaTime() < FPS_CAP_MS){ std::this_thread::yield(); };

		pTime->updateInternalValues();
		pBackloader->joinFinishedThreads();

		// DRAW
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		pWindow->swapBuffers();

		// INPUT
		pInput->intake();

		// UPDATE
		pMainMachine->update();
	}

	pMainMachine->shutdown();
	pBackloader->shutdown();
	pInput->shutdown();
	pTime->shutdown();
	pWindow->shutdown();

	delete pMainMachine;
	delete pBackloader;
	delete pInput;
	delete pTime;
	delete pWindow;

	return 0;
}