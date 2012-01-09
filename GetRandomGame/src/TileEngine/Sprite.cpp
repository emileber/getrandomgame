/*
 * Sprite.cpp
 *
 *  Created on: 2012-01-08
 *      Author: Emile
 */

#include "Sprite.h"
#include "SDLInterface.h"

Sprite::Sprite() {
	_x = 0;
	_y = 0;
	_alpha = 255;
	_spriteSheet = NULL;
	_fileName = "";
}

Sprite::Sprite(int x, int y, std::string filename, int alpha) {
	_x = x;
	_y = y;
	setAlpha(alpha);
	_fileName = filename;
	_spriteSheet = SDLInterface::getInstance()->load_image(filename.c_str());
}

Sprite::Sprite(int x, int y, int w, int h, std::string filename, int nbImage,
		int alpha) {
	_x = x;
	_y = y;
	if (nbImage < 1) {
		nbImage = 1;
	}

	setAlpha(alpha);
	_fileName = filename;
	_spriteSheet = new SDL_Surface[nbImage];
	//_spriteSheet

}

Sprite::Sprite(int x, int y, SDL_Surface * surface, int alpha) {
	_x = x;
	_y = y;
	setAlpha(alpha);
	_spriteSheet = surface;

}

Sprite::Sprite(int x, int y, Sprite * sprite) {
	_x = x;
	_y = y;
	setAlpha(sprite->getAlpha());
	_fileName = sprite->getFileName();
	_spriteSheet = sprite->getSurface();
}

Sprite::~Sprite() {
	SDL_FreeSurface(_spriteSheet);
}

