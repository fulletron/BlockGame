#ifndef _IINPUTLISTENERS_H_
#define _IINPUTLISTENERS_H_

#include "OgrePrerequisites.h"

union SDL_Event;
struct SDL_MouseButtonEvent;

struct SDL_TextInputEvent;
struct SDL_KeyboardEvent;

struct SDL_JoyButtonEvent;
struct SDL_JoyAxisEvent;
struct SDL_JoyHatEvent;

namespace OGraphics
{

class IMouseListener
{
public:
	//Receives SDL_MOUSEMOTION and SDL_MOUSEWHEEL events
	virtual void mouseMoved(const SDL_Event &arg) {}
	virtual void mousePressed(const SDL_MouseButtonEvent &arg, Ogre::uint8 id) {}
	virtual void mouseReleased(const SDL_MouseButtonEvent &arg, Ogre::uint8 id) {}
};

class IKeyboardListener
{
public:
	virtual void textInput(const SDL_TextInputEvent& arg) {}
	virtual void keyPressed(const SDL_KeyboardEvent &arg) {}
	virtual void keyReleased(const SDL_KeyboardEvent &arg) {}
};

class IJoystickListener
{
public:
	virtual void joyButtonPressed(const SDL_JoyButtonEvent &evt, int button) {}
	virtual void joyButtonReleased(const SDL_JoyButtonEvent &evt, int button) {}
	virtual void joyAxisMoved(const SDL_JoyAxisEvent &arg, int axis) {}
	virtual void joyPovMoved(const SDL_JoyHatEvent &arg, int index) {}
};

};

#endif