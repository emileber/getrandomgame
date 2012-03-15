/*
 * GText.cpp
 *
 *  Created on: 2012-03-14
 *      Author: Emile
 */

#include "GText.h"
#include "Graphic/Graphic.h"

namespace TileEngine {

/**********************************************
 * GWord
 *
 */

void GWord::Draw(const Font *font, float x, float y, float scale,
		float alpha) const {

	font->Draw(mWord, x, y, scale, mColor->r, mColor->g, mColor->b, alpha);
}

/**********************************************
 * GTextLine
 *
 *
 */
GTextLine::GTextLine() {
	mWidth = 0;

}

GTextLine::~GTextLine() {
	// TODO Auto-generated destructor stub
}

void GTextLine::PushWord(const GWord* word, int width) {

	mTextLine.push_back(word);
	mWidth += width;

}

void GTextLine::Draw(const Font *font, float x, float y, float scale,
		float alpha) const {
	int spaceWidth = font->GetWidth(" ") * scale;
	float currentX = x;

	// Draw each word
	for (int i = 0; i < GetWordCount(); i++) {
		currentX += spaceWidth;

		// Green Rect around word
//		Graphic::getInstance()->DrawRectangle(currentX, y, mTextLine.at(i)->Width(),
//				font->GetHeight() * scale, 0, 1, 0, 1, 1, true);

		mTextLine.at(i)->Draw(font, currentX, y, scale, alpha);
		currentX += mTextLine.at(i)->Width();
		// Blue Rect around spaces
//		Graphic::getInstance()->DrawRectangle(currentX, y, spaceWidth,
//						font->GetHeight() * scale, 0, 0, 1, 1, 1, true);
	}

}

}/* namespace TileEngine */
