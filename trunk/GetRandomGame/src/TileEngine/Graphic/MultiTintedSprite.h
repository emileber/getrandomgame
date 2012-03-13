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

	virtual void SetColor(int cornerX, int cornerY, GLfloat red, GLfloat green,
			GLfloat blue);

	virtual Color3f *GetColor(int cornerX, int cornerY) const;

	virtual void Draw(GLfloat x, GLfloat y, GLfloat scale = 1,
			GLfloat rotation = 0, GLfloat red = 1, GLfloat green = 1,
			GLfloat blue = 1, GLfloat alpha = 1);
protected:
	//Color3f *mBottomLeftColor, *mBottomRightColor, *mTopRightColor, *mTopLeftColor;
	Color3f *mColorArray[2][2];

};

} /* namespace TileEngine */
#endif /* MULTITINTEDSPRITE_H_ */
