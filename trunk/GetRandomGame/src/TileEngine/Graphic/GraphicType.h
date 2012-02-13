#ifndef GTYPES
#define GTYPES

#include "Global.h"

namespace TileEngine {
///
///Defines a Point with coordinates x and y
///
struct FPoint {
	GLfloat x; /**< The X coordinate */
	GLfloat y; /**< The Y coordinate */
};

///
///A basic rectangle structure
///
struct RectStruct {
	GLfloat top; /**< The top most point on the rectangle 	*/
	GLfloat right; /**< The right most point on the rectangle 	*/
	GLfloat bottom; /**< the bottom most point on the rectangle 	*/
	GLfloat left; /**< The left most point on the rectangle 	*/
};

struct SectionRect {
	GLfloat x; /**< The X coordinate */
	GLfloat y; /**< The Y coordinate */
	GLfloat w;
	GLfloat h;
};

struct Color3f {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};


}

#endif
