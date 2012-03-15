/**
 *  File: Camera.cpp
 *  Project: Kore-Engine
 *
 *  Description: This file defines what the view sees, ie the camera
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "Camera.h"

namespace TileEngine {
//
// Default Constructor
//
Camera::Camera() {
	m_Xpos = 0;
	m_Ypos = 0;
}

//
// Default Destructor
//
Camera::~Camera() {
}

//
// Moves the camera by x and y units
/// @param x a GLfloat
/// @param y a GLfloat
///
void Camera::move(float x, float y) {
	m_Xpos -= x;
	m_Ypos -= y;
}

//
// Sets the absolute position of the camera
/// @param x a GLfloat
/// @param y a GLfloat
///
void Camera::setPosition(float x, float y) {
	m_Xpos = -x;
	m_Ypos = -y;
}

//
// Returns the x cooridinate of the camera
/// @return X position of the camera
///
float Camera::GetX() {
	return m_Xpos;
}

//
// Returns the y cooridinate of the camera
/// @return Y position of the camera
///
float Camera::GetY() {
	return m_Ypos;
}
}
