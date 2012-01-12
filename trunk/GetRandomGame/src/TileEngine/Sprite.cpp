/*
 * Sprite.cpp
 *
 *  Created on: 2012-01-11
 *      Author: Emile
 */

#include "Sprite.h"
#include "SDLInterface.h"
#include <iostream>

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

}

/**
 * New Sprite with ONE (1) SURFACE to Point
 *
 */
Sprite::Sprite(int x, int y, SDL_Surface * surface, int alpha) {
	_x = x;
	_y = y;
	setAlpha(alpha);
	_fileName = "";

	// Set the surface et clip rect
	_spriteSheet = surface;
	setSize(_spriteSheet->w, _spriteSheet->h);
}

/**
 * New Sprite that point stuff of another sprite
 *
 */
Sprite::Sprite(int x, int y, Sprite * sprite) {
	_x = x;
	_y = y;


	setSize(sprite->getWidth(), sprite->getHeight());
	setAlpha(sprite->getAlpha());
	_fileName = sprite->getFileName();
	_spriteSheet = sprite->getSurface();
}

Sprite::~Sprite() {
	cout << "delete " << _fileName << endl;
	SDL_FreeSurface(_spriteSheet);
}
