/**
 *  File: FontManager.cpp
 *  Project: Kore-Engine
 *
 *  Description: This file contains everything font related
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */
//#include "config.h"
#include "Font.h"
//#include "SDL_rwops_zzip.h"
#include "Graphic.h"
#include "Camera.h"

using namespace std;




namespace TileEngine {
//
// Default constructor
/// @params Filename a std::string
Font::Font() {
	m_Static = true;
	m_Font = NULL;
}

//
// Default destructor
//
Font::~Font() {
	delete m_Font;
}

//
// Loads a font from a file
/// @param Filename a std::string
///
void Font::load(std::string filename) {
	//m_Font = ftglCreatePixmapFont("/home/user/Arial.ttf");
	//FTGLPixmapFont font(filename.c_str());
	//m_Font = new FTPixmapFont(filename.c_str());
	//m_Font = new FTTextureFont(filename.c_str());
	m_Font = new FTHaloFont(filename.c_str());

	if (m_Font->Error()) {
		cout << "Error loading Font '" << filename << "'" << endl;
		delete m_Font;
		m_Font = NULL;
	} else {
		//set a default size
		m_Font->FaceSize(20);
	}
}

//
// Unregisters the font and deletes it from memory
//
void Font::Delete() {
	//FontManager::getInstance()->UnRegisterFont(this);
}

//
// Draws text on the screen given the parameters
/// @param Text a std::string
/// @param X a GLfloat
/// @param Y a GLfloat
/// @param Red a GLfloat
/// @param Green a GLfloat
/// @param Blue a GLfloat
/// @param Alpha a GLfloat
///
void Font::Draw(std::string text, GLfloat x, GLfloat y, GLfloat red,
		GLfloat green, GLfloat blue, GLfloat alpha) {
	//do nothing if the font isn't setup
	if (m_Font == NULL) {
		return;
	}

	glLoadIdentity();

	//move with the camera if needed
	if (!m_Static) {
		x = Camera::getInstance()->getXposition() + x;
		y = Camera::getInstance()->getYposition() + y;
	}

	std::string tempStr;

	//fix bug in ftgl when part of the text is offscreen nothing draws
	while ((x < 0) && (text.length() != 0)) {
		tempStr = text[0];
		//x += GetWidth(tempStr);
		text = text.substr(1, text.length());
	}

	glColor4f(red, green, blue, alpha);
	glRasterPos2i((int) x, (int) y);

	glPushMatrix();

	//m_Font->Render(text.c_str());

	glPopMatrix();
}

//
// Sets the font's face size
/// @param Size a uint
///
void Font::SetSize(uint size) {
	if (m_Font == NULL) {
		return;
	}

	//m_Font->FaceSize(size);

	m_FaceSize = size;
}

//
// Sets if the text moves with the camera or not, default is true
/// @param Static a bool
///
void Font::SetStatic(bool isStatic) {
	m_Static = isStatic;
}

//
// returns the height of the font
/// @return Width of the string
///
GLfloat Font::GetHeight() {
	return (GLfloat) m_Font->LineHeight();
}

//
// returns the width of the string
/// @param text a std::string
/// @return width of the string
///
GLfloat Font::GetWidth(std::string text) {
	return (GLfloat) m_Font->Advance(text.c_str());
}

}
