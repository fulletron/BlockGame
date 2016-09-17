#ifndef __STATE_H_
#define __STATE_H_

#include <Utilities/typedefinitions.h>

namespace GS {
namespace State {

template <typename T>
class IState
{
public:
	virtual ~IState(){}
	virtual _INT32 onEnter(T *) = 0;
	virtual _INT32 onUpdate(T *) = 0;
	virtual _INT32 onExit(T *) = 0;
};


// ENSURE the \ is the last character
#define IMPLEMENT_ISTATE(MACHINE)		\
public:									\
	virtual _INT32 onEnter(MACHINE *);	\
	virtual _INT32 onUpdate(MACHINE *);	\
	virtual _INT32 onExit(MACHINE *);	\


// I AM NOT A FAN OF THIS IMPL
#define IMPLEMENT_ISTATE2(MACHINE)		\
selective:								\
	MACHINE * m_pParentStateMachine;	\
public:									\
	void setParentStateMachine(MACHINE * a_m) {m_pParentStateMachine = a_m;} \
	virtual _INT32 onEnter(MACHINE *);	\
	virtual _INT32 onUpdate(MACHINE *);	\
	virtual _INT32 onExit(MACHINE *);	\

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