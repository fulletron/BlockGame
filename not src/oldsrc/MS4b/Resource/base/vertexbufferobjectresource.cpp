#include "vertexbufferobjectresource.h"
#include <Graphics\openglincludes.h>

namespace GS {
namespace ResourceNS {
	VertexBufferObjectResource::VertexBufferObjectResource()
		: m_dataUploaded(false)
	{}

	void VertexBufferObjectResource::__createVBO(const _INT32 & a_size)
	{
		glGenBuffers(1, &m_buffer);
		m_data.ensureCapacity(a_size);
		m_size = a_size;
	}

	void VertexBufferObjectResource::__releaseVBO()
	{
		glDeleteBuffers(1, &m_buffer);
		m_dataUploaded = false;
		m_data.release();
	}

	void* VertexBufferObjectResource::__mapBufferToMemory(const _INT32 & a_usageHint)
	{
		if(!m_dataUploaded)
			return NULL;

		void* ptrRes = glMapBuffer(m_bufferType, a_usageHint);
		return ptrRes;
	}

	void* VertexBufferObjectResource::__mapSubBufferToMemory(const _INT32 & a_usageHint, const _UINT32 & a_offset, const _UINT32 & a_length)
	{
		if(!m_dataUploaded)
			return NULL;

		void* ptrRes = glMapBufferRange(m_bufferType, a_offset, a_length, a_usageHint);
		return ptrRes;
	}

	void VertexBufferObjectResource::__unMapBuffer()
	{
		glUnmapBuffer(m_bufferType);
	}

	void VertexBufferObjectResource::uploadDataToGPU(_INT32 a_drawingHint)
	{
		glBufferData(m_bufferType, m_data.size(), &m_data.get(0), a_drawingHint);
		m_dataUploaded = true;

		/// KYLE :: REALLY? THIS DOESN'T SEEM WANTED (CLEARING THE DATA AFTER UPLOADING TO GPU)
		m_data.release();
	}

	void VertexBufferObjectResource::addData(void* a_data, const _UINT32 & a_dataSize)
	{
		_BYTE * new_data = (_BYTE*)a_data;
		for(_UINT32 i = 0; i < a_dataSize; ++i)
			m_data.add(new_data[i]);
	}


	void VertexBufferObjectResource::bindVBO(_INT32 a_bufferType)
	{
		m_bufferType = a_bufferType;
		glBindBuffer(m_bufferType, m_buffer);
	}

	void* VertexBufferObjectResource::getDataPointer()
	{
		if(m_dataUploaded)return NULL;
		return (void*)m_data.get(0);
	}

	_UINT32 VertexBufferObjectResource::getBuffer()
	{
		return m_buffer;
	}

	void VertexBufferObjectResource::shutdown()
	{
		__releaseVBO();
	}
};
};