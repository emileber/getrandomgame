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
		_nbFrame = 1; // only 1 image in the sprite sheet
		_clip = NULL;
	}

	Animation(int x, int y, SDL_Surface * surface, int alpha = 255) :
			Sprite(x, y, surface, alpha) {
		_nbFrame = 1;
		_clip = NULL;
	}
	Animation(int, int, Sprite *);
	Animation(int, int, int, int, std::string, int, int, int = 255);

	/**
	 * GET functions
	 */

	int getFrametTime() const {
		return _frameTime;
	}

	virtual int getNbImage() const {
		return _nbFrame;
	}

	virtual SDL_Rect * getClip() const {
		return &_clip[_frame % _nbFrame][_clipY];
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
	int _nbFrame, _frame, _lastUpdate, _frameTime;
};

#endif /* ANIMATION_H_ */
