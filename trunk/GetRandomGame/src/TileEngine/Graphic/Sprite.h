/*
 * Sprite.h
 *
 *  Created on: 2012-02-29
 *      Author: Emile
 *
 *      Handle a Texture and a rectangle to easily
 *      draw only one part of a texture
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "Texture.h"

namespace TileEngine {

/*
 *
 */
class Sprite {
public:
	Sprite();
	Sprite(std::string, SectionRect*);
	Sprite(Texture* texture, SectionRect* rect) {
		SetTexture(texture);
		SetRect(rect);
	}
	virtual ~Sprite();

	virtual void SetTexture(std::string);
	virtual void SetTexture(const Texture* texture) {
		mTexture = texture;
	}

	virtual void SetRect(SectionRect* rect) {
		mRect = rect;
	}

	virtual const Texture* GetTexture() const {
		return mTexture;
	}

	virtual int Width() const {
		return mRect->w;
	}
	virtual void Width(float w) {
		mRect->w = w;
	}

	virtual int Height() const {
		return mRect->h;
	}
	virtual void Height(float h) {
		mRect->h = h;
	}

//	virtual void Draw(float x, float y, float scale = 1, float rotation = 0,
//			float red = 1, float green = 1, float blue = 1, float alpha = 1);
	virtual void Draw(float x, float y, float scale = 1, float rotation = 0, const Color3f * color = NULL, float alpha = 1) const;
protected:
	const Texture* mTexture;
	SectionRect* mRect;

};

} /* namespace TileEngine */
#endif /* SPRITE_H_ */
