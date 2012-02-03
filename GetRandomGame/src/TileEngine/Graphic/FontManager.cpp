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

#include "FontManager.h"
//#include "SDL_rwops_zzip.h"
#include "Graphic.h"
#include "Camera.h"

using namespace std;

namespace TileEngine {
//
// Default constructor
/// @params Filename a std::string
Font::Font(std::string Filename) {
	m_Static = true;

	if (Filename != "") {
		Load(Filename);
	} else {
		m_Font = NULL;
	}
}

//
// Default destructor
//
Font::~Font() {
	TTF_CloseFont(m_Font);
	//Delete();
}

//
// Loads a font from a zip
/// @param Filename a std::string
///
//	bool Font::LoadFromZip(std::string Filename)
//	{
//		std::string mode = "rb";
//
//		//zziplib specific code
//		ZZIP_FILE* fp = zzip_fopen(Filename.c_str(),0);
//
//		//holds the file data
//		char buf[17];
//
//		//length of the file
//		int len = 0;
//
//		//stores the files data
//		unsigned char data[200000];
//
//		if (!fp)
//		{
//			cout << "Error loading font from zip '" << Filename << "' " << endl;
//			return false;
//		}
//		else
//		{
//			int n;
//
//			// read chunks of 16 bytes into buf
//			while (0 < (n = zzip_read(fp, buf, 16)))
//			{
//				if( len + n > 200000 )
//				{
//					cout << "Font file is bigger than the buffer, change the size in FontManager.cpp" << endl;
//					return false;
//				}
//
//				for(int i = 0; i < n; i++)
//				{
//					data[len + i] = (unsigned char) buf[i];
//				}
//
//				len += n;
//			}
//		}
//
//		zzip_file_close (fp);
//
//		m_Font = new FTGLPixmapFont( data, len );
//
//		if( m_Font->Error() )
//		{
//			cout << "Error loading font from zip '" << Filename << "' " << m_Font->Error() <<  " " << len << endl;
//			delete m_Font;
//			m_Font = NULL;
//
//			return false;
//		}
//		else
//		{
//			//set a default size
//			m_Font->FaceSize(20);
//			Singleton<FontManager>::GetSingletonPtr()->RegisterFont(this);
//		}
//
//		return true;
//	}

//
// Loads a font from a file
/// @param Filename a std::string
///
bool Font::Load(std::string filename) {
	m_Font = TTF_OpenFont(filename.c_str(), 20);
	;

	if (m_Font) {
		cout << "Error loading Font '" << filename << "'" << endl;
		TTF_CloseFont(m_Font);
		m_Font = NULL;
	} else {
		//set a default size
		//m_Font->FaceSize(20);
		FontManager::getInstance()->RegisterFont(this);
	}

	return true;
}

//
// Unregisters the font and deletes it from memory
//
void Font::Delete() {
	FontManager::getInstance()->UnRegisterFont(this);
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
//GLfloat Font::GetHeight() {
//	return (GLfloat) m_Font->LineHeight();
//}

//
// returns the width of the string
/// @param text a std::string
/// @return width of the string
///
//GLfloat Font::GetWidth(std::string text) {
//	return (GLfloat) m_Font->Advance(text.c_str());
//}

///////////////////////////////////////////////
// Start Font Manager Code
///////////////////////////////////////////////

//
// Default constructor
//
FontManager::FontManager() {
	m_Fonts.clear();
}

//
// Default destructor
//
FontManager::~FontManager() {
	DeleteFonts();
	m_Fonts.clear();
}

//
// Deletes all fonts form memory
//
void FontManager::DeleteFonts() {
	for (uint i = 0; i < m_Fonts.size(); i++) {
		delete m_Fonts[i];
	}
}

//
// Adds a font to the manager
//
void FontManager::RegisterFont(Font* font) {
	//don't add nulls
	if (font == NULL) {
		return;
	}

	//check to see if its already loaded in the manager
	for (uint i = 0; i < m_Fonts.size(); i++) {
		if (font->m_Font == m_Fonts[i]->m_Font) {
			return;
		}
	}

	//add the font to management
	m_Fonts.push_back(font);
}

//
// Removes a font from the manager and deletes it from memory
//
void FontManager::UnRegisterFont(Font* font) {
	//don't add nulls
	if (font == NULL) {
		return;
	}

	int place = -1;

	//check to see if its loaded in the manager
	for (uint i = 0; i < m_Fonts.size(); i++) {
		if (font->m_Font == m_Fonts[i]->m_Font) {
			place = (int) i;
			break;
		}
	}

	//abort if not found
	if (place == -1) {
		return;
	}

	//if the place is at the end of the vector just delete it
	if ((place + 1) == (int) m_Fonts.size()) {
		delete m_Fonts[place];
		m_Fonts.erase(m_Fonts.begin() + place);
	} else // we need to have the font swap places with the last element
	{
		delete m_Fonts[place];
		m_Fonts[place] = m_Fonts[m_Fonts.size()];
		m_Fonts.erase(m_Fonts.end());
	}
}
}
