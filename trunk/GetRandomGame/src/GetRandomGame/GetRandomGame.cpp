/*
 * GetRandomGame.cpp
 *
 *  Created on: 2012-01-03
 *      Author: Emile
 */

/**
 * Last Update:
 * -
 */

#include <ctime>
#include <string>
#include <iostream>

#include "GetRandomGame.h"

#include "WorldMap.h"
#include "MapGenerator.h"

#include "Graphic/Texture.h"
#include "Graphic/Camera.h"
#include "Graphic/Sprite.h"
#include "Graphic/MultiTintedSprite.h"
#include "Graphic/Font.h"

#include "GUI/GLabel.h"
#include "GUI/GTextArea.h"

#include "GameUI/GameUI.h"

using namespace std;

/***************************
 * TEST DECLARATIONS
 */
Texture *_pave, *_grass;
float testx = 0, testy = 0;
SectionRect * tileTestRect;
MultiTintedSprite* _MultiTintedSpriteTest;
Sprite* _spriteTest;
GLabel * _testCoordLabel;
GTextArea * _console;
/**
 * END OF TEST DECLARATIONS
 ***************************/

GetRandomGame::GetRandomGame() {
	cout << "new GetRandomGame()" << endl;

	mGuiContainer = new GameUI();

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
	//WorldMap* map = generator->GenerateANewWorld(129, 1.55, 36, 64444);
	mWorld = generator->GenerateANewWorld(129, 1.55, 36, 666666);

	//mWorld->Draw();

	cout << "Map gen time: " << mGameTime.GetTimerTicks() - startTime << " ms"
			<< endl;

	/****************************************
	 *
	 * TEST INIT
	 *
	 */

	Manager<Font>::getInstance()->LoadRessource("font/CaslonBold.ttf")->SetSize(
			20);
	Manager<Font>::getInstance()->LoadRessource("font/Ellianarelle_Path.ttf")->SetSize(
			50);
	Manager<Font>::getInstance()->LoadRessource(
			"font/Jellyka_Delicious_Cake.ttf")->SetSize(80);

	_pave = mTextureManager->LoadRessource("image/pave.png");
	_grass = NULL;
	_grass = mTextureManager->LoadRessource("image/grass.png");
	if (_grass == NULL) {
		cout << "grass est NULL" << endl;
	}
	_MultiTintedSpriteTest = new MultiTintedSprite(_grass,
			new SectionRect(0, 0, 40, 40));
	//_spriteTest->GetTexture()->SetStatic(true);

	tileTestRect = new SectionRect(0, 0, 40, 40);

	//_spriteTest = new Sprite("image/gui_icons.png",
	//		new SectionRect(311, 0, 48, 54));

	_spriteTest = new Sprite("image/fuck_light.png",
			new SectionRect(0, 0, 512, 256));

	//
	// Menu tests
	//
	cout << "init" << endl;
	_testCoordLabel = new GLabel("(0, 0)", "font/Ellianarelle_Path.ttf");
//	_testCoordLabel->SetOffset(10,
//			mScreenHeight - 10 - _testCoordLabel->Height());
	_testCoordLabel->SetOffset(10, 10);
	_testCoordLabel->SetColor(255, 255, 255);
	//_testCoordLabel->Y(mScreenHeight - 10 - _testCoordLabel->Height());
	mGuiContainer->PushMenu(_testCoordLabel);

	_console = new GTextArea();
	_console->SetFont("font/CaslonBold.ttf");
	_console->SetOffset(3, 3);
	_console->SetSize(450, 190);
	//mGuiContainer->PushMenu(_console);

	_console->PrintLine("Test line in the CONSOLE!");
	_console->PrintLine(
			"abcdefghijklmnopqrstuvwxyz gsfgsfgs f sfg sfg sg sg srsgrserg sg s gs fgs efawefas fghsdf gafaw efsfsdgdfg");
	for (int i = 0; i <= 20; i++) {
		_console->PrintLine("Test line " + mGraphic->NumberToString(i));
	}
	_console->PrintLine(
			"Salut, ca va, je viens de terminer les premiers tests de word wrapping dans le tout nouveau log de texte que j'ai fait. Note: j'ai remarque (<-justement) que les accents ne fonctionne pas :/");

	((WorldMap*) mWorld)->Scale(1.0f - (testx / (40 * 129)));

	/*
	 * END OF TEST INIT
	 ****************************************/

	cout << "GetRandomGame::init()::End" << endl;
}

