/*
 * MultiTintedSprite.cpp
 *
 *  Created on: 2012-03-12
 *      Author: Emile
 */

#include "MultiTintedSprite.h"

namespace TileEngine {

MultiTintedSprite::~MultiTintedSprite() {
	// TODO Auto-generated destructor stub
}

void MultiTintedSprite::Init() {

	mColorArray[0][0] = new Color3f(1.0f, 1.0f, 1.0f);
	mColorArray[0][1] = new Color3f(1.0f, 1.0f, 1.0f);
	mColorArray[1][0] = new Color3f(1.0f, 1.0f, 1.0f);
	mColorArray[1][1] = new Color3f(1.0f, 1.0f, 1.0f);

}

void MultiTintedSprite::SetColor(int cornerX, int cornerY, Color3f *color) {
	if ((cornerX < 0) && (cornerX >= 2) && (cornerY < 0) && (cornerY >= 2)) {
		return;
	}
	mColorArray[cornerX][cornerY] = color;

}

void MultiTintedSprite::SetColor(int cornerX, int cornerY, float red,
		float green, float blue) {
	if ((cornerX < 0) && (cornerX >= 2) && (cornerY < 0) && (cornerY >= 2)) {
		return;
	}
	mColorArray[cornerX][cornerY] = new Color3f(red, green, blue);
}

Color3f * MultiTintedSprite::GetColor(int cornerX, int cornerY) const {
	if ((cornerX < 0) && (cornerX >= 2) && (cornerY < 0) && (cornerY >= 2)) {
		return NULL;
	}

	return mColorArray[cornerX][cornerY];

}

void MultiTintedSprite::Draw(float x, float y, float scale, float rotation,
		const Color3f * color, float alpha) {
//	printf("MultiTintedSprite colors:\n");
//	for (int xi = 0; xi < 2; xi++) {
//		for (int yi = 0; yi < 2; yi++) {
//			printf("corner(x, y) (%d, %d) : (r, g, b) (%f, %f, %f)\n", xi, yi,
//					mColorArray[xi][yi]->r, mColorArray[xi][yi]->g,
//					mColorArray[xi][yi]->b);
//		}
//	}

	if (color == NULL) {
		mTexture->DrawSection4Color(x, y, mRect, mColorArray[0][0],
				mColorArray[1][0], mColorArray[1][1], mColorArray[0][1], scale,
				rotation, alpha);
	} else {
		mTexture->DrawSection(x, y, mRect, scale, rotation, color->r, color->g,
				color->b, alpha);
	}
}

} /* namespace TileEngine */
