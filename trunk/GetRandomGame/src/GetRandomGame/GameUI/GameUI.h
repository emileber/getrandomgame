/*
 * GameUI.h
 *
 *  Created on: 2012-03-13
 *      Author: Emile
 */

#ifndef GAMEUI_H_
#define GAMEUI_H_

#include "GUI/GuiContainer.h"



using namespace TileEngine;
/*
 *
 */
class GameUI: public GuiContainer {
public:
	GameUI();
	virtual ~GameUI();

	virtual void Init();

};

#endif /* GAMEUI_H_ */
