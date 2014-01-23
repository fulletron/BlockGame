#include "paneentities.h"
#include "entity.h"
#include <Panel\base\panel.h>
#include <Game\game.h>
#include <Resource\base\fontresource.h>
#include <Resource\base\shaderprogramresource.h>
#include <Resource\base\meshresource.h>
#include <Resource\constructs\meshes.h>
#include <Resource\constructs\shaderprograms.h>
#include <Resource\base\textureresource.h>
#include <Utilities\gsinlines.h>

namespace GS {
namespace EntityNS {

	PaneTexture * PaneTexture::Construct(		GS::Game * const a_rpGame, 
												GS::PanelNS::Panel * const a_rpPanel, 
												GS::LibraryNS::EntryInitFunction a_initFunction, 
												const _RECT<_FLOAT> & a_posCov, 
												const ALIGNMENT & a_alignment)
	{
		PaneTexture * ret = new PaneTexture();
		ret->m_rpGame = a_rpGame;
		ret->m_rpOwnerPanel = a_rpPanel;

		/// SET ENTITY AND SCREEN VARIABLES

		if(a_rpPanel)
		{
			ret->m_screen.set(a_rpPanel->getScreen(), a_posCov, a_alignment);
			ret->m_rpParentScreen = a_rpPanel->getScreen();
		}
		else
		{
			GS::WindowNS::Screen * t_pWindowScreen = a_rpGame->getGraphics()->get__m_baseWindow()->get__m_windowScreen();
			ret->m_screen.set(t_pWindowScreen, a_posCov, a_alignment);
			ret->m_rpParentScreen = t_pWindowScreen;
		}
		ret->setMyBaseFocus(USHORTMAX);

		/// SET PANE TEXTURE'S RESOURCES
		ret->m_rpMesh = (GS::ResourceNS::MeshResource *)GS::ResourceNS::Meshes::init_mzscrn00(a_rpGame);
		ret->m_rpShaderProgram = (GS::ResourceNS::ShaderProgramResource *) GS::ResourceNS::ShaderPrograms::init_spscrn00(a_rpGame);
		ret->m_rpTexture = (GS::ResourceNS::TextureResource *)a_initFunction(a_rpGame);

		/// MIGHT NOT BE NECESSARY
		//ret->m_position.x = (float)ret->m_screen.m_pxRect.left;
		//ret->m_position.y = (float)ret->m_screen.m_pxRect.bottom;

		return ret;
	}

	void PaneTexture::draw()
	{
		glBindVertexArray(m_rpMesh->get__m_vao());

		glDisable(GL_DEPTH_TEST);
		m_rpShaderProgram->useProgram();

			_RECT<_INT32> t_ownerScreenRect = m_screen.m_pxRect;
			_RECT<_INT32> t_parentScreenRect = m_rpParentScreen->m_pxRect;

			_FLOAT t_X = (((_FLOAT)((t_ownerScreenRect.left * 2) + t_ownerScreenRect.width)) / ((_FLOAT)(t_parentScreenRect.width))) - 1.0f;
			_FLOAT t_Y = (((_FLOAT)((t_ownerScreenRect.bottom * 2) + t_ownerScreenRect.height)) / ((_FLOAT)(t_parentScreenRect.height))) - 1.0f;

			/// THIS TRANSLATION IS BASED ON the -1.0, 1.0 maxes provided standardly.
			glm::mat4 iden = glm::mat4(1.0f);
			glm::mat4 trans = glm::translate(iden, glm::vec3(t_X,t_Y,0.0));
			glm::mat4 scale = glm::scale(trans, glm::vec3((float)t_ownerScreenRect.width / (float)t_parentScreenRect.width, (float)t_ownerScreenRect.height / (float)t_parentScreenRect.height,1.0));

			m_rpShaderProgram->setUniform("trans",&scale);

			/// ================================================================

			glActiveTexture(GL_TEXTURE0);
			glBindTexture( GL_TEXTURE_2D, m_rpTexture->get__m_glTexture() );

		glDrawArrays( GL_TRIANGLES, 0, 6 );
	}

	PaneFontText * PaneFontText::Construct(	GS::Game * const a_rpGame, 
											GS::PanelNS::Panel * const a_rpPanel, 
											GS::LibraryNS::EntryInitFunction a_initFunction, 
											const _RECT<_FLOAT> & a_posCov, 
											const ALIGNMENT & a_alignment, 
											const _ARRAYFOUR<_FLOAT> & a_color,
											const DATATYPE_IDENTIFIER & a_identifier, 
											void * a_data,
											std::string a_overString)
	{
		PaneFontText * ret = new PaneFontText();
		ret->m_rpGame = a_rpGame;
		ret->m_rpOwnerPanel = a_rpPanel;

		/// SET ENTITY AND SCREEN VARIABLES
		if(a_rpPanel)
			ret->m_screen.set(a_rpPanel->getScreen(), a_posCov, a_alignment);
		else
		{
			GS::WindowNS::Screen * t_pWindowScreen = a_rpGame->getGraphics()->get__m_baseWindow()->get__m_windowScreen();
			ret->m_screen.set(t_pWindowScreen, a_posCov, a_alignment);
		}
		ret->setMyBaseFocus(USHORTMAX);

		/// SET PANE FONT VARIABLES
		ret->m_dataType = a_identifier;
		ret->m_rpPrintableData = a_data;
		ret->m_color = a_color;
		ret->m_overString = a_overString;

		/// SET PANE FONT'S RESOURCES
		GLenum error = glGetError();
		ret->m_rpFont = (GS::ResourceNS::FontResource *)a_initFunction(a_rpGame);
		error = glGetError();

		return ret;
	}


