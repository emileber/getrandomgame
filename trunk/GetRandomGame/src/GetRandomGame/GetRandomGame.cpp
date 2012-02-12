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
Texture * _background, *_pave, *_cat, *_grass;
SDL_Surface * _semiTransSurf;
int testx = 0, testy = 0;
Uint32 last = 0;
SectionStruct * tileTestRect;
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
	_pave = new Texture("image/pave.png");

	_grass = new Texture("image/grass.png");

	tileTestRect = new SectionStruct;
	tileTestRect->x = 0;
	tileTestRect->y = 24;
	tileTestRect->w = 40;
	tileTestRect->h = 40;

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

	for (int x = 0; x < 30; x++) {
		for (int y = 0; y < 15; y++) {
			tileTestRect->x = ((x * y + (x ^ y)) % 5) * 40;
			_pave->drawSection(x * 40, y * 40, tileTestRect);
		}
	}
	tileTestRect->x = 0;
	_grass->drawSection(50, 50, tileTestRect, 1, 0,
			((140 + testx) / 256) * 1.0f, (140 / 256) * 1.0f, (0 / 256) * 1.0f);

}

void GetRandomGame::testFunction(int xMod, int yMod) {
	testx += xMod;
	testy += yMod;
}

void GetRandomGame::close() {
	cout << "GetRandomGame::close()" << endl;
	Environment::close(); // call the generic close function to close general stuff

//	delete _background;
//	delete _cat;
//	delete _hello;
//	delete _pave;
}
