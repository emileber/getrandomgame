/*
 * Sprite.cpp
 *
 *  Created on: 2012-02-29
 *      Author: Emile
 */

#include "Manager.h"

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
	delete mRect;
}

void Sprite::SetTexture(std::string filename) {
	SetTexture(Manager<Texture>::getInstance()->LoadRessource(filename));
}

//void Sprite::Draw(float x, float y, float scale, float rotation, float red,
//		float green, float blue, float alpha) {
//	if (mRect != NULL) {
//		mTexture->DrawSection(x, y, mRect, scale, rotation, red, green, blue,
//				alpha);
//	} else {
//		mTexture->Draw(x, y, scale, rotation, red, green, blue, alpha);
//	}
//}

void Sprite::Draw(float x, float y, float scale, float rotation,
		const Color3f *color, float alpha) const{
	if (color != NULL) {
		mTexture->DrawSection(x, y, mRect, scale, rotation, color->r, color->g,
				color->b, alpha);
	} else {
		mTexture->DrawSection(x, y, mRect, scale, rotation, 1, 1, 1, alpha);
	}
}

} /* namespace TileEngine */
