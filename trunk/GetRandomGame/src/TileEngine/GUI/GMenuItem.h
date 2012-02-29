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
	GMenuItem();
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
	virtual int X() {
		return mXoffset;
	}
	virtual void X(int x) {
		mXoffset = x;
	}
	virtual int Y() {
		return mYoffset;
	}
	virtual void Y(int y) {
		mYoffset = y;
	}

	virtual void Toggle(){
		mIsActive = !mIsActive;
	}
protected:
	int mXoffset;
	int mYoffset;
	std::vector<GMenuItem*> mMenuItemList;
	bool mIsActive;

};

} /* namespace TileEngine */
#endif /* GMENUITEM_H_ */
