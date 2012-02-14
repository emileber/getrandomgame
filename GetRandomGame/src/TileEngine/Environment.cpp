/*
 * Environment.cpp
 *
 *  Created on: 2011-12-18
 *      Author: Emile
 */
#include "Environment.h"
#include <iostream>

using namespace std;

namespace TileEngine {

Environment::Environment() {
	cout << "new Environment" << endl;
	_sdl = SDLInterface::getInstance();
	_graphic = Graphic::getInstance();
	_textureManager = Manager<Texture>::getInstance();
	_frameCount = 0;
	_screenWidth = 0;
	_screenHeight = 0;
	cout << "new Environment::End" << endl;
}

void Environment::init(int w, int h) {
	_screenWidth = w;
	_screenHeight = h;
	_gameTime.start();
}

void Environment::update() {
	_world->update();
	//cout << "Environment::update()" << endl;
}

void Environment::draw(){
	_world->draw();
}

void Environment::close() {
	cout << "Environment::close()" << endl;
}

}
