/*
 * Animation.cpp
 *
 *  Created on: 2012-01-08
 *      Author: Emile
 */

#include "Animation.h"
#include "SDLInterface.h"
#include <cstdio>


/**
 * new sprite w/o image
 *
 */
Animation::Animation() {
	_nbFrame = 0;
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
	_frame = 0;
	_fileName = filename;
	_lastUpdate = 0;
	_frameTime = frameTime;
	setAlpha(alpha);
	if (nbImage < 1) {
		nbImage = 1;
	}
	_nbFrame = nbImage;

	_spriteSheet = SDLInterface::getInstance()->load_image(_fileName.c_str());

	// Important to load the sprite first
	// because placeRect uses its size value
	setRect(_width, _height); // custom size for multiple image in sprite sheet
	_clipY = 0;

}

/**
 * New Sprite that point stuff of another sprite
 *
 */
Animation::Animation(int x, int y, Sprite * anim) {
	_x = x;
	_y = y;
	_nbImageX = anim->getNbImageX();
	_nbImageY = anim->getNbImageY();
	_lastUpdate = 0;
	_frameTime = anim->getFrametTime();
	_nbFrame = ((Animation*)anim)->getNbImage();

	setSize(anim->getWidth(), anim->getHeight());

	setAlpha(anim->getAlpha());
	_fileName = anim->getFileName();
	_spriteSheet = anim->getSurface();
	_clip = anim->getClipRect();
}

void Animation::nextFrame(int time) {
	if (time > _lastUpdate + _frameTime) {
		_frame++;
		_lastUpdate = time;
	}
}
