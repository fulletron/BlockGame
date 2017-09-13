#ifndef __IRESOURCEREQUIRER_H_
#define __IRESOURCEREQUIRER_H_

#include <Utilities/definitions_types.h>

namespace GS {
namespace Resource {

/**
* Classes derived from this require specific resources
*/
class IResourceRequirer
{
public:
	virtual _BOOL areResourcesReady() = 0;
};

};
};
#endif
