/*
 * GameUI.cpp
 *
 *  Created on: 2012-03-13
 *      Author: Emile
 */

#include "GameUI.h"
#include "GUI/GLabel.h"
#include "Graphic/Graphic.h"

GameUI::GameUI() {
	Init(); // init itself

}

GameUI::~GameUI() {
	// TODO Auto-generated destructor stub
}

void GameUI::Init() {
	//Graphic* pGraphic = Graphic::getInstance();
	//_testLabel = new GLabel("Bayvania Crossing", "font/Ellianarelle_Path.ttf");
	//_testLabel = new GLabel("Bayvania Crossing", "font/CaslonBold.ttf");
	GLabel * _testLabel = new GLabel("Bayvania Crossing",
			"font/Jellyka_Delicious_Cake.ttf");
	//_testLabel->SetSize(17);
	_testLabel->SetColor(255, 255, 255);
	_testLabel->IsStatic(false);
	_testLabel->SetFontSize(100);
	_testLabel->X(Graphic::getInstance()->GetWidth() - _testLabel->Width());
	_testLabel->Y(Graphic::getInstance()->GetHeight() - _testLabel->Height());
	//PushMenu(_testLabel);

}

