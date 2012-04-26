/*
 * GButton.cpp
 *
 *  Created on: 2012-02-29
 *      Author: Emile
 */

#include "GButton.h"
#include <string>

// TODO finish the GButton

namespace TileEngine {

GButton::GButton() {
	Init();
}

GButton::~GButton() {
}

void GButton::Init() {
	GItem::Init();
	mLabel = NULL;
	mBackground = NULL;
}

void GButton::Update() {
}

void GButton::Draw(int x, int y) {
}

} /* namespace TileEngine */
