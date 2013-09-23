#ifndef __GSOBJECT_H_
#define __GSOBJECT_H_

#include "typedefinitions.h"
#include "gsvariant.h"

namespace GS {
namespace Utilities {

class GSMsg
{
public:
	GSVariant m_msgs[NUM_VARIANTS_PER_MSG];
};

class GSObject
{
public:
	virtual int handleMsg( const GSMsg & a_msg ) = 0;
};

struct _GSObjectPair
{
	_GSObjectPair( GSObject * const a_pGSObject, const _INT64 a_ownerFrameName )
	: pGSObject(a_pGSObject), ownerFrameName( a_ownerFrameName )
	{}
	GSObject * pGSObject;
	_INT64 ownerFrameName;
};

struct _GSKeyPair
{
	_GSKeyPair( const _UINT32 a_key, const _INT64 a_ownerFrameName )
	: key(a_key), ownerFrameName( a_ownerFrameName )
	{}	
	_UINT32 key;
	_INT64 ownerFrameName;
};

};
};

#endif
