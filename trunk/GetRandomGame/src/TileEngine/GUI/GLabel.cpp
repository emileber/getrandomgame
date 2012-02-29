/*
 * GLabel.cpp
 *
 *  Created on: 2012-02-29
 *      Author: Emile
 */

#include "GLabel.h"
#include <string>

namespace TileEngine {

GLabel::GLabel() {
	Init();

}

GLabel::GLabel(std::string text, std::string fontFileName) {
	Init();
	mText = text;
	SetFont(fontFileName);

}

GLabel::~GLabel() {
	// TODO Auto-generated destructor stub
}

void GLabel::Init() {
	GMenuItem::Init();
	mFont = NULL;
	mText = "";
	mColor = new Color3f(0, 0, 0);
	mAlpha = 1.0f;
	mPointSize = 12;
}

void GLabel::Update() {
}

void GLabel::Draw(int x, int y) {
	mFont->Draw(mText, mXoffset + x, mYoffset + y, mColor->r, mColor->g, mColor->b, mAlpha);
}

void GLabel::SetFont(std::string fontFileName) {
	SetFont(Manager<Font>::getInstance()->LoadRessource(fontFileName));
}

void GLabel::SetAlpha(int alpha) {
	mAlpha = (GLfloat) (alpha / 255);
}

void GLabel::SetColor(int r, int g, int b) {
	mColor = new Color3f((r / 255), (g / 255), (b / 255));
}

} /* namespace TileEngine */
