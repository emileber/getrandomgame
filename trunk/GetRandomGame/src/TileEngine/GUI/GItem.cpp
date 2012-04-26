/*
 * GMenuItem.cpp
 *
 *  Created on: 2012-02-27
 *      Author: Emile
 */

#include "GItem.h"
#include <string>

namespace TileEngine {

void GItem::Init() {
	mXoffset = 0;
	mYoffset = 0;
	mWidth = 0;
	mHeight = 0;
	mIsActive = true;
	mIsStatic = true;
	mAlpha = 1.0f;

}

void GItem::Alpha(float alpha) {
	float changedRatio = alpha / mAlpha;
	mAlpha = alpha;
	for (unsigned int i = 0; i < mItemVector.size(); i++) {
		mItemVector.at(i)->Alpha(changedRatio * mItemVector.at(i)->Alpha());
	}
}

void GItem::Update() {
	for (unsigned int i = 0; i < mItemVector.size(); i++) {
		mItemVector.at(i)->Update();
	}

}

void GItem::Draw(int x, int y) {
	if (mIsActive) {
		for (unsigned int i = 0; i < mItemVector.size(); i++) {
			mItemVector.at(i)->Draw(mXoffset + x, mYoffset + y);
		}
	}
}

/**
 * @param menuItem pointer to a menu Item
 *
 * Add a menu item in the update/draw list
 *
 */
void GItem::PushItem(GItem *menuItem) {
	if (menuItem != NULL) {
		mItemVector.push_back(menuItem);
	}
}

} /* namespace TileEngine */
