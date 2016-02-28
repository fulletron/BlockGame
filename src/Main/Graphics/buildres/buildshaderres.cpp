#include <Graphics/reslib.h>

namespace GS {
namespace Graphics {

ShaderResource * ResourceLibrary::__buildShaderRes( const _UINT64 a_name )
{
	ShaderResource * newRes = new ShaderResource();
	std::string src_effect = "Internal/Resources/Effects/";
	std::string src = "";
	_INT32 type = 0;

	switch (a_name)
	{
	case CV8::RES_SH_BASEFONTVS:
		type = GL_VERTEX_SHADER;
		src = _FS::loadFile((_FS::getCurrentFullPath()
			.append(src_effect)
			.append("basicfont.vert").c_str()));
		break;
	case CV8::RES_SH_BASEFONTFS:
		type = GL_FRAGMENT_SHADER;
		src = _FS::loadFile((_FS::getCurrentFullPath()
			.append(src_effect)
			.append("basicfont.frag").c_str()));
		break;
	case CV8::RES_SH_BASEFBVS:
		type = GL_VERTEX_SHADER;
		src = _FS::loadFile((_FS::getCurrentFullPath()
			.append(src_effect)
			.append("basicframebuffer.vert").c_str()));
		break;
	case CV8::RES_SH_BASEFBFS:
		type = GL_FRAGMENT_SHADER;
		src = _FS::loadFile((_FS::getCurrentFullPath()
			.append(src_effect)
			.append("basicframebuffer.frag").c_str()));
		break;
	case CV8::RES_SH_TEXRECTVS:
		type = GL_VERTEX_SHADER;
		src = _FS::loadFile((_FS::getCurrentFullPath()
			.append(src_effect)
			.append("texrect.vert").c_str()));
		break;
	case CV8::RES_SH_TEXRECTFS:
		type = GL_FRAGMENT_SHADER;
		src = _FS::loadFile((_FS::getCurrentFullPath()
			.append(src_effect)
			.append("texrect.frag").c_str()));
		break;
	default: return 0;
	}

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
