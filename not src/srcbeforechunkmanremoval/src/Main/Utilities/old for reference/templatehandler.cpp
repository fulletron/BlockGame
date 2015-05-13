#include "templatehandler.h"
#include <assert.h>

namespace GS {
namespace Utilities {

template <typename T>
void Handle<T>::init( unsigned int a_index )
{
	assert( isNull() );
	assert( index <= MAX_INDEX );

	static unsigned int s_autoMagic = 0;
	if( ++s_autoMagic > MAX_MAGIC )
	{
		s_autoMagic = 1;		// 0 is used for null handle
	}

	m_index = a_index;
	m_magic = s_autoMagic;
}



};
};