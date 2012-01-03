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

class Environment: public Singleton<Environment> {
	friend class Singleton<Environment>;
private:
	Environment();
public:
	World * _world;
	SDLInterface * _sdl;

};

#endif /* ENVIRONMENT_H_ */
