/*
 * Environment.cpp
 *
 *  Created on: 2011-12-18
 *      Author: Emile
 */
#include "Environment.h"
#include <iostream>

using namespace std;

Environment::Environment(){
	cout << "new Environment" << endl;
	_world = new World();
	_sdl = SDLInterface::getInstance();
	cout << "new Environment::End" << endl;
}

