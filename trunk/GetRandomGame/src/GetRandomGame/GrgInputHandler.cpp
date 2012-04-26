/*
 * GRGInputHandler.cpp
 *
 *  Created on: 2012-01-04
 *      Author: Emile
 */

#include "GRGInputHandler.h"
#include "GetRandomGame.h"
#include <cstdio>

GrgInputHandler::GrgInputHandler() {
}

GrgInputHandler::~GrgInputHandler() {
}

bool GrgInputHandler::HandleInput(Environment* environment) {
	//cout << "GRGInputHandler::handleInput" << endl;
	//Get the keystates, used to know if a key is currently pressed

	Uint8 *keystates = SDL_GetKeyState(NULL);

	// Key event : This "if" returns true only if a key have been pressed
	while (SDL_PollEvent(&event)) {
		//cout << "GRGInputHandler::handleInput Event: " << event.type << endl;
		if (event.type == SDL_QUIT) {
			//Quit the program
			return true;
		}

		// TODO faire un switch de l'event type
		if (event.key.keysym.sym != SDLK_LAST) {
			uint32_t eventKey = event.key.keysym.sym;
			//If a key was pressed
			if (event.type == SDL_KEYDOWN) {
				//cout << "key pressed = " << event.key.keysym.sym << endl;
				switch (eventKey) {
				case SDLK_LEFT:
					((GetRandomGame*) environment)->testFunction(-1, 0);
					break;
				case SDLK_RIGHT:
					((GetRandomGame*) environment)->testFunction(1, 0);
					break;
				case SDLK_UP:
					((GetRandomGame*) environment)->testFunction(0, 1);
					break;
				case SDLK_DOWN:
					((GetRandomGame*) environment)->testFunction(0, -1);
					break;
				case SDLK_f:
					Graphic::getInstance()->ToggleFullScreen();
					break;

				}

			}

			if (event.type == SDL_KEYUP) {
				//Set the proper message surface
				switch (eventKey) {
				case SDLK_LEFT:
					break;

				}
			}

			// On mouse motion
			if (event.type == SDL_MOUSEMOTION) {
				MouseMove(event, environment);
			}

		} // end here if event.key.keysym.sym == SDLK_LAST that is not handle in switch
	} // end here if no keys is pressed

	if (keystates[SDLK_LEFT]) {
		printf("left key is held down\n");
		((GetRandomGame*) environment)->testFunction(-1, 0);
	} else if (keystates[SDLK_RIGHT]) {
		printf("right key is held down\n");
		((GetRandomGame*) environment)->testFunction(1, 0);
	} else if (keystates[SDLK_UP]) {
		printf("up key is held down\n");
		((GetRandomGame*) environment)->testFunction(0, 1);
	} else if (keystates[SDLK_DOWN]) {
		printf("down key is held down\n");
		((GetRandomGame*) environment)->testFunction(0, -1);
	}

	// End of the key handler

	//If the user has Xed out the window
//	else if (event.type == SDL_QUIT) {
//		//Quit the program
//		return true;
//	}
	return false;

}

void GrgInputHandler::MouseMove(const SDL_Event & event,
		Environment* environment) {

	((GetRandomGame*) environment)->testFunction(event.motion.x, event.motion.y);
}








