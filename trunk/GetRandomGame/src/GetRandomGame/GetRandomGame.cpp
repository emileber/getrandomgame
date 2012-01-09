/*
 * GetRandomGame.cpp
 *
 *  Created on: 2012-01-03
 *      Author: Emile
 */

#include "GetRandomGame.h"
#include "Sprite.h"
#include <iostream>

using namespace std;

Sprite * _background, *_hello;
int test = 0;

GetRandomGame::GetRandomGame() {
	cout << "new GetRandomGame()" << endl;

	cout << "new GetRandomGame()::End" << endl;
}

void GetRandomGame::init(int w, int h) {
	Environment::init(w,h);
	cout << "GetRandomGame::init()" << endl;
	_background = new Sprite(0, 0, "background.bmp");
	_hello = new Sprite(250, 190, "hello_world.bmp");
	_sdl->setTextColor(255, 0, 0);
	_gameTime.start();
	cout << "GetRandomGame::init()::End" << endl;
}

void GetRandomGame::update() {
	cout << "GetRandomGame::update()" << endl;

	Environment::update(); // generic update
	// then game specific update

	/**
	 * TEST ZONE
	 */

	if (_gameTime.get_ticks() < 5000) {
		_sdl->pushSprite(_hello, 1);
	}
	_sdl->pushSprite(new Sprite(900, 0, _hello), 1);
	_sdl->pushSprite(_background, 0);
	_sdl->renderText(300, 200, "BOOBS", test++);
	outputTime();
}


void GetRandomGame::close() {
	cout << "GetRandomGame::close()" << endl;
	Environment::close(); // call the generic close function to close general stuff

	delete _background; // test
}
