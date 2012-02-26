/*
 * GetRandomGame.cpp
 *
 *  Created on: 2012-01-03
 *      Author: Emile
 */

#include "GetRandomGame.h"
#include "WorldMap.h"
#include "Graphic/Texture.h"
#include "Graphic/Camera.h"
#include <ctime>
#include <iostream>

#include "MapGenerator.h"
#include "WorldMap.h"

using namespace std;

/***************************
 * TEST DECLARATIONS
 */
Texture * _background, *_pave, *_cat, *_grass;
SDL_Surface * _semiTransSurf;
GLfloat testx = 0, testy = 0;
Uint32 last = 0;
SectionRect * tileTestRect;
/**
 * END OF TEST DECLARATIONS
 ***************************/

GetRandomGame::GetRandomGame() {
	cout << "new GetRandomGame()" << endl;

	cout << "new GetRandomGame()::End" << endl;
}

void GetRandomGame::Init(int w, int h) {
	cout << "GetRandomGame::init()" << endl;
	Environment::Init(w, h); // parent class init
	//srand((unsigned) time(0)); // seed the random gen
	//srand(5);

	uint32_t startTime = mGameTime.GetTimerTicks();
	cout << "StarTime: " << startTime << " ms" << endl;

	MapGenerator* generator = new MapGenerator();

	//WorldMap* map = generator->GenerateANewWorld(65, 1.55,36,time(0));
	WorldMap* map = generator->GenerateANewWorld(129, 1.55, 36, 87654);
	map->DropXML();
	map->Draw();

	cout << "Map gen time: " << mGameTime.GetTimerTicks() - startTime << " ms" << endl;

	/****************************************
	 *
	 * TEST INIT
	 *
	 */
	Manager<Texture> * _textMan = Manager<Texture>::getInstance();

	_pave = _textMan->LoadRessource("image/pave.png");
	_grass = _textMan->LoadRessource("image/grass.png");

	tileTestRect = new SectionRect;
	tileTestRect->x = 0;
	tileTestRect->y = 0;
	tileTestRect->w = 40;
	tileTestRect->h = 40;

//	Uint32 start = _gameTime.get_ticks();
//
//	cout << "Map Generation: " << (_gameTime.get_ticks() - start) << " ms" << endl;

	/*
	 * END OF TEST INIT
	 ****************************************/

	cout << "GetRandomGame::init()::End" << endl;
}

void GetRandomGame::Update() {
	//cout << "GetRandomGame::update() | ";

	Environment::Update(); // generic update

	// then game specific update
	//_sdl->renderText(10, 20, DEBUG_LAYER, _sdl->formatTime(_gameTime.get_ticks())); // Show the total up time

	/**
	 * TEST ZONE
	 */

} // END of update()

void GetRandomGame::Draw() {

	int xFullScreenOffset = ((mGraphic->GetWidth() - mScreenWidth)/2);
	int yFullScreenOffset = ((mGraphic->GetHeight() - mScreenHeight)/2);

	// test square that show screen window dimensions
	mGraphic->DrawFilledRectangle(xFullScreenOffset-1, yFullScreenOffset-1, mScreenWidth+2, mScreenHeight+2, 1, 0, 0, 1);

	// background floor
	for (int x = 0; x < 30; x++) {
		for (int y = 14; y >= 0; y--) {
			tileTestRect->x = ((x * y + (x ^ y)) % 5) * 40;
			_pave->DrawSection(xFullScreenOffset + x * 40, yFullScreenOffset + y * 40, tileTestRect);
		}
	}



	// GRASS tile test
	tileTestRect->x = 0;
	GLfloat red = testx / 100;
	mGraphic->DrawFilledRectangle(xFullScreenOffset + 49, yFullScreenOffset + 49, 42, 42, 1, 0, 0, 1);
	_grass->DrawSection(xFullScreenOffset + 50, yFullScreenOffset + 50, tileTestRect, 1, 0, red, 1.0f, 0.0f);
	mGraphic->DrawFilledRectangle(xFullScreenOffset + 99, yFullScreenOffset + 49, 42, 42, 1, 0, 0, 1);
	_grass->DrawSection(xFullScreenOffset + 100, yFullScreenOffset + 50, tileTestRect, 1, 0, 0.90f, 1.0f, 0.0f);
	mGraphic->DrawFilledRectangle(xFullScreenOffset + 149, yFullScreenOffset + 49, 42, 42, 1, 0, 0, 1);
	_grass->DrawSection(xFullScreenOffset + 150, yFullScreenOffset + 50, tileTestRect, 1, 0, 0.75f, 1.0f, 0.0f);
	mGraphic->DrawFilledRectangle(xFullScreenOffset + 199, yFullScreenOffset + 49, 42, 42, 1, 0, 0, 1);
	_grass->DrawSection(xFullScreenOffset + 200, yFullScreenOffset + 50, tileTestRect, 1, 0, 0.5f, 1.0f, 0.0f);
	mGraphic->DrawFilledRectangle(xFullScreenOffset + 249,yFullScreenOffset +  49, 42, 42, 1, 0, 0, 1);
	_grass->DrawSection(xFullScreenOffset + 250, yFullScreenOffset + 50, tileTestRect, 1, 0, 0.25f, 1.0f, 0.0f);
	mGraphic->DrawFilledRectangle(xFullScreenOffset + 299, yFullScreenOffset + 49, 42, 42, 1, 0, 0, 1);
	_grass->DrawSection(xFullScreenOffset + 300, yFullScreenOffset + 50, tileTestRect, 1, 0, 1, 1, 1);

}

void GetRandomGame::testFunction(int xMod, int yMod) {
	//testx += xMod;
	//testy += yMod;
	Camera::getInstance()->move(-xMod, -yMod);
}

void GetRandomGame::Close() {
	cout << "GetRandomGame::close()" << endl;
	Environment::Close(); // call the generic close function to close general stuff
}
