/*
 * Menu.cpp
 *
 *  Created on: 2012-02-27
 *      Author: Emile
 */

#include "GMenu.h"

namespace TileEngine {

GMenu::GMenu() {
	// TODO Auto-generated constructor stub

}
GMenu::GMenu(Sprite* sprite) {
	if (sprite != NULL) {
		mBackground = sprite;
	}
}
GMenu::~GMenu() {
	// TODO Auto-generated destructor stub
}

void GMenu::Init(){
	GMenuItem::Init();
}

void GMenu::Update() {
	GMenuItem::Update();
}

void GMenu::Draw(int x, int y) {
	mBackground->Draw(mXoffset + x, mYoffset + y);

	for (unsigned int i = 0; i < mMenuItemList.size(); i++) {
		mMenuItemList.at(i)->Draw(mXoffset + x, mYoffset + y);
	}

}

} /* namespace TileEngine */
