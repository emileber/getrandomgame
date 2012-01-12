/*
 * SpriteSheet.cpp
 *
 *  Created on: 2012-01-12
 *      Author: Emile
 */

#include "SpriteSheet.h"
#include "SDLInterface.h"

#include <iostream>
using namespace std;

SpriteSheet::SpriteSheet() {
	_nbImage = 0;
	_clip = NULL;
	_clipId = 0;
}

/**
 * New Sprite with "nbImage" IMAGE to LOAD
 *
 */
SpriteSheet::SpriteSheet(int x, int y, int w, int h, std::string filename,
		int nbImage, int alpha) {
	_clipId = 0;
	// coordinate and Size
	_x = x;
	_y = y;
	_width = w;
	_height = h;
	_fileName = filename;
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
SpriteSheet::SpriteSheet(int x, int y, Sprite * spriteSheet, int id) {

	//_clipId = id;
	_x = x;
	_y = y;
	_nbImage = spriteSheet->getNbImage();
	setClipId(id);
	setSize(spriteSheet->getWidth(), spriteSheet->getHeight());

	setAlpha(spriteSheet->getAlpha());
	_fileName = spriteSheet->getFileName();
	_spriteSheet = spriteSheet->getSurface();
	_clip = spriteSheet->getClipRect();
}

void SpriteSheet::setClipId(int idClip) {
	if ((idClip >= 0) && (idClip < _nbImage)) {
		_clipId = idClip;
	}else{
		cout << "setClipId ERROR mis a 0 par default pour l'image: " << _fileName << endl;
		_clipId = 0;
	}

}

void SpriteSheet::setRect(int indice, int x, int y, int w, int h) {
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
void SpriteSheet::placeRect(int nbImage, int w, int h) {
	cout << "Sprite::placeRect " << _fileName << endl;

	_clip = new SDL_Rect[nbImage];
	for (int i = 0; i < nbImage; i++) {
		setRect(i, i * w, 0, w, h);
	}
	cout << "Sprite::placeRect() END" << endl;
}
