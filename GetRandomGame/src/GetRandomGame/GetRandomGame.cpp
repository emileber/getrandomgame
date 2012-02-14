/*
 * GetRandomGame.cpp
 *
 *  Created on: 2012-01-03
 *      Author: Emile
 */

#include "GetRandomGame.h"
#include "Texture.h"
#include <ctime>
#include <iostream>

using namespace std;

/***************************
 * TEST DECLARATIONS
 */
Texture * _background, *_pave, *_cat, *_grass;
SDL_Surface * _semiTransSurf;
GLfloat testx = 0, testy = 0;
Uint32 last = 0;
SectionRect * tileTestRect;
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
	Manager<Texture> * _textMan = Manager<Texture>::getInstance();

	_pave = _textMan->loadRessource("image/pave.png");
	_grass = _textMan->loadRessource("image/grass.png");

	tileTestRect = new SectionRect;
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

	// background floor
	for (int x = 0; x < 30; x++) {
		for (int y = 0; y < 15; y++) {
			tileTestRect->x = ((x * y + (x ^ y)) % 5) * 40;
			_pave->drawSection(x * 40, y * 40, tileTestRect);
		}
	}


	// GRASS tile test
	tileTestRect->x = 0;
	GLfloat red = testx / 100;
	_graphic->drawFilledRectangle(49, 49, 42, 42, 1, 0, 0, 1);
	_grass->drawSection(50, 50, tileTestRect, 1, 0, red, 1.0f, 0.0f);
	_graphic->drawFilledRectangle(99, 49, 42, 42, 1, 0, 0, 1);
	_grass->drawSection(100, 50, tileTestRect, 1, 0, 0.90f, 1.0f, 0.0f);
	_graphic->drawFilledRectangle(149, 49, 42, 42, 1, 0, 0, 1);
	_grass->drawSection(150, 50, tileTestRect, 1, 0, 0.75f, 1.0f, 0.0f);
	_graphic->drawFilledRectangle(199, 49, 42, 42, 1, 0, 0, 1);
	_grass->drawSection(200, 50, tileTestRect, 1, 0, 0.5f, 1.0f, 0.0f);
	_graphic->drawFilledRectangle(249, 49, 42, 42, 1, 0, 0, 1);
	_grass->drawSection(250, 50, tileTestRect, 1, 0, 0.25f, 1.0f, 0.0f);
	_graphic->drawFilledRectangle(299, 49, 42, 42, 1, 0, 0, 1);
	_grass->drawSection(300, 50, tileTestRect, 1, 0, 1, 1, 1);

}

void GetRandomGame::testFunction(int xMod, int yMod) {
	testx += xMod;
	testy += yMod;
}

void GetRandomGame::close() {
	cout << "GetRandomGame::close()" << endl;
	Environment::close(); // call the generic close function to close general stuff
}
