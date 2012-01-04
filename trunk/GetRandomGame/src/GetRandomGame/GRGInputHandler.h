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

class GRGInputHandler: public InputHandler {
public:
	GRGInputHandler();
	virtual ~GRGInputHandler();
	virtual bool handleInput(Environment*);
};

#endif /* GRGINPUTHANDLER_H_ */
