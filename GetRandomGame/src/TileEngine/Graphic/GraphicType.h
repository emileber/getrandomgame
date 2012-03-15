#ifndef GTYPES
#define GTYPES

#include "Global.h"

namespace TileEngine {
///
///Defines a Point with coordinates x and y
///
struct FPoint {
	float x; /**< The X coordinate */
	float y; /**< The Y coordinate */
};

///
///A basic rectangle structure
///
struct RectStruct {
	float top; /**< The top most point on the rectangle 	*/
	float right; /**< The right most point on the rectangle 	*/
	float bottom; /**< the bottom most point on the rectangle 	*/
	float left; /**< The left most point on the rectangle 	*/
};

struct SectionRect {
	float x; /**< The X coordinate */
	float y; /**< The Y coordinate */
	float w;
	float h;
	SectionRect(float xParam, float yParam, float wParam, float hParam): x(xParam), y(yParam), w(wParam), h(hParam){}
};

struct Color3f {
	float r;
	float g;
	float b;
	Color3f(float red, float green, float blue): r(red), g(green), b(blue){}
	Color3f(){}
};


}

#endif
