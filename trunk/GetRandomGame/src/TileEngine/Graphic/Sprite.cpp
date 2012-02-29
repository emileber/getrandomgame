/*
 * Sprite.cpp
 *
 *  Created on: 2012-02-29
 *      Author: Emile
 */

#include "Sprite.h"

namespace TileEngine {

Sprite::Sprite() {
	mTexture = NULL;
	mRect = NULL;

}

Sprite::Sprite(std::string filename, SectionRect *rect) {
	mTexture = Manager<Texture>::getInstance()->LoadRessource(filename);
	mRect = rect;
}

Sprite::~Sprite() {
	delete mTexture;
	delete mRect;
}

void Sprite::SetTexture(std::string filename) {
	SetTexture(Manager<Texture>::getInstance()->LoadRessource(filename));
}

void Sprite::Draw(GLfloat x, GLfloat y, GLfloat scale, GLfloat rotation,
		GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	if (mRect != NULL) {
		mTexture->DrawSection(x, y, mRect, scale, rotation, red, green, blue,
				alpha);
	} else {
		mTexture->Draw(x, y, scale, rotation, red, green, blue, alpha);
	}
}

} /* namespace TileEngine */
