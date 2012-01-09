/*
 * Environment.cpp
 *
 *  Created on: 2011-12-18
 *      Author: Emile
 */
#include "Environment.h"
#include <iostream>

using namespace std;

Environment::Environment() {
	cout << "new Environment" << endl;
	_world = new World();
	_sdl = SDLInterface::getInstance();
	_frameCount = 0;
	_screenWidth = 0;
	_screenHeight = 0;
	cout << "new Environment::End" << endl;
}

void Environment::init(int w, int h) {
	_screenWidth = w;
	_screenHeight = h;
}

void Environment::update() {
	//cout << "Environment::update()" << endl;
}

void Environment::close() {
	cout << "Environment::close()" << endl;
}

void Environment::outputTime() {
	// Render the FPS on screen
	int total = _gameTime.get_ticks();
	//int minute = total / 60000;
	//int second = total % 60000;

	//string timeString = "Time: " + intToString(minute) + ":" + intToString(second);
	string timeString = "Time: " + intToString(total);
	_sdl->renderText(10, 20, timeString, 200);
}

string Environment::intToString(int number) {
	//Une chaine de caracteres temporaire
	char caption[64];

	//On calcule le nombre de frames par seconde et on cree la chaine de caracteres
	sprintf(caption, "%f", (float) number);

	return static_cast<string>(caption);
}
