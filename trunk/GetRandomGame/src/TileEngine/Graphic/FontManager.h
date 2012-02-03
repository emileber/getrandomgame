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
//#include "FTGLPixmapFont.h"

namespace TileEngine {
///
/// Holds all the information about a font and its functions
///
class Font {
	friend class FontManager;

public:
	/// Default Constructor
	Font(std::string filename = "");
	/// Default Destructor
	~Font();

	/// Loads a font from a zip
	bool LoadFromZip(std::string filename);
	/// Loads a font from file
	bool Load(std::string filename);
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
	TTF_Font * m_Font; /**< Stores the font				*/
	bool m_Static; /**< Tells if the font moves with the camera 	*/
	int m_FaceSize; /**< Stores the size of the font		*/
};

///
/// This class manages all fonts
///
class FontManager: public Singleton<FontManager> {
	friend class Singleton<FontManager> ;

public:
	/// Default Constructor
	FontManager();
	/// Default Destructor
	~FontManager();

	/// Deletes all fonts from memory
	void DeleteFonts();
	/// Registers a font for management
	void RegisterFont(Font* font);
	/// Removes a font from management
	void UnRegisterFont(Font* font);
private:

	std::vector<Font*> m_Fonts; /**< Pointers to all the managed fonts */
};
}

#endif
