#ifndef __FONTHELPERS_H_
#define __FONTHELPERS_H_

#include <Graphics/openglincludes.h>

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

struct Vertex2_t
{
	float x,y;

	 /// Default constructor that sets components to 0.
	Vertex2_t() : x(0), y(0) {}
 
	/// Constructs a 2D vector from components.
	Vertex2_t(float x, float y) : x(x), y(y) {}
 
	/// Copy constructor.
	Vertex2_t(const Vertex2_t& Copy) : x(Copy.x), y(Copy.y) {}
 
	/// Assignment operator.
	inline Vertex2_t& operator=(const Vertex2_t& Copy)
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

};
};

#endif