	void PaneFontText::draw()
	{
		glDisable(GL_DEPTH_TEST);
		glDepthFunc(GL_ALWAYS);
	
		GS::ResourceNS::ShaderProgramResource * t_pProgram = m_rpFont->get__m_pShaderProgram();
			
		t_pProgram->useProgram();

		t_pProgram->setUniform("vColor", glm::vec4(m_color.r, m_color.g, m_color.b, m_color.a)); /// THE ACTUAL COLOR!
		// Font color, you can even change transparency of font with alpha parameter
		//t_pProgram->setUniform("vColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); /// WHITE!
		//t_pProgram->setUniform("vColor", glm::vec4(0.6445f, 0.5703f, 0.3867f, 1.0f)); /// UNIQUE GOLD
		//t_pProgram->setUniform("vColor", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)); /// SET GREEN
		//t_pProgram->setUniform("vColor", glm::vec4(1.0f, (165.0f/256.0f), 0.0f, 1.0f)); /// CRAFTED ORANGE
		//t_pProgram->setUniform("vColor", glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)); /// RARE YELLOW
		//t_pProgram->setUniform("vColor", glm::vec4((065.0f/256.0f), (105.0f/256.0f), (225.0f/256.0f), 1.0f) ); /// BLUE MAGIC
		//t_pProgram->setUniform("vColor", glm::vec4( (176.0f/256.0f), (72.0f/256.0f), (248.0f/256.0f), 1.0f) ); ///"EPIC"
		//t_pProgram->setUniform("vColor", glm::vec4(_DB256(67.0f), _DB256(191.0f), _DB256(199.0f), 1.0f)); /// DOUBLE-EDGE TEAL

		_RECT<_INT32> * t_pParentScreenRect = 0;
		
		if(m_rpOwnerPanel)
			t_pParentScreenRect = &m_rpOwnerPanel->getScreen()->m_pxRect;
		else
		{
			t_pParentScreenRect = &m_rpGame->getGraphics()->get__m_baseWindow()->get__m_windowScreen()->m_pxRect;
		}

		/// FRAMEBUFFER VIEWPORTS BELIEVE IN 0,0,width,height
		t_pProgram->setUniform("projectionMatrix", glm::ortho(0.0f, float(t_pParentScreenRect->width), 0.0f, float(t_pParentScreenRect->height)) );

		int t_positionX = 0;
		int t_size = m_screen.m_pxRect.height;
		switch(m_screen.m_relAlignment)
		{
		case ALIGN_LEFT: 
			t_positionX = m_screen.m_pxRect.left;
			break;
		case ALIGN_RIGHT: 
			t_positionX = m_screen.m_pxRect.left - (int)m_rpFont->getStringWidthPx(m_overString, t_size);
			break;
		case ALIGN_CENTER: 
			t_positionX = m_screen.m_pxRect.left - (int)(((float)m_rpFont->getStringWidthPx(m_overString, t_size)) * (float)(0.5f));
			break;
		default: 
			break;
		}

		if(m_overString != "" || m_dataType == DATATYPE_NONE)
		{
			m_rpFont->print(m_overString, t_positionX, m_screen.m_pxRect.bottom, m_screen.m_pxRect.height);
		}
		else
		{
			switch(m_dataType)
			{
			case DATATYPE_UINT32:
				{
				_UINT32 * pVal = (_UINT32 *)m_rpPrintableData;
				char * buf = GS::UtilitiesNS::itoa10_prebuf((_UINT32)*pVal);
				m_rpFont->print(buf, t_positionX, m_screen.m_pxRect.bottom, m_screen.m_pxRect.height);
				}
				break;

				// TODO::
				// KYLE ::
				// GOOD STUFF MUST BE DONE HERE FOR OTHER KINDS OF DATATYPES!
				case DATATYPE_CONSTCHARP: 
					m_rpFont->print(*((std::string*)m_rpPrintableData), 0, t_pParentScreenRect->height - 48, 48);
					break;
				default:
					m_rpFont->print("BAD TYPE", 0, t_pParentScreenRect->height - 48, 48);
			}
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}

	void PaneFontText::onScreenResize()
	{
		if(m_rpOwnerPanel)
		{
			//_RECT<_INT32> * t_pScreenRect = &m_rpOwnerPanel->getScreen()->m_pxRect;
			m_screen.set(m_rpOwnerPanel->getScreen(), m_screen.m_relPosCov, m_screen.m_relAlignment);
			//m_screen.m_pxRect = GS::WindowNS::GetPXRectFromRect(m_screen.m_relPosCov, m_screen.m_relAlignment, *t_pScreenRect);
		}
		else
		{
			GS::WindowNS::Screen * t_pWindowScreen = m_rpGame->getGraphics()->get__m_baseWindow()->get__m_windowScreen();
			m_screen.set(t_pWindowScreen, m_screen.m_relPosCov, m_screen.m_relAlignment);
			//_RECT<_INT32> * t_pScreenRect = &m_rpOwnerPanel->getScreen()->m_pxRect;
			//m_screen.m_pxRect = GS::WindowNS::GetPXRectFromRect(m_screen.m_relPosCov, m_screen.m_relAlignment, *t_pScreenRect);
		}
		m_actorManager.manageOnScreenResize();
	}
};
};