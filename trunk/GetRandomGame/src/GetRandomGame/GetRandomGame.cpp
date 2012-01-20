/*
 * GetRandomGame.cpp
 *
 *  Created on: 2012-01-03
 *      Author: Emile
 */

#include "GetRandomGame.h"
#include "Animation.h"
#include "Sprite.h"
#include <ctime>
#include <iostream>

using namespace std;

/***************************
 * TEST DECLARATIONS
 */
Sprite * _background, *_hello, *_cat, *_pave;
SDL_Surface * _semiTransSurf;
int testx = 0, testy = 0, last = 0;
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
	_gameTime.start();
	printf("timer start OK\n");

	/**
	 *
	 * TEST ZONE
	 *
	 */
	_background = new Sprite(0, 0, "image/background.bmp");
	_hello = new Sprite(250, 190, "image/hello_world.bmp");
	_cat = new Animation(500, 190, 95, 120, "image/cat.bmp", 4, 150);
	_pave = new Sprite(-10, 300, 40, 40, "image/pave.bmp");
	printf("new Sprite OK\n");
	//_cat->
	_sdl->setTextColor(255, 0, 0);

	cout << "GetRandomGame::init()::End" << endl;
}

void GetRandomGame::update() {
	//cout << "GetRandomGame::update()" << endl;

	Environment::update(); // generic update
	// then game specific update
	//outputTime(); // Show the total up time

	/**
	 * TEST ZONE
	 */
//	_semiTransSurf = _sdl->createSurface(50, 500);
//	_sdl->apply_surface(-10, 10, _hello->getSurface(), 255, NULL,
//			_semiTransSurf);
//	_sdl->pushSprite(new Sprite(400, 0, _semiTransSurf), DEBUG_LAYER);
	// Background
//	_sdl->pushSprite(_background, BACKGROUND_LAYER);
//	_sdl->pushSprite(new Sprite(_background->getWidth(), 0, _background),
//			BACKGROUND_LAYER);
//	_sdl->pushSprite(
//			new Sprite(_background->getWidth(), _background->getHeight(),
//					_background), BACKGROUND_LAYER);
//	_sdl->pushSprite(new Sprite(0, _background->getHeight(), _background),
//			BACKGROUND_LAYER);
	// Floor Stuff
	_sdl->pushSprite(_pave, GROUND_LAYER);
	int cpt = 0;
	for (int y = 0; y < 15; y++) {
		for (int i = 0; i < 25; i++) {
			Sprite * tempSprite = new Sprite((i * 40), (y * 40), _pave);
			tempSprite->setClipId((i * (y + cpt++)) % tempSprite->getNbImageX(),
					0);
			_sdl->pushSprite(tempSprite, GROUND_LAYER);
		}
	}

	// Cat stuff
	if (_gameTime.get_ticks() > (last + MOVE_TIME)) {
		//printf("move the cat, last: %10d, time: %10d\n", last,
		//		_gameTime.get_ticks());
		last = _gameTime.get_ticks();
		_cat->setPoint(_cat->getX() + testx, _cat->getY() + testy);
	}
	_sdl->pushSprite(_cat, PEOPLE_LAYER);
	((Animation*) _cat)->nextFrame(_gameTime.get_ticks());

	// render the directions pixel mod
	_sdl->renderText(500, 20, DEBUG_LAYER,
			_sdl->intToString(testx) + ", " + _sdl->intToString(testy));

	//cout << "GetRandomGame::update()::End" << endl;
} // END of update()

void GetRandomGame::testFunction(int xMod, int yMod) {
	testx = xMod * MOVE_DISTANCE;
	testy = yMod * MOVE_DISTANCE;
}

void GetRandomGame::close() {
	cout << "GetRandomGame::close()" << endl;
	Environment::close(); // call the generic close function to close general stuff

	delete _background;
	delete _cat;
	delete _hello;
	delete _pave;
}