void GetRandomGame::Update() {
	//cout << "GetRandomGame::update() | ";

	/**
	 * TEST ZONE
	 */

} // END of update()

void GetRandomGame::Draw() {

	/***************************************************************************
	 *  TEST ZONE
	 */

	// DRAWS LIGHTMAP
	mGraphic->ToggleBlendMode();

	// START DARKENING
	mGraphic->DrawFilledRectangle(0, 0, mScreenWidth, mScreenHeight, 0.1, 0.1,
			0.1, 1);

	_spriteTest->Draw(testx, testy, 1, 0, new Color3f(1, 0, 0), 0.98f);

	mGraphic->DrawLight(mScreenWidth/2, mScreenHeight/2, 300, 1, 1, 1, 0.3, 1);
	mGraphic->DrawLight(mScreenWidth/2, mScreenHeight/2, 150, 1, 1, 1, 1, 1);

//	mGraphic->DrawLight(500, 100, 100, 1, 1, 1, 1, 0.9);
//	mGraphic->DrawLight(50, 500, 150, 1, 1, 1, 1, 0.8);
//	mGraphic->DrawLight(100, 250, 100, 1, 1, 1, 1, 1);
//	mGraphic->DrawLight(100, 250, 100, 1, 1, 1, 1, 1);

	//mGraphic->DrawLight(testx, testy, 150, 1, 1, 0, 1, 1);


	mGraphic->ToggleBlendMode();

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
//	GLfloat red = 1.0f;
//	GLfloat green = 1.0f;
//	for (int x = 15; x < 30; x++) {
//		red = 1 - ((float) x / 30);
//
//		for (int y = 7; y >= 0; y--) {
//			green = ((float) y / 14);
//			_MultiTintedSpriteTest->SetColor(0, 0, red, green, 0.0f);
//			_MultiTintedSpriteTest->SetColor(0, 1, red, green, 0.0f);
//			_MultiTintedSpriteTest->SetColor(1, 0, red, green, 0.0f);
//			_MultiTintedSpriteTest->SetColor(1, 1, red, green, 0.0f);
	//_MultiTintedSpriteTest->Draw(40, 40);
//		}
//
//	}
	//mGraphic->DrawLine(100, 100, 40, 40, 1, 1, 1, 1, 3, false);
	//for (int i = 0; i < 10000; i++) {
	//mGraphic->DrawLight(testx, testy, 50, 1, 0.5, 0, 1, 1);
	//mGraphic->DrawLight(100, 100, 100, 1, 0.5, 0, 1, 1);
	//_spriteTest->Draw(testx, testy, 1, 0, NULL, 0.98f);
	//}
	/*
	 * FIN TEST ZONE
	 ***************************************************************************/

	/*****
	 * Game World Draw
	 */
	//mWorld->Draw();
	/*****
	 * Graphical User Interface Rendering
	 */
	mGuiContainer->Draw();

}

void GetRandomGame::testFunction(int xMod, int yMod) {
	testx = xMod;
	testy = (-yMod) + mScreenHeight;
	//Camera::getInstance()->move(-xMod, -yMod);
	_testCoordLabel->SetText(
			"(" + mGraphic->NumberToString(testx) + ", "
					+ mGraphic->NumberToString(testy) + ")");

	((WorldMap*) mWorld)->Scale(1.0f - (testx / (40 * 129)));
}

void GetRandomGame::Close() {
	cout << "GetRandomGame::close()" << endl;
}
