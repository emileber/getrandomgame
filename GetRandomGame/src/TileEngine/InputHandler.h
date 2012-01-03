/*
 * InputHandler.h
 *
 *  Created on: 2011-12-28
 *      Author: Emile
 */

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "Environment.h"
#include "SDL/SDL.h"

class InputHandler {
public:
	InputHandler();
	virtual ~InputHandler();
	bool handleInput(Environment*);
private:
	SDL_Event event;
};

#endif /* INPUTHANDLER_H_ */
