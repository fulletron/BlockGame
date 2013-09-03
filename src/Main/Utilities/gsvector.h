#ifndef __GSVECTOR_H_
#define __GSVECTOR_H_

#include "typedefinitions.h"
#include "chunkmanager.h"

namespace GS {
namespace Utilities {

template<typename DATA_TYPE>
class GSVector
{
protected:
	DATA_TYPE * m_pDataArray;
	_UINT32 m_curSize;
	_UINT32 m_allSize;
public:
	~GSVector(){}

	GSVector(void)
	{
		m_pDataArray = 0;
		m_curSize = 0;
		m_allSize = 0;
	}

	_INT32 init( ChunkManager * const a_pChunkMan, const _INT64 a_targetFrame, const _UINT32 a_allSize )
	{
		return 0;
	}

	_INT32 init( Frame * const a_pFrame, const _UINT32 a_allSize )
	{
		m_pDataArray = (DATA_TYPE *)a_pFrame->allocate( sizeof(DATA_TYPE) * a_allSize, Frame::PLACE::BOT );
		m_allSize = a_allSize;
		return 0;
	}

	void shutdown()
	{
		memset(m_pDataArray, 0, sizeof(DATA_TYPE) * a_allSize);
		m_pDataArray = 0;
		m_curSize = 0;
		m_allSize = 0;
	}

	_UINT32 getSize()
	{
		return m_curSize;
	}

	void add( DATA_TYPE a_data )
	{
		if( !m_pDataArray )
			return;
	
		m_pDataArray[m_curSize] = a_data;
		m_curSize++;
	}

	void remove( _UINT32 a_index )
	{
		if( m_curSize && m_pDataArray )
			m_curSize--;
		if( m_curSize )
			m_pDataArray[a_index] = m_pDataArray[m_curSize];
	}

	void remove( DATA_TYPE a_data )
	{
		int i = 0;
		it = m_pDataArray[i];

		while( a_data !=  *it && i != m_curSize )
			it = m_pDataArray[++i];

		if( i != m_curSize )
			remove(i);
	}

	DATA_TYPE get( _UINT32 a_index )
	{
		if( m_pDataArray )
			return m_pDataArray[a_index];
	}

};

};
};

#endif
