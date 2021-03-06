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

#include <FTGL/ftgl.h>

#include "Global.h"
#include "Ressource.h"
#include <vector>

namespace TileEngine {
///
/// Holds all the information about a font and its functions
///
class Font: public Ressource {

public:
	/// Default Constructor
	Font();
	/// Default Destructor
	~Font();

	/// Loads a font from file
	virtual void Load(std::string filename);

	/// Deletes a font from memory
	virtual void Delete();

	/// Draws a font
	virtual void Draw(std::string text, float x, float y, float scale = 1,
			float red = 1, float green = 1, float blue = 1,
			float alpha = 1) const;

	/**
	 * Set the face size
	 * (Depracated) scale at draw instead
	 */
	virtual void SetSize(uint size);

	/// Sets if the font moves with the camera
//	virtual void IsStatic(bool isStatic);
//
//	virtual bool IsStatic() const {
//		return mIsStatic;
//	}

/// returns the height of the font
	float GetHeight() const;
	/// returns the width of the string
	float GetWidth(const std::string & text) const;

protected:
	FTFont * mFont; /**< Stores the font				*/
	//FTTextureFont* mFont;
	//bool mIsStatic; /**< Tells if the font moves with the camera 	*/
	int mFaceSize; /**< Stores the size of the font		*/
};
} // namespace end

#endif
