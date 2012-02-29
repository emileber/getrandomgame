/*
 * GMenuItem.cpp
 *
 *  Created on: 2012-02-27
 *      Author: Emile
 */

#include "GMenuItem.h"
#include <string>


namespace TileEngine {

GMenuItem::GMenuItem() {
	Init();
}

GMenuItem::~GMenuItem() {
	// TODO Auto-generated destructor stub
}

void GMenuItem::Init() {
	mXoffset = 0;
	mYoffset = 0;
	mIsActive = true;

}

void GMenuItem::Update() {
	for (unsigned int i = 0; i < mMenuItemList.size(); i++) {
		mMenuItemList.at(i)->Update();
	}

}

void GMenuItem::Draw(int x, int y) {
	if (mIsActive) {
		for (unsigned int i = 0; i < mMenuItemList.size(); i++) {
			mMenuItemList.at(i)->Draw(mXoffset + x, mYoffset + y);
		}
	}
}

/**
 * @param menuItem pointer to a menu Item
 *
 * Add a menu item in the update/draw list
 *
 */
void GMenuItem::PushMenuItem(GMenuItem *menuItem) {
	if (menuItem != NULL) {
		mMenuItemList.push_back(menuItem);
	}
}

} /* namespace TileEngine */
