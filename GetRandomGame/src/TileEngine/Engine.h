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
#include "Global.h"
#include "Graphic.h"

namespace TileEngine {

class Engine: public Singleton<Engine> {
	friend class Singleton<Engine> ;
private:
	Engine();

	SDLInterface * _sdl;
	Graphic * _graphic;
	Environment * _environment;
	InputHandler * _inputHandler;
	Timer _frameTimer; // used to calculate the time taken each game loop
	Timer _fpsTimer; // used to calculate the FPS of the game
	int _frame, _fps, _screenWidth, _screenHeight;
	bool _quit, _init;

	void run();
	void fpsRegulator();

public:
	void init(int, int, std::string, std::string, Environment *,
			InputHandler *);
	void start();
	void stop();

};
}
#endif /* TILEENGINE_H_ */
