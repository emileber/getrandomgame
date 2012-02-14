/*
 * Launcher.cpp
 *
 *  Created on: 2011-12-18
 *      Author: Emile
 */
#include "Engine.h"
#include "GetRandomGame.h"
#include "GRGInputHandler.h"
#include <iostream>


using namespace std;

const int DEFAULT_FONT_SIZE = 15;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* args[]) {
	//cout << "Main START" << endl;
	TileEngine::Engine::getInstance()->init(SCREEN_WIDTH, SCREEN_HEIGHT,
			"Tile Game test", "CaslonBold.ttf", new GetRandomGame(),
			new GRGInputHandler());
	TileEngine::Engine::getInstance()->start();



	cout << "Main END" << endl;
	return 0;
}

