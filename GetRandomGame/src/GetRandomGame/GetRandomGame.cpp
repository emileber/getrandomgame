/*
 * GetRandomGame.cpp
 *
 *  Created on: 2012-01-03
 *      Author: Emile
 */

#include "GetRandomGame.h"
#include "TextureManager.h"
#include <ctime>
#include <iostream>

using namespace std;

/***************************
 * TEST DECLARATIONS
 */
Texture * _background, *_hello, *_cat, *_pave;
SDL_Surface * _semiTransSurf;
int testx = 0, testy = 0;
Uint32 last = 0;
/**
 * END OF TEST DECLARATIONS
 ***************************/

GetRandomGame::GetRandomGame() {
	cout << "new GetRandomGame()" << endl;

	cout << "new GetRandomGame()::End" << endl;
}

void GetRandomGame::init(int w, int h) {
	cout << "GetRandomGame::init()" << endl;
	Environment::init(w, h); // parent class init
	//srand((unsigned) time(0)); // seed the random gen
	//srand(5);

	/****************************************
	 *
	 * TEST INIT
	 *
	 */
	_hello = _textureManager->loadTextureFromFile("image/hello_world.bmp");

	/*
	 * END OF TEST INIT
	 ****************************************/

	cout << "GetRandomGame::init()::End" << endl;
}

void GetRandomGame::update() {
	//cout << "GetRandomGame::update() | ";

	Environment::update(); // generic update

	// then game specific update
	//_sdl->renderText(10, 20, DEBUG_LAYER, _sdl->formatTime(_gameTime.get_ticks())); // Show the total up time

	/**
	 * TEST ZONE
	 */

} // END of update()

void GetRandomGame::draw() {
	_hello->draw(testx, testy, 1, 0, 1, 1, 1, 1);
}

void GetRandomGame::testFunction(int xMod, int yMod) {
	testx = xMod * MOVE_DISTANCE;
	testy = yMod * MOVE_DISTANCE;
}

void GetRandomGame::close() {
	cout << "GetRandomGame::close()" << endl;
	Environment::close(); // call the generic close function to close general stuff

//	delete _background;
//	delete _cat;
//	delete _hello;
//	delete _pave;
}
