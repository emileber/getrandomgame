/*
 * GetRandomGame.cpp
 *
 *  Created on: 2012-01-03
 *      Author: Emile
 */

#include "GetRandomGame.h"
#include "Animation.h"
#include "SpriteSheet.h"
#include <ctime>
#include <iostream>

using namespace std;

Sprite * _background, *_hello, *_cat, *_pave;
int test = 0;

GetRandomGame::GetRandomGame() {
	cout << "new GetRandomGame()" << endl;

	cout << "new GetRandomGame()::End" << endl;
}

void GetRandomGame::init(int w, int h) {
	cout << "GetRandomGame::init()" << endl;
	Environment::init(w, h); // parent class init
	srand((unsigned) time(0)); // seed the random gen
	_gameTime.start();

	/**
	 *
	 * TEST ZONE
	 *
	 */
	_background = new Sprite(0, 0, "image/background.bmp");
	_hello = new Sprite(250, 190, "image/hello_world.bmp");
	_cat = new Animation(500, 190, 95, 120, "image/cat.bmp", 4, 150);
	_pave = new SpriteSheet(10, 300, 40, 40, "image/pave.bmp", 5);
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
	_sdl->pushSprite(_background, BACKGROUND_LAYER);
	_sdl->pushSprite(new Sprite(_background->getWidth(), 0, _background),
			BACKGROUND_LAYER);
	_sdl->pushSprite(
			new Sprite(_background->getWidth(), _background->getHeight(),
					_background), BACKGROUND_LAYER);
	_sdl->pushSprite(new Sprite(0, _background->getHeight(), _background),
			BACKGROUND_LAYER);

	// Floor Stuff

	_pave->setClipId(0);
	_sdl->pushSprite(_pave, GROUND_LAYER);
	_sdl->pushSprite(new SpriteSheet(50, 300, _pave, 1), GROUND_LAYER);
	_sdl->pushSprite(new SpriteSheet(90, 300, _pave, 2), GROUND_LAYER);
	_sdl->pushSprite(new SpriteSheet(130, 300, _pave, 3), GROUND_LAYER);
	_sdl->pushSprite(new SpriteSheet(170, 300, _pave, 4), GROUND_LAYER);

	// Cat stuff
	_sdl->pushSprite(_cat, PEOPLE_LAYER);
	((Animation*)_cat)->nextFrame(_gameTime.get_ticks());

}

void GetRandomGame::close() {
	cout << "GetRandomGame::close()" << endl;
	Environment::close(); // call the generic close function to close general stuff

	delete _background;
	delete _cat;
	delete _hello;
}
