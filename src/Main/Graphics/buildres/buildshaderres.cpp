#include <Graphics/reslib.h>

namespace GS {
namespace Graphics {

//bool ResourceLibrary::__grabSrcFromFile( std::string & a_src,  )
//{
//}

ShaderResource * ResourceLibrary::__buildShaderRes( const _UINT64 a_name )
{
	ShaderResource * newRes = new ShaderResource();
	std::string src_effect = "/Internal/Resources/Effects/";
	//std::string src_effect = "\\Internal\\Resources\\Effects\\";
	std::string src = "";
	_INT32 type = 0;

	std::string src_file = _FS::getCurrentFullPath();
	src_file.append(src_effect);
	//src_file.append("basicfont.vert");
	//std::string test_src = _FS::loadFile(src_file.c_str());


	switch (a_name)
	{
	case CV8::RES_SH_BASEFONTVS:
		type = GL_VERTEX_SHADER;
		src_file.append("basicfont.vert");
		break;
	case CV8::RES_SH_BASEFONTFS:
		type = GL_FRAGMENT_SHADER;
		src_file.append("basicfont.frag");
		break;
	case CV8::RES_SH_BASEFBVS:
		type = GL_VERTEX_SHADER;
		src_file.append("basicframebuffer.vert");
		break;
	case CV8::RES_SH_BASEFBFS:
		type = GL_FRAGMENT_SHADER;
		src_file.append("basicframebuffer.frag");
		break;
	case CV8::RES_SH_TEXRECTVS:
		type = GL_VERTEX_SHADER;
		src_file.append("texrect.vert");
		break;
	case CV8::RES_SH_TEXRECTFS:
		type = GL_FRAGMENT_SHADER;
		src_file.append("texrect.frag");
		break;
	default: return 0;
	}

	src = _FS::loadFile(src_file.c_str());

	/*
	switch(a_name)
	{
	case CV8::RES_SH_BASEFONTVS :
		type = GL_VERTEX_SHADER;
		src = _FS::loadFile( ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Effects/" 
		/ "basicfont.vert").string().c_str() );
		break;
	case CV8::RES_SH_BASEFONTFS: 
		type = GL_FRAGMENT_SHADER;
		src = _FS::loadFile( ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Effects/" 
		/ "basicfont.frag").string().c_str() );
		break;
	case CV8::RES_SH_BASEFBVS: 
		type = GL_VERTEX_SHADER;
		src = _FS::loadFile( ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Effects/" 
		/ "basicframebuffer.vert").string().c_str() );
		break;
	case CV8::RES_SH_BASEFBFS: 
		type = GL_FRAGMENT_SHADER;
		src = _FS::loadFile( ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Effects/" 
		/ "basicframebuffer.frag").string().c_str() );
		break;
	case CV8::RES_SH_TEXRECTVS: 
		type = GL_VERTEX_SHADER;
		src = _FS::loadFile( ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Effects/" 
		/ "texrect.vert").string().c_str() );
		break;
	case CV8::RES_SH_TEXRECTFS: 
		type = GL_FRAGMENT_SHADER;
		src = _FS::loadFile( ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Effects/" 
		/ "texrect.frag").string().c_str() );
		break;
	default: return 0; 
	}
	*/

	newRes->init( src.c_str(), type );
	newRes->assignName( a_name );
	newRes->assignType( ResourceLibrary::SHADER );
	newRes->addCount();
	m_pShaderResources.push_back( newRes );
	return newRes;
}
};

};
