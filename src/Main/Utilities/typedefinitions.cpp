#include "typedefinitions.h"

_INT64 CV8(char * a_name)
{
	return *reinterpret_cast<_INT64*>(&a_name[0]);
}