/*
 * Menu.cpp
 *
 *  Created on: 2012-02-27
 *      Author: Emile
 */

#include "GWindow.h"
#include <set>

namespace TileEngine {

GWindow::GWindow() {
	// TODO Auto-generated constructor stub

}
GWindow::GWindow(Sprite* sprite) {
	if (sprite != NULL) {
		mBackground = sprite;
	}
}
GWindow::~GWindow() {
	// TODO Auto-generated destructor stub
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
