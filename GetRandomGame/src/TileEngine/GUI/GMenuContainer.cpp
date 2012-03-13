/*
 * GMenuContainer.cpp
 *
 *  Created on: 2012-02-29
 *      Author: Emile
 */

#include "GMenuContainer.h"
#include <string>

namespace TileEngine {

GMenuContainer::GMenuContainer() {
	// TODO Auto-generated constructor stub

}

GMenuContainer::~GMenuContainer() {
	// TODO Auto-generated destructor stub
}

void GMenuContainer::Update() {
	for (unsigned int i = 0; i < mActiveMenuList.size(); i++) {
		mActiveMenuList.at(i)->Update();
	}

}

void GMenuContainer::Draw() {
	for (unsigned int i = 0; i < mActiveMenuList.size(); i++) {
		mActiveMenuList.at(i)->Draw(0, 0);
	}

}

/**
 * @param menuItem pointer to a menu Item
 *
 * Add a menu item in the update/draw list
 *
 */
void GMenuContainer::PushMenu(GMenuItem* menuItem) {
	if (menuItem != NULL) {
		mActiveMenuList.push_back(menuItem);
	}
}

} /* namespace TileEngine */
