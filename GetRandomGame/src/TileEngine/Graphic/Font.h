/**
 *  File: cFontManager.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains everything font related
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#ifndef FONTMAN
#define FONTMAN


#include "Global.h"
#include "Ressource.h"
#include <vector>
#include "FTGL/ftgl.h"
//#include "FTGL/FTGLPixmapFont.h"

namespace TileEngine {
///
/// Holds all the information about a font and its functions
///
class Font : public Ressource{

public:
	/// Default Constructor
	Font();
	/// Default Destructor
	~Font();

	/// Loads a font from file
	virtual void load(std::string filename);

	/// Deletes a font from memory
	void Delete();

	/// Draws a font
	void Draw(std::string text, GLfloat x, GLfloat y, GLfloat red = 1,
			GLfloat green = 1, GLfloat blue = 1, GLfloat alpha = 1);
	/// Sets the face size of the font
	void SetSize(uint size);
	/// Sets if the font moves with the camera
	void SetStatic(bool isStatic);

	/// returns the height of the font
	GLfloat GetHeight();
	/// returns the width of the string
	GLfloat GetWidth(std::string text);

private:
	FTFont * m_Font; /**< Stores the font				*/
	bool m_Static; /**< Tells if the font moves with the camera 	*/
	int m_FaceSize; /**< Stores the size of the font		*/
};
} // namespace end

#endif
