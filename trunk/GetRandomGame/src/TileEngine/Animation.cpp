/*
 * Animation.cpp
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
	_nbImage = 0;
	_clip = NULL;
	_frameTime = 1;
	_lastUpdate = 0;

}

/**
 * New Sprite with "nbImage" IMAGE to LOAD
 *
 */
Animation::Animation(int x, int y, int w, int h, std::string filename,
		int nbImage, int frameTime, int alpha) {
	// coordinate and Size
	_x = x;
	_y = y;
	_width = w;
	_height = h;
	_fileName = filename;
	_lastUpdate = 0;
	_frameTime = frameTime;
	setAlpha(alpha);
	if (nbImage < 1) {
		nbImage = 1;
	}
	_nbImage = nbImage;

	placeRect(_nbImage, _width, _height); // custom size for multiple image in sprite sheet
	_spriteSheet = SDLInterface::getInstance()->load_image(_fileName.c_str());

}

/**
 * New Sprite that point stuff of another sprite
 *
 */
Animation::Animation(int x, int y, Animation * anim) {
	_x = x;
	_y = y;
	_nbImage = anim->getNbImage();
	_lastUpdate = 0;
	_frameTime = anim->getFrametTime();

	setSize(anim->getWidth(), anim->getHeight());

	setAlpha(anim->getAlpha());
	_fileName = anim->getFileName();
	_spriteSheet = anim->getSurface();
	_clip = anim->getClipRect();
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
	cout << "Sprite::placeRect " << _fileName << endl;

	_clip = new SDL_Rect[nbImage];
	for (int i = 0; i < nbImage; i++) {
		setRect(i, i * w, 0, w, h);
	}
	cout << "Sprite::placeRect() END" << endl;
}

void Animation::nextFrame(int time) {
	if (time > _lastUpdate + _frameTime) {
		_frame++;
		_lastUpdate = time;
	}
}
