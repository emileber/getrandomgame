/*
 * GetRandomGame.cpp
 *
 *  Created on: 2012-01-03
 *      Author: Emile
 */

#include "GetRandomGame.h"
#include <iostream>

using namespace std;

SDL_Surface * _background;

GetRandomGame::GetRandomGame() {
	cout << "new GetRandomGame()" << endl;

	cout << "new GetRandomGame()::End" << endl;
}

void GetRandomGame::init(){
	cout << "GetRandomGame::init()" << endl;
	_background = _sdl->load_image("background.bmp");
	cout << "GetRandomGame::init()::End" << endl;
}


void GetRandomGame::update() {
	//cout << "GetRandomGame::update()" << endl;

	Environment::update(); // generic update
	// then game specific update

	/**
	 * TEST ZONE
	 */
	_sdl->apply_surface(-5, -5, _background);
	_sdl->renderText(300, 200, "BOOBS");
}

void GetRandomGame::close() {
	cout << "GetRandomGame::close()" << endl;
	Environment::close(); // call the generic close function to close general stuff

	SDL_FreeSurface(_background); // test
}
