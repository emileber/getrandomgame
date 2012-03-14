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
	//mIsStatic = true;
	mFont = NULL;
}

//
// Default destructor
//
Font::~Font() {
	delete mFont;
}

//
// Loads a font from a file
/// @param Filename a std::string
///
void Font::Load(std::string filename) {
	//mFont = ftglCreatePixmapFont("/home/user/Arial.ttf");
	//FTGLPixmapFont font(filename.c_str());

	if (filename != "") {
		mFilename = filename;

		//mFont = new FTPixmapFont(filename.c_str());
		mFont = new FTTextureFont(filename.c_str());

		if (mFont->Error()) {
			cout << "Error loading Font '" << filename << "'" << endl;
			delete mFont;
			mFont = NULL;
			mIsLoaded = false;
		} else {
			//set a default size
			mFont->FaceSize(40);
			mIsLoaded = true;
		}

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
/// @param scale a GLfloat
/// @param Red a GLfloat
/// @param Green a GLfloat
/// @param Blue a GLfloat
/// @param Alpha a GLfloat
///
void Font::Draw(std::string text, GLfloat x, GLfloat y, GLfloat scale,
		GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) const {
	//do nothing if the font isn't setup
	if (mFont == NULL) {
		cout << "Font::Draw() error, font is NULL, can't draw..." << endl;
		return;
	}

	glPushMatrix();

	glLoadIdentity();

	Graphic::getInstance()->SetCurrentTexture(0);

	//move with the camera if needed
//	if (!mIsStatic) {
//		x = Camera::getInstance()->GetX() + x;
//		y = Camera::getInstance()->GetY() + y;
//	}

	// Correct the Y position so letter
	// like p,y,g,q and j don't get below
	// their belonging Y position.
	y -= (mFont->Descender() * scale);

	std::string tempStr;

	//fix bug (WITH PIXMAPFONT) in ftgl when part of the text is offscreen nothing draws
//	while ((x < 0) && (text.length() != 0)) {
//		tempStr = text[0];
//		x += scale * GetWidth(tempStr);
//		text = text.substr(1, text.length());
//	}
	//glEnable(GL_MULTISAMPLE);

	glColor4f(red, green, blue, alpha);

	glRasterPos2i((int) x, (int) y); // for FTPixmapFont
	glTranslatef(x, y, 0.0f); // for FTTextureFont
	glScaled(scale, scale, 0);

	mFont->Render(text.c_str());

	glPopMatrix();

	//reset the color
	glColor3f(1.0f, 1.0f, 1.0f);
}

//
// Sets the font's face size
/// @param Size a uint
///
void Font::SetSize(uint size) {
	if (mFont == NULL) {
		return;
	}

	mFont->FaceSize(size);

	mFaceSize = size;
}

//
// Sets if the text moves with the camera or not, default is true
/// @param Static a bool
///
//void Font::IsStatic(bool isStatic) {
//	mIsStatic = isStatic;
//}

//
// returns the height of the font
/// @return Width of the string
///
GLfloat Font::GetHeight() const {
	return (GLfloat) mFont->LineHeight();
}

//
// returns the width of the string
/// @param text a std::string
/// @return width of the string
///
GLfloat Font::GetWidth(const std::string & text) const {
	return (GLfloat) mFont->Advance(text.c_str());
}

}
