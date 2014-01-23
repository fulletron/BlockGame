#ifndef __WINDOW_H_
#define __WINDOW_H_

#include "..\..\game\definitions.h"
#include "openglincludes.h"

namespace GS
{
	class Game;

	namespace WindowNS
	{
		class Window;

		_RECT<_INT32> GetPXRectFromWindow(GS::WindowNS::Window * const a_pBW,
								const ALIGNMENT & a_alignment, 
								const _RECT<_FLOAT> & a_slice);

		_RECT<_INT32> GetPXRectFromWindow(GS::Game * const a_rpGame,
								const ALIGNMENT & a_alignment, 
								const _RECT<_FLOAT> & a_slicePosCov);

		_RECT<_INT32> GetPXRectFromRect(const _RECT<_FLOAT> & a_slicePosCov, 
								const ALIGNMENT & a_sliceAlignment, 
								const _RECT<_INT32> & a_pxFrame);
		/*
		class Screen
		{
			_RECT<_FLOAT>			m_relPosCov;
			ALIGNMENT				m_relAlignment;

			_RECT<_INT32>			m_pxRect;
		};
		*/

		struct Screen 
		{
			ALIGNMENT				m_relAlignment;
			_RECT<_FLOAT>			m_relPosCov;
			_RECT<_INT32>			m_pxRect;

			void set(const _RECT<_INT32> & a_windowDimensions, const _RECT<_FLOAT> & a_relPosCov, const ALIGNMENT & a_relAlignment)
			{
				m_relAlignment = a_relAlignment;
				m_relPosCov = a_relPosCov;
				m_pxRect = a_windowDimensions;
			}
			
			void set(Screen * const a_pParentScreen, const _RECT<_FLOAT> & a_relPosCov, const ALIGNMENT & a_relAlignment)
			{
				m_relAlignment = a_relAlignment;
				m_relPosCov = a_relPosCov;
				m_pxRect = GetPXRectFromRect(a_relPosCov,a_relAlignment, a_pParentScreen->m_pxRect);
			}
		};

		class Window
		{
		private:
			GS::Game *					m_rpGame;

			bool						m_bWindowed;
			bool						m_bVsync;

			Screen						m_windowScreen;

			static bool					sm_needsWindowRefresh;
			static GLint				_maintainAspectRatio(GLint a_width, GLint a_height);
			static void GLFWCALL		_windowResizeFunction(GLint a_width, GLint a_height);
		public:
			static bool		needsRefresh(){return sm_needsWindowRefresh;}

			_UINT32			init(GS::Game * const a_pGame);
			void			shutdown();
			void			retainWindowIntegrity();

			GET_ACCESSOR(		bool,		m_bWindowed				);
			GETP_ACCESSOR(		Screen,		m_windowScreen			);
			GETRP_ACCESSOR(		GS::Game,	m_rpGame				);
		};

		/*
		_RECT<_INT32>	GetRectSlice(
							GS::Game * const a_pG,
							const ALIGNMENT & a_alignment, 
							const _RECT<_FLOAT> & a_slice);

		_RECT<_INT32>	GetRectSlice(
							Window * const a_pBW,
							const ALIGNMENT & a_alignment, 
							const _RECT<_FLOAT> & a_slice, 
							const _RECT<_INT32> & a_frame);

		/// WILL THIS EVER NEED THE BOOL CENTERIZED???????????
		_RECT<_INT32>	GetSliceOfSlice(
							_INT32 a_slicePX, 
							_INT32 a_slicePY, 
							_FLOAT a_stepX, 
							_FLOAT a_stepY, 
							_INT32 a_totalCountX, 
							_INT32 a_totalCountY, 
							_FLOAT a_coverageX, 
							_RECT<_INT32> a_frame); 
		*/
	};

};

#endif