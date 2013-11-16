#include "shaders.h"
#include "shaderprograms.h"
#include "..\base\shaderprogramresource.h"
#include <Game\game.h>
#include "..\base\shaderresource.h"

namespace GS {
namespace ResourceNS {

namespace ShaderPrograms {
	GS::LibraryNS::IEntry * __init_shaderProgram(GS::Game * const a_rpGame, const _UINT64 & a_key, GS::LibraryNS::EntryInitFunction a_vsFunc, GS::LibraryNS::EntryInitFunction a_fsFunc)
	{
		ShaderProgramResource * ret = (ShaderProgramResource *)a_rpGame->getLibrary()->getEntry(a_key);
		
		if(!ret)
		{
			ret = new ShaderProgramResource();
			ret->init(		a_rpGame, 
							a_vsFunc,
							a_fsFunc
						);
		}
		return a_rpGame->getLibrary()->addEntry(a_key, (GS::ResourceNS::IResourceFile *)ret);
	}

	GS::LibraryNS::IEntry * init_spfontdr(GS::Game * const a_rpGame)
	{
		GS::LibraryNS::IEntry * ret = __init_shaderProgram(
			a_rpGame, 
			(_UINT64)"spfontdr", 
			GS::ResourceNS::Shaders::init_vsfont00,
			GS::ResourceNS::Shaders::init_fsfont00
			);

		ShaderProgramResource * t_pShaderProgram = (ShaderProgramResource *)ret;

		t_pShaderProgram->link();
		

		return ret;
	}

	GS::LibraryNS::IEntry * init_spscrn00(GS::Game * const a_rpGame)
	{

		GS::LibraryNS::IEntry * ret = __init_shaderProgram(
			a_rpGame, 
			(_UINT64)"spscrn00", 
			GS::ResourceNS::Shaders::init_vsscrn00,
			GS::ResourceNS::Shaders::init_fsscrn00
			);

		ShaderProgramResource * t_pShaderProgram = (ShaderProgramResource *)ret;

		glBindFragDataLocation( t_pShaderProgram->getProgramID(), 0, "outColor" );

		t_pShaderProgram->link();

		/// SHIT NEEDS TO BE BOUND!

		return ret;
	}
};

};
};