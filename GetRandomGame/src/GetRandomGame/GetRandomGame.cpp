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
#include <string>
#include <iostream>

#include "MapGenerator.h"
#include "WorldMap.h"
#include "Graphic/Font.h"
#include "Graphic/Sprite.h"
#include "GUI/GLabel.h"

using namespace std;

/***************************
 * TEST DECLARATIONS
 */
Texture * _background, *_pave, *_cat, *_grass;
SDL_Surface * _semiTransSurf;
GLfloat testx = 0, testy = 0;
Uint32 last = 0;
SectionRect * tileTestRect;
Font * _fontTest;
Sprite* _spriteTest;
GLabel* _testLabel;
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
	WorldMap* map = generator->GenerateANewWorld(129, 1.55, 36, 64444);
	map->DropXML();
	map->Draw();

	cout << "Map gen time: " << mGameTime.GetTimerTicks() - startTime << " ms"
			<< endl;

	/****************************************
	 *
	 * TEST INIT
	 *
	 */
	Manager<Texture> * _textMan = Manager<Texture>::getInstance();

	_pave = _textMan->LoadRessource("image/pave.png");
	_grass = _textMan->LoadRessource("image/grass.png");
	_spriteTest = new Sprite("image/gui_icons.png",
			new SectionRect(208, 0, 55, 54));
	_spriteTest->GetTexture()->SetStatic(true);

	//_testLabel = new GLabel("Bayvania Crossing", "font/Ellianarelle_Path.ttf");
	_testLabel = new GLabel("Bayvania Crossing",
			"font/Jellyka_Delicious_Cake.ttf");

	tileTestRect = new SectionRect(0, 0, 40, 40);

	_fontTest = new Font();
	_fontTest = Manager<Font>::getInstance()->LoadRessource(
			"font/Jellyka_Delicious_Cake.ttf");
	//_fontTest->SetSize(20);

	Manager<Font>::getInstance()->ListAllRessourceKey();
	Manager<Texture>::getInstance()->ListAllRessourceKey();

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

	// offset when fullscreen
	int xFullScreenOffset = ((mGraphic->GetWidth() - mScreenWidth) / 2);
	int yFullScreenOffset = ((mGraphic->GetHeight() - mScreenHeight) / 2);

	// background floor
	for (int x = 0; x < 30; x++) {
		for (int y = 14; y >= 0; y--) {
			tileTestRect->x = ((x * y + (x ^ y)) % 5) * 40;
			_pave->DrawSection(xFullScreenOffset + x * 40,
					yFullScreenOffset + y * 40, tileTestRect);
		}
	}

	/**
	 * Font test
	 */
	int xFont = mGraphic->GetWidth() - _fontTest->GetWidth("Bayvania Crossing");
	int yFont = mGraphic->GetHeight() - _fontTest->GetHeight() / 2 - 10;
	//mGraphic->DrawFilledRectangle(xFont, yFont,
	//		_fontTest->GetWidth("Bayvania Crossing"), _fontTest->GetHeight(),
	//		0.5, 1, 1, 1);

	//int size = 12;
	//for (int i = 0; i < 100; i++) {
	//_fontTest->SetSize(size++);
	_fontTest->Draw("Bayvania Crossing", 100 + xFont, yFont, 1, 0, 0, 0, 1);
	_fontTest->Draw(
			SdlInterface::getInstance()->IntToString(_fontTest->GetHeight()),
			100, yFont, 1, 0, 0, 0, 1);
	//}

	/**
	 * RECT test
	 */
	SectionRect* rectTest = new SectionRect(500, 500, 20, 20);
	Color3f* rectColor = new Color3f(0.5f, 0.5f, 1);
	mGraphic->DrawFilledRectangle(rectTest, rectColor, 1, true);
	mGraphic->DrawRectangle(rectTest, rectColor, 1, 2, true);
	mGraphic->DrawRectangle(20, 200, 42, 42, 1, 0, 0, 1, 3, true);
	mGraphic->DrawFilledRectangle(20, 100, 40, 40, 1, 1, 0, 1, true);

	/**
	 * GRASS tile test
	 */
	tileTestRect->x = 0;
	GLfloat red = testx / 100;
	mGraphic->DrawRectangle(xFullScreenOffset + 49, yFullScreenOffset + 49, 42,
			42, 1, 0, 0, 1, 2);
	_grass->DrawSection(xFullScreenOffset + 50, yFullScreenOffset + 50,
			tileTestRect, 1, 0, red, 1.0f, 0.0f);

	/**
	 * Menu tests
	 */
	_spriteTest->Draw(200, 200);
	_testLabel->Draw(303, 200);
}

void GetRandomGame::testFunction(int xMod, int yMod) {
	testx += xMod;
	testy += yMod;
	Camera::getInstance()->move(-xMod, -yMod);
}

void GetRandomGame::Close() {
	cout << "GetRandomGame::close()" << endl;
	Environment::Close(); // call the generic close function to close general stuff
}
