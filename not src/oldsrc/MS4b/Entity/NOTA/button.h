#ifndef __BUTTON_H_
#define __BUTTON_H_

#include "entity.h"
#include "..\..\Game\definitions.h"

namespace GS { class Game;
namespace ResourceNS{ class Resource; };
namespace EntityNS {
	struct Builder_Button
	{
		Builder_Button(
		wchar_t *		a_buttonSays,
		_UINT32			a_resourceKey,
		_2DFLOATVEC		a_posPerc,
		_2DFLOATVEC		a_baseScale)
		{
			buttonSays =	a_buttonSays;
			resourceName =	a_resourceKey;
			posPerc =		a_posPerc;
			baseScale =		a_baseScale;
		}

		wchar_t *		buttonSays;
		_UINT32			resourceName;
		_2DFLOATVEC		posPerc;
		_2DFLOATVEC		baseScale;
	};

	class Button : public Entity2D
	{
	private:
		GS::Game *					m_rpGame;
		ResourceNS::Resource *		m_rpResourceFont;
		ResourceNS::Resource *		m_rpResourceTexture;

		_2DFLOATVEC					m_buttonDimensions;

		bool						m_active;
		wchar_t *					m_pButtonSays;
		_UINT32						m_selected;

		float						m_breatheStep;
		_2DFLOATVEC					m_breatheScale;

	public:
		Button()
		: m_rpGame(0), m_rpResourceFont(0), m_rpResourceTexture(0),
		m_buttonDimensions(0.0f,0.0f), m_active(false), m_pButtonSays(0),
		m_selected(0), m_breatheStep(0.0f), m_breatheScale(0.0f,0.0f)
		{}
		~Button(){}

		_UINT32 init(GS::Game * const a_rpGame, void const * const a_data);
		void update(_DOUBLE a_dt);
		void draw();
		void shutdown();
		bool input(const GS::InputNS::Input & a_input, bool & a_moDone, bool & a_kbDone);
		void onScreenResize();
		void entityRescale();


		wchar_t * getButtonSays(){return m_pButtonSays;}
		void resetScale();

		// IUF BREATHE
		//_UINT32 getBreatheStepFreq();
		//void breatheupdate(_DOUBLE dt);
	};
};
};

#endif