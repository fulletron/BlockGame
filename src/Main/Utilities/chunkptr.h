#ifndef __CHUNKPTR_H_
#define __CHUNKPTR_H_ 

#include "typedefinitions.h"
#include "frame.h"

namespace GS {
namespace Utilities {

class ChunkPtr
{
#ifdef TEST_ENABLED
public:
#else
protected:
#endif

	_BYTE * m_pData;
	Frame * m_pOwnerFrame;
	_INT64 m_ownerName;


public:	

	ChunkPtr();
	ChunkPtr( _BYTE * a_pData, Frame * a_pOwnerFrame, const _INT64 a_ownerName);

	void clean();
	bool isValid();

	void setpData( _BYTE * const a_pData){ m_pData = a_pData; }
	void setpOwnerFrame( Frame * const a_pOwner ){ m_pOwnerFrame = a_pOwner; }
	void setOwnerName( const _INT64 a_ownerName ){ m_ownerName = a_ownerName; }

	_BYTE * getpData(){return m_pData;}
	Frame * getOwnerFrame(){return m_pOwnerFrame;}
	_INT64 getOwnerName(){return m_ownerName;}

protected:

	_BYTE * __pointer();
	void __update(ChunkPtr & a_cpUp);
};

template<typename DATA_TYPE>
class TChunkPtr : public ChunkPtr
{
#ifdef TEST_ENABLED
public:
#else
protected:
#endif

public:	
	DATA_TYPE & dereference()
	{
		return *(pointer());
	}

	DATA_TYPE * pointer()
	{
		if(isValid())
			return RC( DATA_TYPE *, __pointer() );
		else
			return 0;
	}

	TChunkPtr<DATA_TYPE> & operator=(ChunkPtr & a_chunkPtr)
	{
		m_pData = a_chunkPtr.getpData();
		m_pOwnerFrame = a_chunkPtr.getOwnerFrame();
		m_ownerName = a_chunkPtr.getOwnerName();

		return *this;
	}

protected:
};

};
};

typedef GS::Utilities::ChunkPtr _ChunkPtr;
#define _TChunkPtr GS::Utilities::TChunkPtr

#endif
