#ifndef __ILIBRARY_H_
#define __ILIBRARY_H_

#include <Utilities\definitions_types.h>

namespace GS {
namespace Library {

/**
* All the functionality necessary from the stage regarding the library.
*/
class IStageToLibraryLiaison
{
public:
	/**
	* Tells the library to prepare a resource from the game
	* files located on the computer.
	*/
	virtual _UINT32 subscribe(const _UINT64 & a_id) = 0;

	/**
	* Tells the library it needs a resource in one less place.
	*/
	virtual _UINT32 unsubscribe(const _UINT64 & a_id) = 0;
};


/**
* ILibrary is the Resource library.
*/
class ILibrary
{
public:
	/**
	* Initializes the library
	*/
	virtual _UINT32 init() = 0;

	/**
	* Destroys the library
	*/
	virtual _UINT32 shutdown() = 0;

	/**
	* Tells the library to prepare a resource from the game
	* files located on the computer.
	*/
	//virtual _UINT32 subscribe( const _UINT64 & a_id ) = 0;

	/**
	* Tells the library it needs a resource in one less place.
	*/
	//virtual _UINT32 unsubscribe( const _UINT64 & a_id ) = 0;
};

/**
* Derived objects can subscribe and unsubscribe to resources in the library
*/
class ISubscriber
{
selective:
	/**
	* Tells the library to prepare a resource from the game
	* files located on the computer.
	*/
	virtual _UINT32 __subscribe(const _UINT64 & a_id) = 0;
//	virtual _UINT32 __subscribe(ILibrary * a_lib, const _UINT64 & a_id) = 0;

	/**
	* Tells the library it needs a resource in one less place.
	*/
	virtual _UINT32 __unsubscribe(const _UINT64 & a_id) = 0;
//	virtual _UINT32 __unsubscribe(ILibrary * a_lib, const _UINT64 & a_id) = 0;
};



};
};

#endif
