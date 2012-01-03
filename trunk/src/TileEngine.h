/*
 * TileEngine.h
 *
 *  Created on: 2011-12-26
 *      Author: Emile
 */

#ifndef TILEENGINE_H_
#define TILEENGINE_H_

#include "Singleton.h"
#include "SDLInterface.h"
#include "Environment.h"
#include "InputHandler.h"
#include "Timer.h"

class TileEngine: public Singleton<TileEngine> {
	friend class Singleton<TileEngine> ;
private:
	TileEngine();

	SDLInterface * _sdl;
	Environment * _environment;
	InputHandler * _inputHandler;
	Timer _frameTimer; // used to calculate the time taken each game loop
	Timer _fpsTimer; // used to calculate the FPS of the game
	int _frame, _fps;
	bool _quit;

	void init(Environment*, InputHandler*);
	void run();
	void fpsRegulator();

public:
	void start(Environment*, InputHandler*);

};

#endif /* TILEENGINE_H_ */
