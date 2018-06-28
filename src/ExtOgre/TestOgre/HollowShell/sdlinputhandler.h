
//Thanks to Jordan Milne and Scrawl for allowing to use their
//sdlinputwrapper files as base under the MIT license

#ifndef _SDLINPUTHANDLER_H_
#define _SDLINPUTHANDLER_H_

#include "basesystem.h"
#include "OgrePrerequisites.h"
#include "sdlemulationlayer.h"

#if OGRE_USE_SDL2

#include <SDL.h>

namespace OGraphics
{
	class IMouseListener;
	class IKeyboardListener;
	class IJoystickListener;

	class SdlInputHandler
	{
		SDL_Window  *mSdlWindow;

		BaseSystem          *mGraphicsSystem;
		BaseSystem          *mLogicSystem;
		IMouseListener       *mMouseListener;
		IKeyboardListener    *mKeyboardListener;
		IJoystickListener    *mJoystickListener;

		// User settings
		/// User setting. From the SDL docs: While the mouse is in relative mode, the
		/// cursor is hidden, and the driver will try to report continuous motion in
		/// the current window. Only relative motion events will be delivered, the
		/// mouse position will not change.
		bool        mWantRelative;
		/// Locks the pointer to remain inside the window.
		bool        mWantMouseGrab;
		/// Whether to show the mouse.
		bool        mWantMouseVisible;

		// Describes internal state.
		bool        mIsMouseRelative;
		/// Used when driver doesn't support relative mode.
		bool        mWrapPointerManually;
		bool        mGrabPointer;
		bool        mMouseInWindow;
		bool        mWindowHasFocus;

		Uint16      mWarpX;
		Uint16      mWarpY;
		bool        mWarpCompensate;

		void updateMouseSettings(void);

		void handleWindowEvent(const SDL_Event& evt);

		/// Moves the mouse to the specified point within the viewport
		void warpMouse(int x, int y);

		/// Prevents the mouse cursor from leaving the window.
		void wrapMousePointer(const SDL_MouseMotionEvent& evt);

		/// Internal method for ignoring relative
		/// motions as a side effect of warpMouse()
		bool handleWarpMotion(const SDL_MouseMotionEvent& evt);

	public:
		SdlInputHandler(SDL_Window *sdlWindow,
			IMouseListener *mouseListener,
			IKeyboardListener *keyboardListener,
			IJoystickListener *joystickListener);
		virtual ~SdlInputHandler();

		void _handleSdlEvents(const SDL_Event& evt);

		/// Locks the pointer to the window
		void setGrabMousePointer(bool grab);

		/// Set the mouse to relative positioning mode (when not supported
		/// by hardware, we emulate the behavior).
		/// From the SDL docs: While the mouse is in relative mode, the
		/// cursor is hidden, and the driver will try to report continuous
		/// motion in the current window. Only relative motion events will
		/// be delivered, the mouse position will not change.
		void setMouseRelative(bool relative);

		/// Shows or hides the mouse cursor.
		void setMouseVisible(bool visible);

		// Sets the logic system to allow piping of input from graphics to logic
		void setLogicSystem(BaseSystem * logicSystem);

		// Sets the graphics system to help pipe along input
		void setGraphicsSystem(BaseSystem * graphicsSystem);
	};
}

#endif

#endif
