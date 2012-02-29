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
	Sprite(Texture* texture, SectionRect* rect){
		SetTexture(texture);
		SetRect(rect);
	}
	virtual ~Sprite();

	virtual void SetTexture(std::string);
	virtual void SetTexture(Texture* texture){
		mTexture = texture;
	}

	virtual void SetRect(SectionRect* rect){
		mRect = rect;
	}

	virtual Texture* GetTexture(){
		return mTexture;
	}

	virtual void Draw(GLfloat x, GLfloat y, GLfloat scale = 1,
			GLfloat rotation = 0, GLfloat red = 1, GLfloat green = 1,
			GLfloat blue = 1, GLfloat alpha = 1);
protected:
	Texture* mTexture;
	SectionRect* mRect;

};

} /* namespace TileEngine */
#endif /* SPRITE_H_ */
