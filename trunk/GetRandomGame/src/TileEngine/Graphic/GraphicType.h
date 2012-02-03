#ifndef GTYPES
#define GTYPES

#include "Global.h"

namespace TileEngine
{
	///
	///Defines a Point with coordinates x and y
	///
	struct sPoint
	{
		GLfloat x;	/**< The X coordinate */
		GLfloat y;	/**< The Y coordinate */
	};

	///
	///A basic rectangle structure
	///
	struct sRect
	{
		GLfloat Top; 	/**< The top most point on the rectangle 	*/
		GLfloat Right; 	/**< The right most point on the rectangle 	*/
		GLfloat Bottom; /**< the bottom most point on the rectangle 	*/
		GLfloat Left; 	/**< The left most point on the rectangle 	*/
	};
}

#endif
