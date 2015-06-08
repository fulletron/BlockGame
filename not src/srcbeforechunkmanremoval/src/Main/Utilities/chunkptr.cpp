#include "chunkptr.h"
#include <Utilities/chunkmanager.h>
#include <cstring>

extern GS::Utilities::ChunkManager g_chunkman;

namespace GS {
namespace Utilities {


	ChunkPtr::ChunkPtr()
	{
		clean();
	}

	ChunkPtr::ChunkPtr( _BYTE * a_pData, Frame * a_pOwnerFrame, const _INT64 a_ownerName)
	{
		m_pData = a_pData;
		m_pOwnerFrame = a_pOwnerFrame;
		m_ownerName = a_ownerName;
	}

	void ChunkPtr::clean()
	{
		m_pData = 0;
		m_pOwnerFrame = 0;
		m_ownerName = 0;
	}

	bool ChunkPtr::__isValid()
	{
		if( m_ownerName && m_pData )
			return true;

		return false;
	}

	_BYTE * ChunkPtr::__pointer()
	{
		if(!__isValid())
			return 0;

		// The data has moved
		if ( m_pOwnerFrame->getName() != m_ownerName )
			__update(g_chunkman.getNewChunkPtr( ChunkPtr(m_pData, m_pOwnerFrame, m_ownerName) ));

		// return data
		return m_pData;
	}

	void ChunkPtr::__update( ChunkPtr  a_cpUp )
	{
		m_pData = a_cpUp.__pointer();
		m_pOwnerFrame = a_cpUp.getOwnerFrame();
		m_ownerName = a_cpUp.getOwnerName();
	}

};
};