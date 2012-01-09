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

class Environment {
public:
	Environment(); // generic constructor
	virtual ~Environment(){}
	virtual void init() {} // subclass specific initialization
	virtual void update(); // generic function, redefine by the subclass
	virtual void close(); // generic function, redefine by the subclass

protected:

	World * _world;
	SDLInterface * _sdl;
	Timer _gameTime;
	int _frameCount;

};

#endif /* ENVIRONMENT_H_ */
