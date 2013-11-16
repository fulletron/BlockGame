#ifndef __VERTEXBUFFEROBJECTRESOURCE_H_
#define __VERTEXBUFFEROBJECTRESOURCE_H_

#include "resourcefile.h"
#include <Graphics\openglincludes.h>

namespace GS {
namespace ResourceNS {

	struct VertexBufferObjectBuilder
	{
		GS::Game * m_rpGame;
	};

	class VertexBufferObjectResource : public IResourceFile
	{
	private:
		void __releaseVBO();

		void* __mapBufferToMemory(const _INT32 & a_hint);
		void* __mapSubBufferToMemory(const _INT32 & a_usageHint, const _UINT32 & a_offset, const _UINT32 & a_length);
		void __unMapBuffer();

	public:
		VertexBufferObjectResource();
		~VertexBufferObjectResource(){}

		void __createVBO(const _INT32 & a_size = 0);

		_UINT32 init(void * a_pVertexBufferObjectBuilder);
		void shutdown();

		void bindVBO(_INT32 a_bufferType = GL_ARRAY_BUFFER);
		void* getDataPointer();
		_UINT32 getBuffer();

		void addData(void * a_data, const _UINT32 & a_dataSize);
		void uploadDataToGPU(const _INT32 a_usageHint);
	private:
		_UINT32					m_buffer;
		_INT32					m_size;
		_INT32					m_bufferType;
		_GSVECTOR(_BYTE)		m_data;

		bool					m_dataUploaded;
	};
};
};

#endif