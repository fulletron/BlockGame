#ifndef __CHUNKPTR_H_
#define __CHUNKPTR_H_ 

#include "typedefinitions.h"
#include "frame.h"

/**
* _TChunkPtr is where the magic happens. Chunk Manager allocations return a
* ChunkPtrs, the base class for a _TChunkPtr, which simply is a templated
* ChunkPtr. You can call dereference() to set the data, call pointer() to
* get a pointer, and assign ChunkPointers to TChunkPtrs
**/

namespace GS {
namespace Utilities {

class ChunkPtr
{
selective:
	_BYTE * m_pData;
	Frame * m_pOwnerFrame;
	_INT64 m_ownerName;

public:	
	ChunkPtr();
	ChunkPtr( _BYTE * a_pData, Frame * a_pOwnerFrame, const _INT64 a_ownerName);

	void clean();

	void setpData( _BYTE * const a_pData){ m_pData = a_pData; }
	void setpOwnerFrame( Frame * const a_pOwner ){ m_pOwnerFrame = a_pOwner; }
	void setOwnerName( const _INT64 a_ownerName ){ m_ownerName = a_ownerName; }

	_BYTE * bytePointer(){return m_pData;}
	Frame * getOwnerFrame(){return m_pOwnerFrame;}
	_INT64 getOwnerName(){return m_ownerName;}

selective:
	bool __isValid();
	_BYTE * __pointer(); // fpermissive if &
	void __update(ChunkPtr a_cpUp); // fpermissive if &
};

template<typename DATA_TYPE>
class TChunkPtr : protected ChunkPtr
{
public:	
	DATA_TYPE & dereference()
	{
		return *(pointer());
	}

	DATA_TYPE * pointer()
	{
		if(__isValid())
			return RC( DATA_TYPE *, __pointer() );
		else
			return 0;
	}

	TChunkPtr<DATA_TYPE> & operator=(ChunkPtr a_chunkPtr)
	{
		m_pData = a_chunkPtr.bytePointer();
		m_pOwnerFrame = a_chunkPtr.getOwnerFrame();
		m_ownerName = a_chunkPtr.getOwnerName();

		return *this;
	}
};

};
};

typedef GS::Utilities::ChunkPtr _ChunkPtr;
#define _TChunkPtr GS::Utilities::TChunkPtr

#endif
