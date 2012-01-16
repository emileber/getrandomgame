/*
 * Sprite.cpp
 *
 *  Created on: 2012-01-11
 *      Author: Emile
 */

#include "Sprite.h"
#include "SDLInterface.h"
#include <iostream>
#include <cstdio>

using namespace std;
/**
 * new sprite w/o image
 *
 */
Sprite::Sprite() {
	_x = 0;
	_y = 0;
	setSize(0, 0);
	_alpha = 255;

	_spriteSheet = NULL;
	_fileName = "";
}

/**
 * New sprite with ONE (1) IMAGE to LOAD
 *
 */
Sprite::Sprite(int x, int y, std::string filename, int alpha) {
	// coordinate
	_x = x;
	_y = y;
	setAlpha(alpha);
	_fileName = filename;

	// Set the surface et clip rect
	_spriteSheet = SDLInterface::getInstance()->load_image(_fileName.c_str());
	setSize(_spriteSheet->w, _spriteSheet->h);
	setRect(_width, _height);

}

/**
 * New Sprite with ONE (1) SURFACE to Point
 *
 */
Sprite::Sprite(int x, int y, SDL_Surface * surface, int alpha) {
	_x = x;
	_y = y;
	_clipX = 0;
	_clipY = 0;
	setAlpha(alpha);
	_fileName = "";

	// Set the surface et clip rect
	_spriteSheet = surface;
	setSize(_spriteSheet->w, _spriteSheet->h);
	setRect(_spriteSheet->w, _spriteSheet->h);
}

/**
 * New Sprite that point stuff of another sprite
 *
 */
Sprite::Sprite(int x, int y, Sprite * sprite) {
	_x = x;
	_y = y;

	_nbImageX = sprite->getNbImageX();
	_nbImageY = sprite->getNbImageY();
	setAlpha(sprite->getAlpha());
	_fileName = sprite->getFileName();
	_spriteSheet = sprite->getSurface();
	_clip = sprite->getClipRect();
	setClipId(sprite->getClipX(), sprite->getClipY());
	setSize(sprite->getWidth(), sprite->getHeight());
}

/**
 * New Sprite with "nbImage" IMAGE to LOAD
 *
 */
Sprite::Sprite(int x, int y, int w, int h, std::string filename, int alpha) {
	_clipX = 0;
	_clipY = 0;
	// coordinate and Size
	_x = x;
	_y = y;
	_width = w;
	_height = h;
	_fileName = filename;
	setAlpha(alpha);

	_spriteSheet = SDLInterface::getInstance()->load_image(_fileName.c_str());
	setRect(_width, _height); // custom size for multiple image in sprite sheet

}

Sprite::~Sprite() {
	cout << "delete " << _fileName << endl;
	SDL_FreeSurface(_spriteSheet);
}

void Sprite::setClipId(int xId, int yId) {
	if ((xId >= 0) && (xId < _nbImageX)) {
		_clipX = xId;
	} else {
		cout << "setClipId X OOB, mis a 0 par default pour l'image: "
				<< _fileName << endl;
		_clipX = 0;
	}

	if ((yId >= 0) && (yId < _nbImageY)) {
		_clipY = yId;
	} else {
		cout << "setClipId Y OOB, mis a 0 par default pour l'image: "
				<< _fileName << endl;
		_clipY = 0;
	}

}

/**
 * *************************************
 * |     |     |     |     |     |     |
 * | 0,0 | 1,0 | 2,0 | 3,0 | 4,0 | 5,0 |
 * |     |     |     |     |     |     |
 * *************************************
 * |     |     |     |     |     |     |
 * | 0,1 | 1,1 | 2,1 | 3,1 | 4,1 | 5,1 |
 * |     |     |     |     |     |     |
 * *************************************
 *
 */
void Sprite::setRect(int w, int h) {
	cout << "Sprite::placeRect " << _fileName << endl;
	if ((w == 0) || (h == 0)) {
		cout << "W et H NULL, returning" << endl;
		_nbImageX = 1;
		_nbImageY = 1;
		_clipX = 0;
		_clipY = 0;
		_clip = NULL;
		return;
	}
	//cout << "W et H are ok" << endl;
	_nbImageX = abs(_spriteSheet->w / w);
	_nbImageY = abs(_spriteSheet->h / h);

	cout << "nbX: " << _nbImageX << endl << "nbY: " << _nbImageY << endl;

	_clip = new SDL_Rect*[_nbImageX];
	for (int x = 0; x < _nbImageX; x++) {
		_clip[x] = new SDL_Rect[_nbImageY];
		for (int y = 0; y < _nbImageY; y++) {
			_clip[x][y].x = x * w;
			_clip[x][y].y = y * h;
			_clip[x][y].w = w;
			_clip[x][y].h = h;
			printf("x, y: %2d, %2d | clip x,y,w,h: %4d %4d %4d %4d \n", x, y, _clip[x][y].x, _clip[x][y].y, _clip[x][y].w, _clip[x][y].h);
		}
	}
	cout << "Sprite::placeRect() END" << endl;
}
