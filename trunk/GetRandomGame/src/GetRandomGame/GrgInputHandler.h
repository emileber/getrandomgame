/*
 * GRGInputHandler.h
 *
 *  Created on: 2012-01-04
 *      Author: Emile
 */

#ifndef GRGINPUTHANDLER_H_
#define GRGINPUTHANDLER_H_

#include "InputHandler.h"
#include "SDL/SDL.h"

using namespace TileEngine;

class GrgInputHandler: public InputHandler {

private:
	void MouseMove(const SDL_Event&, Environment*);

public:
	GrgInputHandler();
	virtual ~GrgInputHandler();
	virtual bool HandleInput(Environment*);
};

#endif /* GRGINPUTHANDLER_H_ */
