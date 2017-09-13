#ifndef __IDIMENSIONABLE_H_
#define __IDIMENSIONABLE_H_

#include <Utilities\definitions_types.h>

namespace GS {
namespace Graphics {

class IDimensionable {
public:
	virtual _VEC2D<_INT32> getPixelDimensions() const = 0;
};


};

};

#endif