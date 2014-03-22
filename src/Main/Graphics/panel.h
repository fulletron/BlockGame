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

	/**
	* Panes handle input to minimize input effort.
	* TODO :: ACCEPT INPUT OF SOME FORM!
	* also have panes check for the kinds of input they accept
	* before collision!
	*/
	virtual _BOOL handleInput() = 0;

selective:
	virtual _UINT32 __glFramebufferInit() = 0;
	virtual void	__glFramebufferDestroy() = 0;
	virtual _UINT32 __glTexColorBufferInit() = 0;
	virtual void 	__glTexColorBufferDestroy() = 0;
	virtual _UINT32 __glRboDepthStencilInit() = 0;
	virtual void	__glRboDepthStencilDestroy() = 0;

};

class Pane : public IPane {
public:
	static const int CENTERED_X = 1 >> 0;
	static const int CENTERED_Y = 1 >> 1;
	static const int ORIGIN_TOP = 1 >> 2;
	static const int ORIGIN_LEFT = 1 >> 3;

selective:
	GLuint m_framebuffer;
	GLuint m_texColorBuffer;
	GLuint m_rboDepthStencil;
	Pane * m_pParentPane;
	Vec4D<float> m_boxBlueprint;
	Vec4D<_UINT32> m_boxActual;
	_CHAR m_orientationBitFlag;
public:
	Pane() : 
		m_framebuffer(0),
		m_texColorBuffer(0),
		m_rboDepthStencil(0),
		m_pParentPane(0),
		m_orientationBitFlag(0)
		{}

	~Pane(){}

	virtual void draw() = 0;
	virtual _BOOL isDirty() = 0;
	virtual _BOOL handleInput() = 0;

selective:
	_UINT32 __glFramebufferInit();
	void __glFramebufferDestroy();
	_UINT32 __glTexColorBufferInit();
	void __glTexColorBufferDestroy();
	_UINT32 __glRboDepthStencilInit();
	void __glRboDepthStencilDestroy(); 
};

class IPaneObj {
public:
	/**
	* Check the state of the object to see if it has visually changed
	*/
	virtual _BOOL getDirty() const = 0;
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
