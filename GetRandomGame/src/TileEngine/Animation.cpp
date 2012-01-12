/*
 * Sprite.cpp
 *
 *  Created on: 2012-01-08
 *      Author: Emile
 */

#include "Animation.h"
#include "SDLInterface.h"

#include <iostream>

using namespace std;

/**
 * new sprite w/o image
 *
 */
Animation::Animation() {
	_x = 0;
	_y = 0;
	setSize(0, 0);
	_alpha = 255;
	_nbImage = 0;
	_clip = NULL;

	_spriteSheet = NULL;
	_fileName = "";
}

/**
 * New sprite with ONE (1) IMAGE to LOAD
 *
 */
Animation::Animation(int x, int y, std::string filename, int alpha) {
	// coordinate
	_x = x;
	_y = y;
	setAlpha(alpha);

	_nbImage = 1; // only 1 image in the sprite sheet
	_fileName = filename;

	// Set the surface et clip rect
	_spriteSheet = SDLInterface::getInstance()->load_image(_fileName.c_str());
	setSize(_spriteSheet->w, _spriteSheet->h);

	_clip = NULL;

}

/**
 * New Sprite with ONE (1) SURFACE to Point
 *
 */
Animation::Animation(int x, int y, SDL_Surface * surface, int alpha) {
	_x = x;
	_y = y;
	_nbImage = 1;
	setAlpha(alpha);
	_fileName = "";

	// Set the surface et clip rect
	_spriteSheet = surface;
	setSize(_spriteSheet->w, _spriteSheet->h);
	_clip = NULL;
}

/**
 * New Sprite with "nbImage" IMAGE to LOAD
 *
 */
Animation::Animation(int x, int y, int w, int h, std::string filename, int nbImage,
		int alpha) {
	// coordinate and Size
	_x = x;
	_y = y;
	_width = w;
	_height = h;

	if (nbImage < 1) {
		nbImage = 1;
	}
	_nbImage = nbImage;
	setAlpha(alpha);
	_fileName = filename;
	placeRect(_nbImage, _width, _height); // custom size for multiple image in sprite sheet
	_spriteSheet = SDLInterface::getInstance()->load_image(_fileName.c_str());
	//_spriteSheet

}

/**
 * New Sprite that point stuff of another sprite
 *
 */
Animation::Animation(int x, int y, Animation * sprite) {
	_x = x;
	_y = y;
	_nbImage = sprite->getNbImage();

	if (_nbImage > 1) {
		// SET the size
		setSize(sprite->getWidth(), sprite->getHeight());
	}
	setAlpha(sprite->getAlpha());
	_fileName = sprite->getFileName();
	_spriteSheet = sprite->getSurface();
	_clip = sprite->getClipRect();
}

Animation::~Animation() {
	SDL_FreeSurface(_spriteSheet);
}

void Animation::setRect(int indice, int x, int y, int w, int h) {
	_clip[indice].x = x;
	_clip[indice].y = y;
	_clip[indice].w = w;
	_clip[indice].h = h;
}

/**
 * *************************************
 * |     |     |     |     |     |     |
 * |  1  |  2  |  3  |  4  |  5  |  6  |
 * |     |     |     |     |     |     |
 * *************************************
 */
void Animation::placeRect(int nbImage, int w, int h) {
	cout << "Sprite::placeRect(" << endl;

	_clip = new SDL_Rect[nbImage];
	for (int i = 0; i < nbImage; i++) {
		setRect(i, i * w, 0, w, h);
	}
	cout << "Sprite::placeRect() END" << endl;
}
