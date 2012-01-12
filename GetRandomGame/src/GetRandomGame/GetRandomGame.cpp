/*
 * GetRandomGame.cpp
 *
 *  Created on: 2012-01-03
 *      Author: Emile
 */

#include "GetRandomGame.h"
#include "Animation.h"
#include <iostream>

using namespace std;

Animation * _background, *_hello, *_cat;
int test = 0, catTimer = 250;

GetRandomGame::GetRandomGame() {
	cout << "new GetRandomGame()" << endl;

	cout << "new GetRandomGame()::End" << endl;
}

void GetRandomGame::init(int w, int h) {
	cout << "GetRandomGame::init()" << endl;
	Environment::init(w, h); // parent class init

	_gameTime.start();

	/**
	 *
	 * TEST ZONE
	 *
	 */
	_background = new Animation(0, 0, "background.bmp");
	_hello = new Animation(250, 190, "hello_world.bmp");
	_cat = new Animation(500, 190, 95, 120, "cat.bmp", 4);
	_sdl->setTextColor(255, 0, 0);

	cout << "GetRandomGame::init()::End" << endl;
}

void GetRandomGame::update() {
	//cout << "GetRandomGame::update()" << endl;

	Environment::update(); // generic update
	// then game specific update
	outputTime(); // Show the total up time

	/**
	 * TEST ZONE
	 */
	_sdl->pushSprite(_background, 0);
	_sdl->pushSprite(new Animation(_background->getWidth(), 0, _background), 0);
	_sdl->pushSprite(
			new Animation(_background->getWidth(), _background->getHeight(),
					_background), 0);
	_sdl->pushSprite(new Animation(0, _background->getHeight(), _background), 0);

	if (_gameTime.get_ticks() < 5000) {
		_sdl->pushSprite(_hello, 1);
	}

	_sdl->renderText(300, 200, "BOOBS", test++, 40);

	_sdl->pushSprite(_cat);
	if (_gameTime.get_ticks() > (catTimer + 150)) {
		_cat->nextFrame();
		catTimer = _gameTime.get_ticks();
	}

}

void GetRandomGame::close() {
	cout << "GetRandomGame::close()" << endl;
	Environment::close(); // call the generic close function to close general stuff

	delete _background; // test
}
