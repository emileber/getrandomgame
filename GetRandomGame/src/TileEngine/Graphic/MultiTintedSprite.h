/*
 * MultiTintedSprite.h
 *
 *  Created on: 2012-03-12
 *      Author: Emile
 */

#ifndef MULTITINTEDSPRITE_H_
#define MULTITINTEDSPRITE_H_

#include "Sprite.h"
#include "GraphicType.h"

namespace TileEngine {

/*
 *
 */
class MultiTintedSprite: public Sprite {
public:
	MultiTintedSprite() :
			Sprite() {
		Init();
	}
	MultiTintedSprite(std::string fontFileName, SectionRect* rect) :
			Sprite(fontFileName, rect) {
		Init();
	}
	MultiTintedSprite(Texture* texture, SectionRect* rect) :
			Sprite(texture, rect) {
		Init();
	}
	virtual ~MultiTintedSprite();

	virtual void Init();

	virtual void SetColor(int cornerX, int cornerY, Color3f *color);

	virtual void SetColor(int cornerX, int cornerY, float red, float green,
			float blue);

	virtual Color3f *GetColor(int cornerX, int cornerY) const;

	virtual void Draw(float x, float y, float scale = 1, float rotation = 0,
			const Color3f * color = NULL, float alpha = 1);
protected:
	//Color3f *mBottomLeftColor, *mBottomRightColor, *mTopRightColor, *mTopLeftColor;
	Color3f *mColorArray[2][2];

};

} /* namespace TileEngine */
#endif /* MULTITINTEDSPRITE_H_ */
