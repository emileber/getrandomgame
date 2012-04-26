/*
 * Environment.cpp
 *
 *  Created on: 2011-12-18
 *      Author: Emile
 */

#include <iostream>

#include "Environment.h"

using namespace std;

namespace TileEngine {

Environment::Environment() {
	cout << "new Environment" << endl;
	mGraphic = Graphic::getInstance();
	mTextureManager = Manager<Texture>::getInstance();
	mFrameCount = 0;
	mScreenWidth = 0;
	mScreenHeight = 0;
	cout << "new Environment::End" << endl;
}

void Environment::Init(int w, int h) {
	mScreenWidth = w;
	mScreenHeight = h;
	mGameTime.Start();
}


}
