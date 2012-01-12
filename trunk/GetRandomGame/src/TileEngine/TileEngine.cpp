/*
 * TileEngine.cpp
 *
 *  Created on: 2011-12-26
 *      Author: Emile
 */

#include "TileEngine.h"
#include "SDL/SDL.h"
#include <iostream>

using namespace std;

/**
 * CONSTANTS
 */
const bool DEBUG = true;
//Les attributs de l'ecran (640 * 480)
const int SCREEN_BPP = 32;
//Le nombre de frames par seconde
const int FRAMES_PER_SECOND = 24;

/**
 * CONSTRUTOR
 */
TileEngine::TileEngine() {
	cout << "new TileEngine" << endl;
	_frame = 0; // start the frame counter
	_fps = 0;

	// default resolution
	_screenWidth = 640;
	_screenHeight = 480;

	_init = false;
	_quit = false;
	cout << "new TileEngine::End" << endl;
}

/**
 * init(...)
 *  Call that first, then call start();
 *
 */
void TileEngine::init(int screenW, int screenH, string caption, string fontFile,
		Environment * environment, InputHandler * inputHandler) {
	cout << "TileEngine init" << endl;

	_environment = environment;
	_inputHandler = inputHandler;

	// set the custom resolution
	_screenWidth = screenW;
	_screenHeight = screenH;

	_frame = 0; // start the frame counter
	_quit = false;

	// get a pointer to the sdl interface
	_sdl = SDLInterface::getInstance();

	// then init the interface with default values
	if (_sdl->init(_screenWidth, _screenHeight, SCREEN_BPP, caption, TOTAL_LAYER)
			== false) {
		cout << "TileEngine::init sdl init = ERROR" << endl;
	}
	if (_sdl->setFont(fontFile, 15) == false) {
		cout << "TileEngine::init setFont = ERROR" << endl;
	}

	_environment->init(_screenWidth, _screenHeight);

	_init = true;

	cout << "TileEngine init::End" << endl;
}

/**
 * start()
 *  It literally starts the engine
 *
 */
void TileEngine::start() {
	cout << "TileEngine start" << endl;
	if (_init) {
		run(); //start the game loop
	}
	cout << "TileEngine start::End" << endl;
}

/**
 * run()
 *  its the actual game loop
 *
 */
void TileEngine::run() {
	cout << "TileEngine run" << endl;
	if (DEBUG) {
		_fpsTimer.start();
	}

	/**
	 *  GAME LOOP
	 */
	while (!_quit) {
		/**
		 * each iteration, do this:
		 */

		_frameTimer.start(); //Calcul le temps d'execution de l'iteration

		// Collect and handle inputs informations (return false on exit)
		_quit = _inputHandler->handleInput(_environment);

		// UPDATE the environment
		_environment->update();

		// show FPS information
		if (DEBUG) {
			fpsRegulator();
		}

		// finally, flip the screen
		_sdl->render();

		// wait the time left after the last loop (timeLeft = timeEachLoop - timeTakenThisLoop)
		while (_frameTimer.get_ticks() < 1000 / FRAMES_PER_SECOND)
			;

	} // End of the GAME LOOP

	// Stop the program correctly
	stop();

	cout << "TileEngine run::End" << endl;
}

void TileEngine::fpsRegulator() {

	_frame++; // incremente à chaque frame

	// Render the FPS on screen
	_sdl->renderText(10, 5, DEBUG_LAYER, "FPS: " + _sdl->intToString(_fps), 200);

	//Si une seconde est passee depuis la derniere mise à jour de la barre caption
	if (_fpsTimer.get_ticks() > 1000) {
		_fps = _frame; // get the current fps

		_frame = -1; // reset the frame counter

		_fpsTimer.start(); // restart the timer for each second
	}
}

void TileEngine::stop() {
	_environment->close();
	_sdl->cleanUp();
}

