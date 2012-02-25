/*
 * Launcher.cpp
 *
 *  Created on: 2011-12-18
 *      Author: Emile
 *
 *      Used to launch the game
 *
 */
#include "Engine.h"
#include "GetRandomGame.h"
#include "GrgInputHandler.h"
#include <iostream>
#include "Global.h"

using namespace std;



int main(int argc, char* args[]) {
	//cout << "Main START" << endl;



	TileEngine::Engine::getInstance()->Init(SCREEN_WIDTH, SCREEN_HEIGHT,
			"Tile Game test", new GetRandomGame(),
			new GrgInputHandler());
	TileEngine::Engine::getInstance()->Start();



	cout << "Main END" << endl;
	return 0;
}

