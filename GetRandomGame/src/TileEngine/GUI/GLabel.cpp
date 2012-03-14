/*
 * GLabel.cpp
 *
 *  Created on: 2012-02-29
 *      Author: Emile
 */

#include "GLabel.h"
#include "Graphic/Camera.h"
#include <string>

namespace TileEngine {

GLabel::GLabel() {
	Init();

}

GLabel::GLabel(std::string text, std::string fontFileName) {
	Init();
	SetFont(fontFileName);
	SetText(text);
	SetFontSize(50);

}

GLabel::~GLabel() {
	// TODO Auto-generated destructor stub
}

void GLabel::Init() {
	GItem::Init();
	mFont = NULL;
	mText = "";
	mColor = new Color3f(0, 0, 0);
	mAlpha = 1.0f;
	mPointSize = 50;
}

/**
 * Uses the texture Manager template Singleton to load
 * the font if not already loaded. Then keep a pointer
 * to it through the Setter function.
 * @param font file name as a string
 */
void GLabel::SetFont(std::string fontFileName) {
	SetFont(Manager<Font>::getInstance()->LoadRessource(fontFileName));
}

void GLabel::SetFont(const Font* font) {
	mFont = font;
}

/**
 * Takes 3 integers between 0 and 255
 * Then convert the value in a %
 * as a Float
 * @param r as red value between 0 and 255 (int)
 * @param g as gree value between 0 and 255 (int)
 * @param b as blue value between 0 and 255 (int)
 */
void GLabel::SetColor(GLfloat r, GLfloat g, GLfloat b) {
	mColor = new Color3f((r / 255), (g / 255), (b / 255));
}

/**
 * this sets the text
 * Be aware that it also gets the width the text
 * will take and that this operation may be a little
 * consumming over time.
 */
void GLabel::SetText(std::string text) {
	mText = text;
	Width(mFont->GetWidth(mText) * (mPointSize / mFont->GetHeight()));
}

void GLabel::Update() {
}

void GLabel::Draw(int x, int y) {

	if (!mIsStatic) {
		x = Camera::getInstance()->GetX() + x;
		y = Camera::getInstance()->GetY() + y;
	}

	mFont->Draw(mText, mXoffset + x, mYoffset + y,
			(mPointSize / mFont->GetHeight()), mColor->r, mColor->g, mColor->b,
			mAlpha);
}

} /* namespace TileEngine */
