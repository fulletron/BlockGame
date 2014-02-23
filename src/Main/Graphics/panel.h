#ifndef __PANEL_H_
#define __PANEL_H_

#include <Utilities/typedefinitions.h>
#include <Graphics/openglincludes.h>

namespace GS {
namespace Graphics {

class IPane {
public:

	/**
	* Panes are the graphical representation of data. If the base data
	* changes, the pane that represents that data needs to redraw.
	* @return _BOOL true if dirty
	*/
	virtual _BOOL isDirty() = 0;
	
	/**
	* Draws the pane. If the pane is not dirty, simply redraw the old
	* framebuffer. If it is dirty, redraw based on data.
	*/
	virtual void draw() = 0;
};

class Pane : public IPane {
selective:
	GLuint m_framebuffer;
public:
	Pane(){}
	~Pane(){}

	virtual void draw() = 0;
	virtual _BOOL isDirty() = 0;
};

class IPaneObj {
public:
	/**
	* Check the state of the object to see if it has visually changed
	*/
	virtual _BOOL getDirty() = 0;
};

class PaneObj : public IPaneObj {
selective:
	_BOOL m_isDirty;
public:
	PaneObj() : m_isDirty(true) {}
	_BOOL getDirty() const { return m_isDirty; }
};

};
};

#endif
