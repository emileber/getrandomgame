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
	Sprite(int x, int y, int w, int h, std::string filename, int alpha = 255);
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

	virtual int getNbImageX() const {
		return _nbImageX;
	}

	virtual int getNbImageY() const {
		return _nbImageY;
	}

	virtual int getClipX() const {
		return _clipX;
	}

	virtual int getClipY() const {
		return _clipY;
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

	virtual void setClipId(int, int);

	virtual SDL_Rect * getClip() const {
		std::cout << "Sprite::getClip " << _fileName << std::endl;
		return &_clip[_clipX][_clipY];
	}

	virtual SDL_Rect ** getClipRect() {
		return _clip;
	}

	virtual void reset() {
		_clipX = 0;
	}

protected:
	int _x, _y, _width, _height, _alpha;
	int _nbImageX, _nbImageY, _clipX, _clipY;
	SDL_Rect ** _clip;
	SDL_Surface * _spriteSheet;
	std::string _fileName;

	void setRect(int w, int h);

};

#endif /* SPRITE_H_ */
