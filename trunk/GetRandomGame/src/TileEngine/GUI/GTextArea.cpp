/*
 * GTextArea.cpp
 *
 *  Created on: 2012-03-13
 *      Author: Emile
 */

#include "GTextArea.h"
#include "Graphic/Graphic.h"
#include "Graphic/Camera.h"
#include <sstream>

namespace TileEngine {

GTextArea::GTextArea() {
	Init();

}

GTextArea::~GTextArea() {
	// TODO Auto-generated destructor stub
}

void GTextArea::Init() {
	GItem::Init();
	mFont = NULL;
	mColorDefault = new Color3f(1, 1, 1);
	mCurrentLine = new GTextLine();
	mSpaceWidth = 0;
	SetFontSize(20);

}

void GTextArea::SetFont(std::string fontFileName) {
	SetFont(Manager<Font>::getInstance()->LoadRessource(fontFileName));
}

void GTextArea::SetFont(const Font *font) {
	mFont = font;
	mSpaceWidth = mFont->GetWidth(" ") * (mPointSize / mFont->GetHeight());
}

void GTextArea::PrintLine(std::string text, Color3f *color) {
	if (text == "") {
		return;
	}
	if (color == NULL) {
		color = mColorDefault;
	}

	GLfloat scale = (mPointSize / mFont->GetHeight());

	std::stringstream ss(text);
	std::string word;
	int currentWidth = mCurrentLine->Width()
						+ (mCurrentLine->GetWordCount() * mSpaceWidth);

	while (std::getline(ss, word, ' ')) {

		GWord* newWord = new GWord(word, mFont->GetWidth(word) * scale, color);

		if ((currentWidth + mSpaceWidth + newWord->Width()) <= mWidth) {
			// append to the current line.
			mCurrentLine->PushWord(newWord, newWord->Width());
			currentWidth +=  mSpaceWidth + newWord->Width();
		} else {
			// the line can't take that last word
			// so push the line in the stack and start a new one
			mTextVector.push_back(mCurrentLine);
			mCurrentLine = new GTextLine();
			mCurrentLine->PushWord(newWord, newWord->Width());
			currentWidth = newWord->Width();
		}

	}

	mTextVector.push_back(mCurrentLine);
	mCurrentLine = new GTextLine();
	//GWord

	//mTextVector.push_back(text);

}

void GTextArea::Update() {
}

/**
 * Draw
 * Render each line
 */
void GTextArea::Draw(int x, int y) {
	//std::cout << "HERE" << std::endl;

	if (!mIsStatic) {
		x = Camera::getInstance()->GetX() + x;
		y = Camera::getInstance()->GetY() + y;
	}

	// background (test line)
	Graphic::getInstance()->DrawFilledRectangle(x + mXoffset, y + mYoffset,
			mWidth, mHeight, 0, 0, 0, 0.75f, true);

	GLfloat scale = (mPointSize / mFont->GetHeight());
	//GLfloat scale = 1.0f;

	// Number of line to draw
	int nbLine = mTextVector.size();
	int lineIterator = nbLine - 1;
	// custom font height (for the look)
	int fontHeight = mFont->GetHeight() * 0.9f * scale;

	// draw each line until the Text Area is full
	for (int i = 0; i < nbLine; i++) {

		if ((i * fontHeight) > (mHeight - fontHeight)) {
			// si la prochaine ligne va depasser le top de
			// l'area, stop drawing
			break;
		}

		// calcul de l'offset pour chaque ligne
		int lineY = mYoffset + y + (i * fontHeight);

//		Graphic::getInstance()->DrawRectangle(x + mXoffset, lineY,
//				mFont->GetWidth(mTextVector.at(i)) * scale, fontHeight, 0, 1, 0, 1, 2,
//				true);

		// Render that line of text
		mTextVector.at(lineIterator)->Draw(mFont, mXoffset + x, lineY, scale,
				mAlpha);
		lineIterator--;

//		mFont->Draw(mTextVector.at(i), mXoffset + x, lineY, scale,
//				mColorDefault->r, mColorDefault->g, mColorDefault->b, mAlpha);
	} // end of line drawing FOR

	GItem::Draw(mXoffset + x, mYoffset + y);
}

} /* namespace TileEngine */
