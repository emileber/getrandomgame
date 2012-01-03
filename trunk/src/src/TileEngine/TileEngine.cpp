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
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
//Le nombre de frames par seconde
const int FRAMES_PER_SECOND = 24;
const int DEFAULT_FONT_SIZE = 15;

TileEngine::TileEngine() {
	cout << "new TileEngine" << endl;
	_frame = 0; // start the frame counter
	_fps = 0;
	// get a pointer to the sdl interface
	_sdl = SDLInterface::getInstance();

	// then init the interface with default values
	_sdl->init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, "tile game");
	if (_sdl->setFont("CaslonBold.ttf", 15) == false) {
		cout << "TileEngine::init setFont = ERROR" << endl;
	}

	cout << "new TileEngine::End" << endl;
}

void TileEngine::start(Environment * environment, InputHandler * inputHandler) {
	cout << "TileEngine start" << endl;
	init(environment, inputHandler); //initialize all the components needed
	run(); //start the game loop
	cout << "TileEngine start::End" << endl;
}

void TileEngine::fpsRegulator() {

	_frame++; // incremente à chaque frame

	//Une chaine de caracteres temporaire
	char caption[64];

	//On calcule le nombre de frames par seconde et on cree la chaine de caracteres
	sprintf(caption, "FPS: %f", (float) _fps);

	// Render the FPS on screen
	_sdl->renderText(SCREEN_WIDTH - 100, 5, caption, NULL, NULL);

	//Si une seconde est passee depuis la derniere mise à jour de la barre caption
	if (_fpsTimer.get_ticks() > 1000) {
		_fps = _frame; // get the current fps

		_frame = -1; // reset the frame counter

		_fpsTimer.start(); // restart the timer for each second
	}
}

void TileEngine::init(Environment * environment, InputHandler * inputHandler) {
	cout << "TileEngine init" << endl;

	_environment = environment;

	_inputHandler = inputHandler;

	_frame = 0; // start the frame counter
	_quit = false;

	cout << "TileEngine init::End" << endl;
}

void TileEngine::run() {
	cout << "TileEngine run" << endl;
	if (DEBUG) {
		_fpsTimer.start();
	}

	/**
	 *
	 *  TEST ZONE
	 *
	 *
	 */
	// test image
	SDL_Surface * hello = _sdl->load_image("background.bmp");
	if (hello == NULL) {
		_quit = true;
	}

	/**
	 *  GAME LOOP
	 */
	while (!_quit) {
		_frameTimer.start(); //On demarre le timer fps

		/**
		 * TEST ZONE
		 */
		//cout << " game looping... ";
		_sdl->apply_surface(0, 0, hello, NULL, NULL);
		_sdl->renderText(300, 200, "BOOBS", NULL, NULL);

		/**
		 * each iteration, do this:
		 */

		// Collect and handle inputs informations (return false on exit)
		_quit = _inputHandler->handleInput(_environment);

		// UPDATE the environment
		//_environment->update()

		if (DEBUG) {
			fpsRegulator();
		}

		// finally, flip the screen
		_sdl->render();

		// wait the time left after the last loop (timeLeft = timeEachLoop - timeTakenThisLoop)
		while (_frameTimer.get_ticks() < 1000 / FRAMES_PER_SECOND)
			;

	} // End of the GAME LOOP

	SDL_FreeSurface(hello); // test
	_sdl->cleanUp();

	cout << "TileEngine run::End" << endl;
}

