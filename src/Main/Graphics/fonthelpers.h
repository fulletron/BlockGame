#ifndef __FONTHELPERS_H_
#define __FONTHELPERS_H_

#include <Graphics/openglincludes.h>

#define VBO_OFFSET(count, vertex, field) \
    (void*)((count * sizeof(vertex)) + (long int)&(((vertex*)NULL)->field))

namespace GS {
namespace Graphics {

struct Vector2_t
{
	float x,y;

	 /// Default constructor that sets components to 0.
	Vector2_t() : x(0), y(0) {}
 
	/// Constructs a 2D vector from components.
	Vector2_t(float x, float y) : x(x), y(y) {}
 
	/// Copy constructor.
	Vector2_t(const Vector2_t& Copy) : x(Copy.x), y(Copy.y) {}
 
	/// Assignment operator.
	inline Vector2_t& operator=(const Vector2_t& Copy)
	{ x = Copy.x; y = Copy.y; return (*this); }
};

/// A rectangle at a certain point in space.
struct Rect_t
{
	Rect_t(float x, float y, int w, int h) : x(x), y(y), w(w), h(h) {}
	Rect_t() : x(0.f), y(0.f), w(0), h(0) {}
 
	float x, y;
	int w, h;
};

/**
* Represents a 32-bit floating point color (RGBA).
* Limited to the range [0, 1].
**/
struct Color4f_t
{
	Color4f_t() : r(1), g(1), b(1), a(1) {}
	Color4f_t(float r, float g, float b, float a) :
	r(r), g(g), b(b), a(a) {}
	float r, g, b, a;
};

// TODO ::
// this only requires 3 floats for color
struct Vertex2_t
{
	Vector2_t Position;
	Vector2_t TexCoord;
	Color4f_t Color;
};


};
};

#endif