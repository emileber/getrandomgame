/**
 *  File: cCamera.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains defination of a camera
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#ifndef CAMERA
#define CAMERA

#include "Global.h"

namespace TileEngine {
///
/// The camera handles what the view is looking at
///
class Camera: public Singleton<Camera> {
	friend class Singleton<Camera>;
public:
	/// Default Constructor
	Camera();
	/// Default Destructor
	~Camera();

	/// Moves the camera by x and y units
	void move(float x, float y);
	/// Sets the absolute position of the camera
	void setPosition(float x, float y);

	/// Returns the x cooridinate of the camera
	float GetX();
	/// Returns the y  cooridinate of the camera
	float GetY();
private:
	float m_Xpos; /**< The x position of the camera 	*/
	float m_Ypos; /**< The y position of the camera 	*/
};
}

#endif
