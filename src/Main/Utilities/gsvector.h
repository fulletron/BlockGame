#ifndef __CHUNKVECTOR_H_
#define __CHUNKVECTOR_H_

#include "typedefinitions.h"
#include "frame.h"
#include "chunkptr.h"
#include "chunkmanager.h"

namespace GS {
namespace Utilities {

/*
template<typename DATA_TYPE>
class IVector
{
public:
	virtual void shutdown() = 0;
	virtual _UINT32 getSize() = 0;
	virtual void add( DATA_TYPE a_data ) = 0;
	virtual void clean() = 0;
	virtual void remove( _UINT32 a_index ) = 0;
	//virtual void remove( DATA_TYPE a_data ) = 0;
	virtual DATA_TYPE get( _UINT32 a_index ) = 0;
};
*/

template<typename DATA_TYPE>
class LimitedVector
{
selective:
	DATA_TYPE * m_pData;
	_UINT32 m_curSize;
	_UINT32 m_maxSize;
public:
	~LimitedVector(){}
	
	LimitedVector()
	{
		clean();
		m_curSize = 0;
		m_pData = 0;
		m_maxSize = 0;
	}

	_INT32 init( const _UINT32 a_maxSize, DATA_TYPE * a_pData )
	{
		m_maxSize = a_maxSize;
		m_pData = a_pData;
		clean();
		return 0;
	}

	void shutdown()
	{
		clean();
		m_curSize = 0;
		m_maxSize = 0;
	}
	
	_UINT32 getMax() const
	{
		return m_maxSize;
	}

	_UINT32 getSize() const
	{
		return m_curSize;
	}

	_UINT32 add( DATA_TYPE & a_data )
	{
		if( m_curSize + 1 < m_maxSize )
			return -1;

		std::memcpy( &m_pData[m_curSize],
				&a_data,
				sizeof(DATA_TYPE) );
		m_curSize++;
		return m_curSize - 1;
	}

	void clean()
	{
		memset( m_pData, 0, sizeof(DATA_TYPE) * m_maxSize);
	}

	void remove( _UINT32 a_index )
	{
		if( m_curSize )
			m_curSize--;
		if( m_curSize )
			std::memcpy( &m_pData[a_index], 
				&m_pData[m_curSize + 1], 
				sizeof(DATA_TYPE) );
	}

	DATA_TYPE get( _UINT32 a_index )
	{
		return m_pData[a_index];
	}

	DATA_TYPE * getp( _UINT32 a_index )
	{
		return &m_pData[a_index];
	}

};

/*
template<typename DATA_TYPE>
class LimitedVector16 : public IVector<DATA_TYPE>
{
selective:
	static const int MAX_SIZE = 16;

	DATA_TYPE m_vector[MAX_SIZE];

	_UINT32 m_curSize;

public:

	~LimitedVector16(){}

	LimitedVector16(void)
	{
		clean();
		m_curSize = 0;
	}

	_INT32 init( const _UINT32 a_allSize )
	{
		return 0;
	}	

	void shutdown()
	{
		clean();
		m_curSize = 0;
	}

	_UINT32 getSize()
	{
		return m_curSize;
	}

	void add( DATA_TYPE a_data )
	{
		if( m_curSize + 1 < MAX_SIZE )
			return;

		m_vector[m_curSize] = a_data;
		m_curSize++;
	}

	void clean()
	{
		memset(&m_vector, 0, sizeof(DATA_TYPE) * MAX_SIZE);
	}

	void remove( _UINT32 a_index )
	{
		if( m_curSize )
			m_curSize--;
		if( m_curSize )
			m_vector[a_index] = m_vector[m_curSize];
	}

	DATA_TYPE get( _UINT32 a_index )
	{
		return m_vector[a_index];
	}

};

template<typename DATA_TYPE>
class LimitedVector4 : public IVector<DATA_TYPE>
{
selective:
	static const int MAX_SIZE = 4;

	DATA_TYPE m_vector[MAX_SIZE];

	_UINT32 m_curSize;

public:

	~LimitedVector4(){}

	LimitedVector4(void)
	{
		clean();
		m_curSize = 0;
	}

	_INT32 init( const _UINT32 a_allSize )
	{
		return 0;
	}	

	void shutdown()
	{
		clean();
		m_curSize = 0;
	}

	_UINT32 getSize()
	{
		return m_curSize;
	}

	void add( DATA_TYPE a_data )
	{
		if( m_curSize + 1 < MAX_SIZE )
			return;

		m_vector[m_curSize] = a_data;
		m_curSize++;
	}

	void clean()
	{
		memset(&m_vector, 0, sizeof(DATA_TYPE) * MAX_SIZE);
	}

	void remove( _UINT32 a_index )
	{
		if( m_curSize )
			m_curSize--;
		if( m_curSize )
			m_vector[a_index] = m_vector[m_curSize];
	}

	DATA_TYPE get( _UINT32 a_index )
	{
		return m_vector[a_index];
	}
};

*/

template<typename DATA_TYPE>
class ChunkVector //: public IVector<DATA_TYPE>
{
#ifdef TEST_ENABLED
public:
#else
protected:
#endif
	TChunkPtr<DATA_TYPE> m_chunkPtr;

	_UINT32 m_curSize;
	_UINT32 m_allSize;
	_BOOL	m_inited;

public:
	~ChunkVector(){}

	ChunkVector(void)
	{
		m_curSize = 0;
		m_allSize = 0;
		m_inited = false;
	}

	ChunkVector<DATA_TYPE> & operator=( ChunkPtr a_chunkPtr )
	{
		m_chunkPtr = a_chunkPtr;
		return *this;
	}

	_INT32 init( const _UINT32 a_allSize )
	{
		m_inited = true;
		m_allSize = a_allSize;
		return 0;
	}	

	_INT32 init( const _UINT32 a_allSize, ChunkPtr a_chunkPtr )
	{
		m_chunkPtr = a_chunkPtr;

	}

	void shutdown()
	{
		clean();
		m_curSize = 0;
		m_allSize = 0;
		m_inited = false;
	}

	_UINT32 getSize()
	{
		// assert( (m_inited == true) ); // fpermissive error
		return m_curSize;
	}

	void add( DATA_TYPE a_data )
	{
		DATA_TYPE * pCurPlace = (m_chunkPtr.pointer());
		if( !pCurPlace )
			return;
		pCurPlace[m_curSize] = a_data;
		m_curSize++;
	}

	void clean()
	{
		//assert(m_inited);

		memset(m_chunkPtr.pointer(), 0, sizeof(DATA_TYPE) * m_allSize);
	}

	void remove( _UINT32 a_index )
	{
		// assert(m_inited); // fpermissive error

		if( m_curSize && m_chunkPtr.pointer() )
			m_curSize--;
		if( m_curSize )
			m_chunkPtr.pointer()[a_index] = m_chunkPtr.pointer()[m_curSize + 1];
	}

	DATA_TYPE get( _UINT32 a_index )
	{
		// assert(m_inited); // fpermissive error

		if( m_chunkPtr.pointer() )
			//return m_chunkPtr.dereference()[a_index];
			return (m_chunkPtr.pointer())[a_index];
		return 0;
	}

};

};
};

#endif
