/*
 * TileEngine.cpp
 *
 *  Created on: 2011-12-26
 *      Author: Emile
 */

#include "Engine.h"
#include <iostream>

using namespace std;

namespace TileEngine {

int frameCount = 0; // test global frame counter

/****************************************
 * CONSTRUTOR
 */
Engine::Engine() {
	cout << "new TileEngine" << endl;
	_frame = 0; // start the frame counter
	_fps = 0;

	// default resolution
	_screenWidth = 640;
	_screenHeight = 480;

	_init = false;
	_quit = false;
	printf("sizeof int: %d\n", sizeof(int));
	cout << "new TileEngine::End" << endl;
}

/****************************************
 * init(...)
 *  Call that first, then call start();
 *
 */
void Engine::init(int screenW, int screenH, string caption, string fontFile,
		Environment * environment, InputHandler * inputHandler) {
	cout << "Engine init" << endl;

	_environment = environment;
	_inputHandler = inputHandler;

	// set the custom resolution
	_screenWidth = screenW;
	_screenHeight = screenH;

	_frame = 0; // start the frame counter
	_quit = false;

	// get a pointer to the sdl interface
//	_sdl = SDLInterface::getInstance();
//
//	// then init the interface with default values
//	if (_sdl->init(_screenWidth, _screenHeight, SCREEN_BPP, caption,
//			TOTAL_LAYER) == false) {
//		cout << "TileEngine::init sdl init = ERROR" << endl;
//	}
//	if (_sdl->setFont(fontFile, 15) == false) {
//		cout << "TileEngine::init setFont = ERROR" << endl;
//	}

	_graphic = Graphic::getInstance();
	_graphic->initialize(_screenWidth, _screenHeight, SCREEN_BPP, caption);
	_graphic->makeWindow();

	_environment->init(_screenWidth, _screenHeight);

	_init = true;

	cout << "Engine init::End" << endl;
}

/****************************************
 * start()
 *  It literally starts the engine
 *
 */
void Engine::start() {
	cout << "Engine start" << endl;
	if (_init) {
		run(); //start the game loop
	}
	cout << "Engine start::End" << endl;
}

/****************************************
 * run()
 *  its the actual game loop
 *
 */
void Engine::run() {
	cout << "Engine run" << endl;
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

		_environment->update(); // UPDATE the environment

		if (DEBUG) {
			fpsRegulator(); // show FPS information
		}


		_graphic->clearScreen(); // clear the screen

		// all the draw OPs
		_environment->draw();

		_graphic->flipBuffers(); // flip the screen

		// wait the time left after the last loop (timeLeft = timeEachLoop - timeTakenThisLoop)
		while (_frameTimer.get_ticks() < 1000 / FRAMES_PER_SECOND)
			;
		frameCount++; // test frame count
	} // End of the GAME LOOP

	// Stop the program correctly
	stop();

	cout << "Engine run::End" << endl;
}

/****************************************
 * fpsRegulator
 * 	show the fps
 *
 */
void Engine::fpsRegulator() {
	//printf("SDL_getTicks: %10d\n", SDL_GetTicks());
	//printf("fpsRegulator(_frame: %d, _fps: %d)\n", _frame, _fps);
	_frame++; // incremente à chaque frame

	// Render the FPS on screen
	//_sdl->renderText(10, 5, DEBUG_LAYER, "FPS: " + _sdl->intToString(_fps));
	_graphic->setCaption("FPS: " + _sdl->intToString(_fps));

	//Si une seconde est passee depuis la derniere mise à jour de la barre caption
	if (_fpsTimer.get_ticks() > 1000) {
		_fps = _frame; // get the current fps

		_frame = -1; // reset the frame counter

		_fpsTimer.start(); // restart the timer for each second
		printf("frame/Time: %4d%10d\n", frameCount, _environment->getTime());
	}
	//printf("fpsRegulator END\n");
}

/****************************************
 *
 *
 */
void Engine::stop() {
	_environment->close();
	_graphic->shutdown();
	_graphic->kill();
	//_sdl->cleanUp();
}

}
