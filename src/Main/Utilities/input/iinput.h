#ifndef __IINPUT_H_
#define __IINPUT_H_

#include "../definitions_types.h"

namespace GS {
namespace Utilities {

/**
	Instantaneous Input is the only thing that is kept track of here.
*/
class IInput
{
public:
	/**
	* Setup the Input. call once ever.
	*/
	//virtual _UINT32 init(void) = 0;

	/**
	* Teardown the Input. call once ever.
	*/
	virtual _UINT32 shutdown(void) = 0;

	/**
	* The "Poll" command. Fills Input's internal deck with all current inputs
	* Call once per frame. This will push booleans from pressed->held->released
	*/
	virtual _UINT32 intake(void) = 0;

	/**
	* THIS PROBABLY SHOULDN'T BE USED. intake() needs to look at previous input
	* to push it from pressed->held->released
	*/
	//virtual _UINT32 clear(void) = 0;

	/**
	* Check Input's internal deck for the specific key press. 
	* returns TRUE if that input is found.
	*/
	virtual _BOOL isPressed(const _UINT32 &) const = 0;

	/**
	* Check Input's internal deck for the specific key held.
	* returns TRUE if that input is found.
	*/
	virtual _BOOL isHeld(const _UINT32 &) const = 0;

	/**
	* Check Input's internal deck for the specific key released.
	* returns TRUE if that input is found.
	*/
	virtual _BOOL isReleased(const _UINT32 &) const = 0;

	/**
	* Grabs the mouse movement in DOUBLE format. 
	* _UINT Param is for mouse move or scroll wheel.
	*/
	virtual _VEC2D<_DOUBLE> mouseMovement(const _UINT32 &) const = 0;

	/**
	* Grabs the analog stick tilt in DOUBLE format.
	* _UINT Param is for left or right analogue.
	*/
	virtual _VEC2D<_DOUBLE> analogMovement(const _UINT32 &) const = 0;
};

}
}

#endif