/*
 * GMenuItem.h
 *
 *  Created on: 2012-02-27
 *      Author: Emile
 */

#ifndef GMENUITEM_H_
#define GMENUITEM_H_

#include "IClickable.h"

#include <vector>
namespace TileEngine {

/*
 *
 */
class GMenuItem: public IClickable {
public:
	GMenuItem() {
	}
	virtual ~GMenuItem();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw(int x = 0, int y = 0) = 0;

	virtual bool MouseHover(int x, int y) = 0;
	virtual bool MouseClick(int x, int y) = 0;
	virtual bool MousePressed(int x, int y) = 0;
	virtual bool MouseReleased(int x, int y) = 0;

	virtual void PushMenuItem(GMenuItem*);

	/**
	 * ACCESSOR
	 *
	 */
	virtual int X() const {
		return mXoffset;
	}
	virtual void X(int x) {
		mXoffset = x;
	}
	virtual int Y() const {
		return mYoffset;
	}
	virtual void Y(int y) {
		mYoffset = y;
	}

	virtual int Width() const {
		return mWidth;
	}
	virtual void Width(int w) {
		mWidth = w;
	}

	virtual int Height() const {
		return mHeight;
	}
	virtual void Height(int h) {
		mHeight = h;
	}

	virtual void Toggle() {
		mIsActive = !mIsActive;
	}

	virtual void IsStatic(bool isStatic) {
		mIsStatic = isStatic;
	}

	virtual bool IsStatic() const {
		return mIsStatic;
	}
protected:
	int mXoffset;
	int mYoffset;
	int mWidth;
	int mHeight;
	std::vector<GMenuItem*> mMenuItemList;
	bool mIsActive;
	bool mIsStatic;

};

} /* namespace TileEngine */
#endif /* GMENUITEM_H_ */
