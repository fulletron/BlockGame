#ifndef __STATE_H_
#define __STATE_H_

#include <Utilities\definitions_types.h>

namespace GS {
namespace State {

	/**
	* This is a State of the machine provided by the template.
	*/
template <typename MACHINE> class IState
{
public:
	virtual ~IState(){}
	virtual _UINT32 onEnter(MACHINE *) = 0;
	virtual _UINT32 onUpdate(MACHINE *) = 0;
	virtual _UINT32 onExit(MACHINE *) = 0;
};


// ENSURE the \ is the last character
/**
* ADDS NO MEMBER VARIABLES
* Creates the virtual functions for all of IState.
*/
#define IMPLEMENT_ISTATE(MACHINE)		\
public:									\
	virtual _UINT32 onEnter(MACHINE *);	\
	virtual _UINT32 onUpdate(MACHINE *);	\
	virtual _UINT32 onExit(MACHINE *);

/**
* ADDS NO MEMBER VARIABLES
* Creates the virtual functions for all of IState.
* EXCEPT UPDATE, EXPECTATION IS TO BE OVERWRITTEN
*/
#define IMPLEMENT_ISTATE_NOUPDATE(MACHINE)		\
public:									\
	virtual _UINT32 onEnter(MACHINE *);	\
	virtual _UINT32 onExit(MACHINE *);



/*
template<typename T> class A { int x; }; // primary template
template<class T> class A<T*> { long x; }; // partial specialization

// class template with a template template parameter V
template<template<typename> class V> class C
{
	V<int> y; // uses the primary template
	V<int*> z; // uses the partial specialization
};

C<A> c; // c.y.x has type int, c.z.x has type long

// class template with a template template parameter V
template<template<typename> class IS> class IFState
{
	IS<T> y;
};
*/

};
};

#endif