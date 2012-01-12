/*
 * SpriteSheet.h
 *
 *  Created on: 2012-01-12
 *      Author: Emile
 */

#ifndef SPRITESHEET_H_
#define SPRITESHEET_H_

#include "Sprite.h"

#include <iostream>

class SpriteSheet: public Sprite {
public:
	SpriteSheet();
	SpriteSheet(int, int, Sprite *, int);
	SpriteSheet(int, int, int, int, std::string, int, int = 255);

	virtual void setClipId(int idClip);

	virtual int getClipId() const{
		return _clipId;
	}

	virtual int getNbImage() const {
		//std::cout << "SpriteSheet nbImage " << _nbImage << " " << _fileName << std::endl;
		return _nbImage;
	}

	virtual SDL_Rect * getClipRect() {
		return _clip;
	}

	virtual SDL_Rect * getClip() {
		return &_clip[_clipId];
	}

private:
	int _nbImage, _clipId;
	SDL_Rect * _clip;

	void setRect(int indice, int x, int y, int w, int h);
	void placeRect(int nbImage, int w, int h);
};

#endif /* SPRITESHEET_H_ */
