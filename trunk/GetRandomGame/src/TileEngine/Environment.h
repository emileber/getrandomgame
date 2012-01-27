/*
 * Environment.h
 *
 *  Created on: 2011-12-18
 *      Author: Emile
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "World.h"
#include "Singleton.h"
#include "SDLInterface.h"
#include "Timer.h"
#include "Enumeration.h"

class Environment {
public:
	Environment(); // generic constructor
	virtual ~Environment(){}
	virtual void init(int, int); // generic initialization
	virtual void update(); // generic function, redefine by the subclass
	virtual void close(); // generic function, redefine by the subclass
	virtual Uint32 getTime(){
		return _gameTime.get_ticks();
	}

protected:

	World * _world;
	SDLInterface * _sdl;
	Timer _gameTime;
	int _screenWidth, _screenHeight;
	Uint32 _frameCount;

};

#endif /* ENVIRONMENT_H_ */