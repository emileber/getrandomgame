/*
 * Animation.h
 *
 *  Created on: 2012-01-08
 *      Author: Emile
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "Sprite.h"
//#include "SDLInterface.h"

class Animation: public Sprite {

public:
	Animation();
	Animation(int x, int y, std::string filename, int alpha = 255) :
			Sprite(x, y, filename, alpha) {
		_nbImage = 1; // only 1 image in the sprite sheet
		_clip = NULL;
	}

	Animation(int x, int y, SDL_Surface * surface, int alpha = 255) :
			Sprite(x, y, surface, alpha) {
		_nbImage = 1;
		_clip = NULL;
	}
	Animation(int, int, Sprite *);
	Animation(int, int, int, int, std::string, int, int, int = 255);

	/**
	 * GET functions
	 */

	int getFrametTime(){
		return _frameTime;
	}

	virtual int getNbImage() {
		return _nbImage;
	}

	virtual SDL_Rect * getClipRect() {
		return _clip;
	}

	virtual SDL_Rect * getClip() {
		return &_clip[_frame % _nbImage];
	}


	/**
	 * SET functions
	 */
	//virtual void setSprite(std::string); // Do nothing, for futur uses
	virtual void nextFrame(int time);

	virtual void reset() {
		_frame = 0;
	}

private:
	int _nbImage, _frame, _lastUpdate, _frameTime;
	SDL_Rect * _clip;

	void placeRect(int, int, int);
	void setRect(int, int, int, int = 0, int = 0);
};

#endif /* ANIMATION_H_ */
