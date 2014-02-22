#ifndef __PANEL_H_
#define __PANEL_H_

#include <Utilities/typedefinitions.h>

namespace GS {
namespace Graphics {

class IPane {
public:
	/**
	* Panes must be optionally visible
	* @return _BOOL true if visible
	*/
	virtual _BOOL isVisible() = 0;

	/**
	* Panes are the graphical representation of data. If the base data
	* changes, the pane that represents that data needs to redraw.
	* @return _BOOL true if dirty
	*/
	virtual _BOOL isDirty() = 0;

	/**
	* This function is only to be used by IPaneObj
	* It allows for a way to have actual data tell the Pane that it has
	* changed.
	*/
	virtual void makeDirty() = 0;
	
	/**
	* Draws the pane. If the pane is not dirty, simply redraw the old
	* framebuffer. If it is dirty, redraw based on data.
	*/
	virtual void draw() = 0;
};

class IPaneObj {
public:
	/**
	* Tell all subscribing panes that this object has changed
	*/
	virtual void setDirty() = 0;
};

};
};

#endif
