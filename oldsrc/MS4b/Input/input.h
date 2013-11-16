#ifndef __INPUT_H_
#define __INPUT_H_

#include <Game\definitions.h>
#include <Graphics\openglincludes.h>
#include "eventbuffer.h"

namespace GS { class Game;
namespace InputNS
{
	struct InpKeyboard
	{
		char								keyState[256];
	};

	struct InpMouse
	{
		_2DFLOATVEC							mousePos;
		char								mouseButton[8];
	};

	class Input
	{
	private:
		Game *								m_pGame;

		sf::Keyboard						m_sfKeyboard;
		sf::Mouse							m_sfMouse;

		InpKeyboard							m_keyboard;
		InpMouse							m_mouse;			

		bool								m_moDone;
		bool								m_kbDone;

		void __grabKeyboard();
		void __grabMouse();

	public:
		_UINT32 init(GS::Game * const a_g);
		void grabInput();
		void setMousePos(const int &, const int &);
		void resetInput();
		void shutdown();

		void resetHandlingInput(){m_moDone = false; m_kbDone = false;}
		bool kbIsProcessable(){return !m_kbDone;}
		bool moIsProcessable(){return !m_moDone;}
		bool hasInputBeenProcessed(){if(m_moDone && m_kbDone){return true;}else{return false;}}

		InpKeyboard * getKeyboard(){return &m_keyboard;}
		InpMouse * getMouse(){return &m_mouse;}

		_2DFLOATVEC getMousePos();
	};
};
};
#endif