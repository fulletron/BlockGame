#include "shaders.h"
#include "..\base\shaderresource.h"
#include <Game\game.h>

namespace GS {
namespace ResourceNS {

namespace Shaders {
	
	GS::LibraryNS::IEntry * __init_shader(GS::Game * a_rpGame, const _UINT64 & a_shaderKey, const char * a_charStream, int a_shaderType)
	{
		ShaderResource * ret = (ShaderResource *)a_rpGame->getLibrary()->getEntry(a_shaderKey);
		
		if(!ret)
		{
			ret = new ShaderResource();
			ret->init(		a_rpGame,
							a_charStream,
							a_shaderType
						);
		}
		return a_rpGame->getLibrary()->addEntry(a_shaderKey, (GS::ResourceNS::IResourceFile *)ret);
	}

	GS::LibraryNS::IEntry * init_vsfont00(GS::Game * a_rpGame)
	{
		const char* vSource =
			"#version 330\n"
			"uniform mat4 projectionMatrix;"
			"uniform mat4 modelViewMatrix;"
			"layout (location = 0) in vec2 inPosition;"
			"layout (location = 1) in vec2 inCoord;"
			"out vec2 texCoord;"
			"void main() {"
			"	gl_Position = projectionMatrix*modelViewMatrix*vec4(inPosition, 0.0, 1.0);"
			"	texCoord = inCoord;"
			"}";

		return __init_shader(a_rpGame,
							(_UINT64)"vsfont00",
							vSource, /// KYLE :: THIS IS THE VERTEX SHADER SOURCE CODE
							GL_VERTEX_SHADER
							);
	}

	GS::LibraryNS::IEntry * init_fsfont00(GS::Game * a_rpGame)
	{
		const char* fSource = 
			"#version 330\n"
			"in vec2 texCoord;"
			"out vec4 outputColor;"
			"uniform sampler2D gSampler;"
			"uniform vec4 vColor;"

			"void main() {"
				"vec4 vTexColor = texture2D(gSampler, texCoord);"

				//"outputColor = vTexColor*vec4(vColor.r, vColor.g, vColor.b, vColor.a);"

				/// CONDITIONAL FADE!!!!!
				//if(vTexColor.r + vTexColor.g + vTexColor.b < 0.05f){outputColor = vec4(0.0,0.0,0.0,0.0f);}"
				//"else{outputColor = vTexColor*vec4(vColor.r, vColor.g, vColor.b, vColor.a);}"

				/// MATHS FADE!!!!!!(ADJUSTABLE FOR MOUSEOVER HIGHLIGHT!)
				//"outputColor = vTexColor*vec4(vColor.r, vColor.g, vColor.b, vColor.a * (vTexColor.r + vTexColor.g + vTexColor.b) * 100.0);"
				"outputColor = vec4(vTexColor.r*vColor.r, vTexColor.r*vColor.g, vTexColor.r*vColor.b, vTexColor.r*(vColor.a * (vTexColor.r + vTexColor.g + vTexColor.b) * 100.0));"
			"}";


		return __init_shader(a_rpGame,
							(_UINT64)"fsfont00",
							fSource, /// KYLE :: THIS IS THE FRAGMENT SHADER SOURCE CODE
							GL_FRAGMENT_SHADER
							);
	}

	GS::LibraryNS::IEntry * init_vsscrn00(GS::Game * a_rpGame)
	{
		const char* vSource =
			"#version 150\n"
			"in vec2 position;"
			"in vec2 texcoord;"
			"uniform mat4 trans;"
			//"uniform vec4 posCov = vec4(0.0,0.0,1.0,1.0);"
			"out vec2 Texcoord;"
			"void main() {"
			"	Texcoord = texcoord;"
			"	gl_Position = trans * vec4( position, 0.0, 1.0 );"
			"}";

		return __init_shader(a_rpGame,
							(_UINT64)"vsscrn00",
							vSource, /// KYLE :: THIS IS THE VERTEX SHADER SOURCE CODE
							GL_VERTEX_SHADER
							);
	}

	GS::LibraryNS::IEntry * init_fsscrn00(GS::Game * a_rpGame)
	{
		const char* fSource =
			"#version 150\n"
			"in vec2 Texcoord;"
			"out vec4 outColor;"
			"uniform sampler2D texFramebuffer;"
			"void main() {"
			"	outColor = texture( texFramebuffer, Texcoord );"
			"}";

		return __init_shader(a_rpGame,
							(_UINT64)"fsscrn00",
							fSource, /// KYLE :: THIS IS THE FRAGMENT SHADER SOURCE CODE
							GL_FRAGMENT_SHADER
							);
	}

	GS::LibraryNS::IEntry * init_vs2dtex0(GS::Game * a_rpGame)
	{
		const char* vSource =
			"#version 330\n"
			"uniform mat4 projectionMatrix;"
			"uniform mat4 modelViewMatrix;"
			"layout (location = 0) in vec2 inPosition;"
			"layout (location = 1) in vec2 inCoord;"
			"out vec2 texCoord;"
			"void main() {"
			"	gl_Position = projectionMatrix*modelViewMatrix*vec4(inPosition, 0.0, 1.0);"
			"	texCoord = inCoord;"
			"}";

		return __init_shader(a_rpGame,
							(_UINT64)"vs2dtex0",
							vSource, /// KYLE :: THIS IS THE VERTEX SHADER SOURCE CODE
							GL_VERTEX_SHADER
							);
	}

	GS::LibraryNS::IEntry * init_fs2dtex0(GS::Game * a_rpGame)
	{
		const char* fSource = 
			"#version 330\n"
			"in vec2 texCoord;"
			"out vec4 outputColor;"
			"uniform sampler2D gSampler;"
			"uniform vec4 vColor;"

			"void main() {"
				"outputColor = texture2D(gSampler, texCoord);"
			"}";


		return __init_shader(a_rpGame,
							(_UINT64)"fs2dtex0",
							fSource, /// KYLE :: THIS IS THE FRAGMENT SHADER SOURCE CODE
							GL_FRAGMENT_SHADER
							);
	}

};

};
};