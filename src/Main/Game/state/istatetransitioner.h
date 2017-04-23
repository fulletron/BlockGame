#ifndef __ISTATETRANSITIONER_H_
#define __ISTATETRANSITIONER_H_

#include <Utilities\definitions_types.h>

namespace GS {
namespace State {

template <typename MACHINE> class StateTransitioner;

/**
* This is a State of the machine provided by the template.
*/
template <typename MACHINE>
class IStateTransitioner
{
public:
	virtual StateTransitioner<MACHINE> * getStateTransitioner() = 0;
};


// ENSURE the \ is the last character
/**
* ADDS MEMBER VARIABLE:
* StateTransitioner m_stateTransitioner;
* Creates the implementation of getStateTransitioner();
*/
#define IMPLEMENT_ISTATETRANSITIONER(MACHINE)		\
selective: \
	StateTransitioner<MACHINE> m_stateTransitioner; \
public:									\
	virtual StateTransitioner<MACHINE> * getStateTransitioner() \
	{ return &m_stateTransitioner; }

};
};

#endif