/*
 * Sprite.h
 *
 *  Created on: 2012-01-11
 *      Author: Emile
 */

#ifndef SPRITE_H_
#define SPRITE_H_
#include <string>
#include "SDL/SDL.h"
#include <iostream>
//#include "SDLInterface.h"

class Sprite {
public:
	Sprite();
	Sprite(int, int, std::string, int = 255);
	Sprite(int, int, SDL_Surface*, int = 255);
	Sprite(int, int, Sprite *);
	virtual ~Sprite();

	int getX() const {
		return _x;
	}
	int getY() const {
		return _y;
	}

	int getAlpha() const {
		return _alpha;
	}

	int getWidth() const {
		return _width;
	}
	int getHeight() const {
		return _height;
	}
	std::string getFileName() {
		return _fileName;
	}

	SDL_Surface * getSurface() {
		return _spriteSheet;
	}

	virtual int getNbImage() const {
		//std::cout << "Sprite nbImage " << _fileName << std::endl;
		return 1;
	}

	virtual int getClipId() const{
		return 0;
	}

	void setPoint(int x, int y) {
		_x = x;
		_y = y;
	}
	void setSize(int w, int h) {
		_width = w;
		_height = h;
	}

	void setAlpha(int alpha = 255) {
		if ((alpha > 255) || (alpha < 0)) {
			alpha = 255;
		}
		_alpha = alpha;
	}

	virtual void setClipId(int id) {

	}

	virtual SDL_Rect * getClip() {
		return NULL;
	}
	virtual SDL_Rect * getClipRect() {
		return NULL;
	}

	virtual int getFrametTime() {
		return 1;
	}

//	virtual void setSprite(std::string) {
//		// Do nothing, for futur uses
//	}
	virtual void nextFrame(int time) {

	}

	virtual void reset() {
	}

protected:
	int _x, _y, _width, _height, _alpha;
	SDL_Surface * _spriteSheet;
	std::string _fileName;
};

#endif /* SPRITE_H_ */
