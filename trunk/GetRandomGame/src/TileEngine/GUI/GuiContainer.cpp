/*
 * GMenuContainer.cpp
 *
 *  Created on: 2012-02-29
 *      Author: Emile
 */

#include "GuiContainer.h"
#include <string>

namespace TileEngine {

GuiContainer::GuiContainer() {

}

GuiContainer::~GuiContainer() {
	// TODO Auto-generated destructor stub
}

void GuiContainer::Update() {
	for (std::list<GItem*>::iterator it = mItemList.begin();
			it != mItemList.end(); ++it) {
		if ((*it)->IsActive()) {
			(*it)->Update();
		}
	}

}

void GuiContainer::Draw() {
	for (std::list<GItem*>::iterator it = mItemList.begin();
			it != mItemList.end(); ++it) {
		// for each Item, draw if active
		if ((*it)->IsActive()) {
			(*it)->Draw(0, 0);
		}
	}

}

/**
 * @param menuItem pointer to a menu Item
 *
 * Add a menu item in the update/draw list
 *
 */
void GuiContainer::PushMenu(GItem* menuItem) {
	if (menuItem == NULL) {
		return; // prevent from adding NULL element
	}

	mItemList.push_back(menuItem);
	mItemList.unique(); // prevent double

}

} /* namespace TileEngine */
