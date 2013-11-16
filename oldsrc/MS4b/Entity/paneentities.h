#ifndef __PANEENTITIES_H_
#define __PANEENTITIES_H_

#include "entity.h"
#include <Game\definitions.h>
#include <Resource\base\resourcefile.h>
#include <Panel\base\panel.h>
#include <Graphics\window.h>

namespace GS {
namespace ResourceNS{ class FontResource; class TextureResource; class FontTextureResource; class MeshResource; class ShaderProgramResource;};
namespace PanelNS { class ILayer; };
namespace EntityNS {

	enum DATATYPE_IDENTIFIER
	{
		DATATYPE_UNKNOWN = -1,
		DATATYPE_NONE = 0,
		DATATYPE_STRING = 1,
		DATATYPE_CHARP = 2,
		DATATYPE_UINT32 = 3,
		DATATYPE_INT32 = 4,
		DATATYPE_USHORT = 5,
		DATATYPE_SHORT = 6,
		DATATYPE_CONSTSTRING = 7,
		DATATYPE_CONSTCHARP = 8,
	}; 

	class PaneTexture : public Entity2D
	{
	public:
		static PaneTexture * Construct(		GS::Game * const a_rpGame, 
											GS::PanelNS::Panel * const a_rpLayer, 
											GS::LibraryNS::EntryInitFunction a_textureInitFunc, 
											const _RECT<_FLOAT> & a_posCov, 
											const ALIGNMENT & a_alignment);

	private:
		GS::ResourceNS::TextureResource *			m_rpTexture;	
		GS::ResourceNS::MeshResource *				m_rpMesh;
		GS::ResourceNS::ShaderProgramResource *		m_rpShaderProgram;

		GS::PanelNS::Panel *						m_rpOwnerPanel;


		GS::WindowNS::Screen						m_screen;
		GS::WindowNS::Screen *						m_rpParentScreen;
		//_RECT<_FLOAT>								m_posCov;
		//ALIGNMENT									m_alignment;
	public:
		PaneTexture(){}
		~PaneTexture(){}

		//_UINT32 init(){return 0;}
		void update(const _DOUBLE & a_dt){}
		void draw();
		void shutdown(){}
		bool input(GS::InputNS::Input * const a_input){return false;}
		void onScreenResize()
		{
			m_screen.m_pxRect = GS::WindowNS::GetPXRectFromRect(m_screen.m_relPosCov, m_screen.m_relAlignment, m_rpParentScreen->m_pxRect);
			m_actorManager.manageOnScreenResize();
		}
	};

	class PaneFontText : public Entity2D
	{
	public:
		static PaneFontText * Construct(	GS::Game * const a_rpGame, 
											GS::PanelNS::Panel * const a_rpLayer, 
											GS::LibraryNS::EntryInitFunction a_initFunction, 
											const _RECT<_FLOAT> & a_posCov, 
											const ALIGNMENT & a_alignment, 
											const _ARRAYFOUR<_FLOAT> & a_color,
											const DATATYPE_IDENTIFIER & a_identifier, 
											void * a_data,
											std::string a_overString);

	protected:
		GS::ResourceNS::FontResource *				m_rpFont;

		GS::PanelNS::Panel *						m_rpOwnerPanel;
		GS::WindowNS::Screen						m_screen;

		_ARRAYFOUR<_FLOAT>							m_color;
		DATATYPE_IDENTIFIER							m_dataType;
		void *										m_rpPrintableData;
		std::string									m_overString;


	public:
		PaneFontText(){}
		~PaneFontText(){}

		//_UINT32 init();
		void update(const _DOUBLE & a_dt){}
		void draw();
		void shutdown(){}
		bool input(GS::InputNS::Input * const a_pInput){return false;}
		void onScreenResize();
	};
};
};

#endif