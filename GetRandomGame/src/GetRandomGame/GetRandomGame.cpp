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
//#include "Graphic/Sprite.h"
#include "Graphic/MultiTintedSprite.h"
#include "GUI/GLabel.h"

using namespace std;

/***************************
 * TEST DECLARATIONS
 */
Texture *_pave, *_grass;
GLfloat testx = 0, testy = 0;
SectionRect * tileTestRect;
Font * _fontTest;
MultiTintedSprite* _MultiTintedSpriteTest;
Sprite* _spriteTest;
GLabel* _testLabel, *_testCoordLabel;
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

//	uint32_t startTime = mGameTime.GetTimerTicks();
//	cout << "StarTime: " << startTime << " ms" << endl;
//
//	MapGenerator* generator = new MapGenerator();
//
//	//WorldMap* map = generator->GenerateANewWorld(65, 1.55,36,time(0));
//	WorldMap* map = generator->GenerateANewWorld(129, 1.55, 36, 64444);
//	map->DropXML();
//	map->Draw();
//
//	cout << "Map gen time: " << mGameTime.GetTimerTicks() - startTime << " ms"
//			<< endl;

	/****************************************
	 *
	 * TEST INIT
	 *
	 */

	_pave = mTextureManager->LoadRessource("image/pave.png");
	_grass = NULL;
	_grass = mTextureManager->LoadRessource("image/grass.png");
	if (_grass == NULL) {
		cout << "grass est NULL" << endl;
	}
	_MultiTintedSpriteTest = new MultiTintedSprite(_grass,
			new SectionRect(0, 0, 40, 40));
	//_spriteTest->GetTexture()->SetStatic(true);

	//_testLabel = new GLabel("Bayvania Crossing", "font/Ellianarelle_Path.ttf");
	//_testLabel = new GLabel("Bayvania Crossing", "font/CaslonBold.ttf");
	_testLabel = new GLabel("Bayvania Crossing",
			"font/Jellyka_Delicious_Cake.ttf");
	_testLabel->SetSize(17);
	_testLabel->SetColor(255, 255, 255);
	_testLabel->IsStatic(false);

	_testCoordLabel = new GLabel("Bayvania Crossing", "font/CaslonBold.ttf");

	tileTestRect = new SectionRect(0, 0, 40, 40);

	_fontTest = new Font();
	_fontTest = Manager<Font>::getInstance()->LoadRessource(
			"font/Jellyka_Delicious_Cake.ttf");

	_spriteTest = new Sprite("image/gui_icons.png",
			new SectionRect(311, 0, 48, 54));

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
	 * GRASS tile test
	 */
	GLfloat red = 1.0f;
	GLfloat green = 1.0f;
	for (int x = 15; x < 30; x++) {
		red = 1 - ((float) x / 30);

		for (int y = 7; y >= 0; y--) {
			green = ((float) y / 14);
			_MultiTintedSpriteTest->SetColor(0, 0, red, green, 0.0f);
			_MultiTintedSpriteTest->SetColor(0, 1, red, green, 0.0f);
			_MultiTintedSpriteTest->SetColor(1, 0, red, green, 0.0f);
			_MultiTintedSpriteTest->SetColor(1, 1, red, green, 0.0f);

			_MultiTintedSpriteTest->Draw(xFullScreenOffset + x * 40,
					yFullScreenOffset + y * 40);
			//_testLabel->SetText(
			//		"(" + SdlInterface::getInstance()->IntToString(x) + ","
					//		+ SdlInterface::getInstance()->IntToString(y)
					//		+ ")");
			//mGraphic->DrawFilledRectangle(xFullScreenOffset + x * 40,
			//		yFullScreenOffset + y * 40 - 1, 40, 17, 0, 0, 0);
			//_testLabel->Draw(xFullScreenOffset + x * 40,
			//		yFullScreenOffset + y * 40 + 1);

		}

	}
	/**
	 * Menu tests
	 */
	//_spriteTest->Draw(200, 200);

	/**
	 * Test coord screen output
	 */
	_testCoordLabel->Draw(10, mScreenHeight - 10 - _testCoordLabel->Height());

	/**
	 * font bug test
	 *
	 */

	/*
	Si j'enlève tout output/draw et que je draw uniquement du text:
	4000 lines = 12 fps (unplayable fps limit)
	3000 lines = 16 fps
	2000 lines = 24 fps (Dramatic fps limit)
	1500 lines = 32 fps
	1150 lines = 43 fps
	1000 lines = 48 fps
	700 lines = 69 fps
	600 lines = 80 fps
	500 lines = 95 fps
	400 lines = 118 fps
	300 lines = 153 fps
	221 lines = 199 fps (premier changement)
	200 lines = 220 fps
	100 lines = 394 fps
	1 line = 593 fps
	*/



//	for (GLfloat x = 0; x < testx; x++) {
//		_testLabel->Draw(100, 100);
//	}

	//mGraphic->DrawLine(100, 100, 40, 40, 1, 1, 1, 1, 3, false);
}

void GetRandomGame::testFunction(int xMod, int yMod) {
	testx += xMod;
	testy += yMod;
	Camera::getInstance()->move(-xMod, -yMod);
	_testCoordLabel->SetText("("+mSdlInterface->IntToString(testx)+", "+mSdlInterface->IntToString(testy)+")");
}

void GetRandomGame::Close() {
	cout << "GetRandomGame::close()" << endl;
	Environment::Close(); // call the generic close function to close general stuff
}
