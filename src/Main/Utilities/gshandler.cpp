#include "gshandler.h"

namespace GS {
namespace Utilities {

template<typename DATA_TYPE>
GSHandler<DATA_TYPE>::GSHandler()
{

}

template<typename DATA_TYPE>
_INT32 GSHandler<DATA_TYPE>::init( Frame * const a_pFrame, const _UINT32 a_size )
{
	return 0;
}

template<typename DATA_TYPE>
void GSHandler<DATA_TYPE>::shutdown()
{
}

template<typename DATA_TYPE>
_UINT32 GSHandler<DATA_TYPE>::insert( DATA_TYPE a_data )
{
	return 0;
}

template<typename DATA_TYPE>
DATA_TYPE GSHandler<DATA_TYPE>::get( const _UINT32 a_key )
{
	return 0;
}

template<typename DATA_TYPE>
void GSHandler<DATA_TYPE>::remove( const _UINT32 a_key )
{
}

};
};