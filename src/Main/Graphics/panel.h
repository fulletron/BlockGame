#ifndef __PANEL_H_
#define __PANEL_H_

#include <Utilities/typedefinitions.h>
#include <Graphics/openglincludes.h>

namespace GS {
namespace Graphics {

class FontResource;
class ShaderProgramResource;
class TextureResource;
class MeshResource;
class Pane;

class IDimensionable {
public:
	virtual Vec2D<_INT32> getPixelDimensions() const = 0;
	//virtual GLuint getFramebuffer() const = 0;
};

class IPaneAsset {
public:
	/**
	* init the paneasset resources
	*/
	virtual _INT32 init( Pane * const a_pParent ) = 0;

	/**
	* Check the state of an object to see if it needs to be redrawn
	*/
	virtual _BOOL isDirty() const = 0;

	/**
	* Tells the PaneAsset to clean up
	*/ 
	virtual void shutdown() = 0;

	/**
	* Draws the PaneAsset.
	*/
	virtual void draw( GS::Graphics::IDimensionable * const a_dims ) = 0;

	/**
	* Determines how to handle input for the PaneAsset
	*/
	virtual _BOOL handleInput() = 0;

	/**
	* Updates the PaneAsset by dt.
	*/
	virtual void update(const _DOUBLE a_dt) = 0;
};


class Pane;
class IPane : public IPaneAsset, public IDimensionable {
public:
	/**
	* Panes are the graphical representation of data. If the base data
	* changes, the pane that represents that data needs to redraw.
	* WILL PROPOGATE TO ALL PaneAssets.
	* @return _BOOL true if dirty
	*/
	virtual _BOOL isDirty() const = 0;
	
	/**
	* Draws the pane.
	* This will call isDirty(), which
	* WILL PROPOGATE TO ALL PaneAssets.
	*/
	virtual void draw( GS::Graphics::IDimensionable * const a_dims ) = 0;

	/**
	* Panes handle input to minimize input effort.
	* TODO :: ACCEPT INPUT OF SOME FORM!
	* also have panes check for the kinds of input they accept
	* before collision!
	* WILL PROPOGATE TO ALL PaneAssets.
	*/
	virtual _BOOL handleInput() = 0;

	/**
	* Sets the parent pane and calculates the actual dimensions.
	*/
	virtual _INT32 initBlueprints( const Vec4D<float> & a_blueprint ) = 0;

	/**
	* Updates the Pane.
	* WILL PROPOGATE TO ALL PaneAssets.
	*/ 
	virtual void update(const _DOUBLE a_dt) = 0;

	/**
	* Tells this pane to prepare to shutdown.
	* WILL PROPOGATE TO ALL PaneAssets.
	*/
	virtual void shutdown() = 0;

	/**
	* Get the dimensions of the given IDimensionable 
	* (IPane, in this case)
	*/
	virtual Vec2D<_INT32> getPixelDimensions() const = 0;

	/**
	* Get the Pane's framebuffer.
	*/
//	virtual GLuint getFramebuffer() const = 0;

selective:

	// ALSO, I MAY WANT ACCESS TO THESE TO DO CERTAIN THINGS
privatized:
	/**
	* Calls all of the __gl private functions that setup the framebuffer
	*/
	virtual _UINT32 __initFramebuffer() = 0;

	virtual _INT32 __calculateDimActual() = 0;
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

	static GS::Graphics::Pane * NO_PARENT;

selective:
	static _BOOL m_screenLoaded;
//	static GLuint m_vaoQuad;
//	static GLuint m_vboQuad;

//	GLuint m_framebuffer;
//	GLuint m_texColorBuffer;
//	GLuint m_rboDepthStencil;
	Pane * m_pParentPane;
	Vec4D<float> m_boxBlueprint;
	Vec4D<_UINT32> m_boxActual;
	_CHAR m_orientationBitFlag;

	// STD ::
	std::vector<IPaneAsset *> m_paneAssets;


