/*
 * Menu.cpp
 *
 *  Created on: 2012-02-27
 *      Author: Emile
 */

// TODO finis GWindow cpp

#include <set>

#include "GWindow.h"


namespace TileEngine {

GWindow::GWindow() {

}
GWindow::GWindow(Sprite* sprite) {
	if (sprite != NULL) {
		mBackground = sprite;
	}
}
GWindow::~GWindow() {
}

void GWindow::Init() {
	GItem::Init();
}

void GWindow::Update() {
	GItem::Update();
}

void GWindow::Draw(int x, int y) {
	mBackground->Draw(mXoffset + x, mYoffset + y);

	GItem::Draw(mXoffset + x, mYoffset + y);

}

} /* namespace TileEngine */
