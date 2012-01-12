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
#include "Enumeration.h"

class TileEngine: public Singleton<TileEngine> {
	friend class Singleton<TileEngine> ;
private:
	TileEngine();

	SDLInterface * _sdl;
	Environment * _environment;
	InputHandler * _inputHandler;
	Timer _frameTimer; // used to calculate the time taken each game loop
	Timer _fpsTimer; // used to calculate the FPS of the game
	int _frame, _fps, _screenWidth, _screenHeight;
	bool _quit, _init;

	void run();
	void fpsRegulator();

public:
	void init(int, int, std::string, std::string, Environment *, InputHandler *);
	void start();
	void stop();

};

#endif /* TILEENGINE_H_ */
