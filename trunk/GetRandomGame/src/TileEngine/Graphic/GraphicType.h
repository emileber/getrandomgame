/*
 * GraphicType.h
 *
 *  Created on: 2012-01-25
 *      Author: Emile
 *
 *      Some basic types, may change
 */


#ifndef GTYPES
#define GTYPES

namespace TileEngine {


/**
 * Layer enum
 *  Layers go from 0 to 11 (makes a total of 12)
 *  Somes are not define, wich let them available for future uses
 */
enum LayerNumber {
	LAYER_BACKGROUND = 1,
	LAYER_GROUND = 4,
	LAYER_PEOPLE = 6,
	LAYER_FOREGROUND = 8,
	LAYER_MENU = 10,
	LAYER_DEBUG = 11
};

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
