/*
 * GetRandomGame.cpp
 *
 *  Created on: 2012-01-03
 *      Author: Emile
 */

/**
 * Last Update:
 * - Changed IntToString to NumberToString template function
 * - GTextArea en construction
 * - GameUI est implementer et gere correctement les UI(Menu)
 * - Correction de Font (p,y,g,q and j getting below their belonging place)
 * - Ajout de const pour securiser les donnees (Font particulierement)
 * - Word wrap fonctionne dans le GTextArea
 * - Creation de GText qui gere des mots et des lignes pour le word wrap
 * - GText gere aussi une couleur par mot au besoin
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
#include "GUI/GTextArea.h"
#include "GameUI/GameUI.h"

using namespace std;

/***************************
 * TEST DECLARATIONS
 */
Texture *_pave, *_grass;
GLfloat testx = 0, testy = 0;
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

	cout << "new GetRandomGame()::End" << endl;
}

void GetRandomGame::Init(int w, int h) {
	cout << "GetRandomGame::init()" << endl;
	Environment::Init(w, h); // parent class init
	mGuiContainer = new GameUI();

	//srand((unsigned) time(0)); // seed the random gen
	//srand(5);

	uint32_t startTime = mGameTime.GetTimerTicks();
	cout << "StarTime: " << startTime << " ms" << endl;

	MapGenerator* generator = new MapGenerator();

	//WorldMap* map = generator->GenerateANewWorld(65, 1.55,36,time(0));
	//WorldMap* map = generator->GenerateANewWorld(129, 1.55, 36, 64444);
	mWorld = generator->GenerateANewWorld(129, 1.55, 36, 64444);
	((WorldMap*) mWorld)->DropXML();
	mWorld->Draw();

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

	_spriteTest = new Sprite("image/gui_icons.png",
			new SectionRect(311, 0, 48, 54));

	cout << "init" << endl;
	_testCoordLabel = new GLabel("(0, 0)",
			"font/Ellianarelle_Path.ttf");
	_testCoordLabel->SetOffset(10,
			mScreenHeight - 10 - _testCoordLabel->Height());
	_testCoordLabel->SetColor(255, 255, 255);
	//_testCoordLabel->Y(mScreenHeight - 10 - _testCoordLabel->Height());
	mGuiContainer->PushMenu(_testCoordLabel);

	_console = new GTextArea();
	_console->SetFont("font/CaslonBold.ttf");
	_console->SetOffset(3, 3);
	_console->SetSize(450, 190);
	mGuiContainer->PushMenu(_console);

	_console->PrintLine("Test line in the CONSOLE!");
	_console->PrintLine("abcdefghijklmnopqrstuvwxyz gsfgsfgs f sfg sfg sg sg srsgrserg sg s gs fgs efawefas fghsdf gafaw efsfsdgdfg");
	for (int i = 0; i <= 20; i++) {
		_console->PrintLine("Test line " + mSdlInterface->NumberToString(i));
	}
	_console->PrintLine("Salut, ca va, je viens de terminer les premiers tests de word wrapping dans le tout nouveau log de texte que j'ai fait. Note: j'ai remarque (<-justement) que les accents ne fonctionne pas :/");

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

		}

	}

	//mGraphic->DrawLine(100, 100, 40, 40, 1, 1, 1, 1, 3, false);

	/*
	 * FIN TEST ZONE
	 ***************************************************************************/

	/*****
	 * Graphical User Interface Rendering
	 */
	mGuiContainer->Draw();

}

void GetRandomGame::testFunction(int xMod, int yMod) {
	testx += xMod;
	testy += yMod;
	Camera::getInstance()->move(-xMod, -yMod);
	_testCoordLabel->SetText(
			"(" + mSdlInterface->NumberToString(testx) + ", "
					+ mSdlInterface->NumberToString(testy) + ")");
}

void GetRandomGame::Close() {
	cout << "GetRandomGame::close()" << endl;
}
