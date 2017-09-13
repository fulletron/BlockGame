#ifndef __REFERENCER_H_
#define __REFERENCER_H_

#include <Graphics\window\window.h>
#include <Utilities\input\input.h>
#include <Utilities\time\time.h>
#include <Graphics/backloader/backloader.h>

namespace GS {
// THIS IS A LIST OF GAME SPECIFIC THINGS

	namespace Stage { class MainMachine; };


	class Referencer
	{
	public:
		GS::Graphics::IWindow * pWindow;
		GS::Utilities::ITime * pTime;
		GS::Utilities::IInput * pInput;
		GS::Backloader::Backloader * pBackloader;
		GS::Stage::MainMachine *pMainMachine;
	};
};

#endif