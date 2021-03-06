/*
 * InputHandler.h
 *
 *  Created on: 2011-12-28
 *      Author: Emile
 */

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "SDL/SDL.h"

#include "Environment.h"

namespace TileEngine {

class InputHandler {
public:
	InputHandler();
	virtual ~InputHandler();
	virtual bool HandleInput(Environment*);
protected:
	SDL_Event event;
};
}
#endif /* INPUTHANDLER_H_ */
