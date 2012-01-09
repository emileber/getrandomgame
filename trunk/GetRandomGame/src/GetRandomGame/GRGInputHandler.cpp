/*
 * GRGInputHandler.cpp
 *
 *  Created on: 2012-01-04
 *      Author: Emile
 */

#include "GRGInputHandler.h"
#include <iostream>

using namespace std;

GRGInputHandler::GRGInputHandler() {
	// TODO Auto-generated constructor stub

}

GRGInputHandler::~GRGInputHandler() {
	// TODO Auto-generated destructor stub
}

bool GRGInputHandler::handleInput(Environment* environment) {
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
		if (event.key.keysym.sym != SDLK_LAST) {
			uint32_t eventKey = event.key.keysym.sym;
			//If a key was pressed
			if (event.type == SDL_KEYDOWN) {
				cout << "key pressed = " << event.key.keysym.sym << endl;
				//Set the proper message surface
				switch (eventKey) {
				case SDLK_c:
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
		} // end here if event.key.keysym.sym == SDLK_LAST that is not handle in switch
	} // end here if no keys is pressed

	if (keystates[SDLK_LEFT]) {
		cout << "left key is held down" << endl;
	} else if (keystates[SDLK_RIGHT]) {
		cout << "right key is held down" << endl;
	}

	// End of the key handler

	//If the user has Xed out the window
	else if (event.type == SDL_QUIT) {
		//Quit the program
		return true;
	}
	return false;

}
