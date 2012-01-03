/*
 * Launcher.cpp
 *
 *  Created on: 2011-12-18
 *      Author: Emile
 */
#include "TileEngine.h"
#include "Environment.h"
#include "InputHandler.h"
#include <iostream>

using namespace std;

int main(int argc, char* args[]){
	cout << "Main START" << endl;
	TileEngine::getInstance()->start(Environment::getInstance(), new InputHandler);
	//string test;
	//cout << "enter somthing: ";
	//cin >> test;
	cout << "Main END" << endl;
	return 0;
}