	// MAY NOT BELONG IN OVERARCHING PANE, BUT THESE ARE IN EVERY PANE
	// KYLE ::
	// ALSO, I MAY WANT ACCESS TO THESE TO DO CERTAIN THINGS
privatized:
	GS::Graphics::ShaderProgramResource *		m_pScreenProg;
	GS::Graphics::ShaderProgramResource *		m_pTexProg;
	GS::Graphics::MeshResource *				m_pMesh;
	GS::Graphics::MeshResource *				m_pScreenMesh;

//	GLint										m_texloc;
//	GLint										m_transloc;

public:
	Pane() :
//		m_framebuffer(0),
//		m_texColorBuffer(0),
//		m_rboDepthStencil(0),
		m_pParentPane(0),
		m_orientationBitFlag(0),
		//m_pTex(0),
		m_pScreenProg(0), 
		m_pTexProg(0),
		m_pMesh(0),
		m_pScreenMesh(0)//,
//		m_texloc(0),
//		m_transloc(0)
		{}

	~Pane(){}

	/**
	* Draws the panel and all of it's assets to
	* its' framebuffer.
	* THIS WILL CALL draw() FOREACH m_paneAssets
	*/
	virtual void draw( GS::Graphics::IDimensionable * const a_dims );

	/**
	* Cycles through all of m_paneAssets to see
	* if any of them are dirty, which would set
	* the entire panel to dirty.
	* THIS WILL CALL isDirty() FOREACH m_paneAssets
	*/
	virtual _BOOL isDirty() const;

	/**
	* tells the pane to handle input
	* Each derived pane will handle input differently.
	* THIS WILL CALL handleInput() FOREACH m_paneAssets
	*/
	virtual _BOOL handleInput();

	/**
	* Initializes the Panel dimensional values like:
	* Parent Panel
	* Screen percentage and size in relation to parent
	* Screen pixel dimensions in relation to parent
	*/
	_INT32 initBlueprints( 
		const Vec4D<float> & a_blueprint );

	/**
	* Destroys and cleans up the Pane Object
	* Specifically, this cleans the 
	* THIS WILL CALL preShutdown()
	*/
	virtual void shutdown();

	/**
	* TODO :: THIS MAY NOT BE NEEDED 
	* Updates all paneAssets by a_dt
	* THIS WILL CALL update() FOREACH m_paneAssets
	*/
	virtual void update(const _DOUBLE a_dt);

	/**
	* Initializes the standard Pane library resources
	* THIS WILL CALL postInit()
	*/
	virtual _INT32 init( Pane * const a_pParent );

	/**
	* Get the dimensions of the given IDimensionable 
	* (IPane, in this case)
	*/
	virtual Vec2D<_INT32> getPixelDimensions() const;

	/**
	* Get the Pane's framebuffer.
	*/
//	virtual GLuint getFramebuffer() const;


selective:

	/**
	* Empty function for the base class
	* Override this for a more specialized init.
	*/
	virtual _INT32 __postInit() {return 0;}

	/**
	* Empty function for the base class
	* Override this for a more specialized shutdown.
	*/
	virtual void __preShutdown() {}

	/**
	* Empty function for the base class
	* Override to draw panel specific presentables
	*/
	virtual void __draw( GS::Graphics::IDimensionable * const a_dimensionable ) {}

	/**
	* Empty function for the base class
	* Override to properly tell specific panels they are dirty
	*/
	virtual _BOOL __isDirty() const {return false;}




	_UINT32 __initFramebuffer();

	_INT32 __calculateDimActual();
	_UINT32 __glFramebufferInit();
	void __glFramebufferDestroy();
	_UINT32 __glTexColorBufferInit();
	void __glTexColorBufferDestroy();
	_UINT32 __glRboDepthStencilInit();
	void __glRboDepthStencilDestroy(); 

	static _INT32 __initScreenVAOVBO();
	static void __shutdownScreenVAOVBO();

};

};
};

#endif
