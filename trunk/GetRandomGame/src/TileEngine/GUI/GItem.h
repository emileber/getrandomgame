/*
 * GMenuItem.h
 *
 *  Created on: 2012-02-27
 *      Author: Emile
 */

#ifndef GMENUITEM_H_
#define GMENUITEM_H_

#include <vector>

#include "IClickable.h"
//#include "Global.h"

namespace TileEngine {

/*
 *
 */
class GItem: public IClickable {
public:
	GItem() {
	}
	virtual ~GItem() {

	}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw(int x = 0, int y = 0) = 0;

	virtual void PushItem(GItem*);

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

	virtual void SetOffset(int x, int y) {
		mXoffset = x;
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

	virtual void SetSize(int w, int h) {
		mWidth = w;
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
	virtual void IsActive(bool isActive) {
		mIsActive = isActive;
	}

	virtual bool IsActive() const {
		return mIsActive;
	}

	virtual void Alpha(float alpha);
	virtual float Alpha() const {
		return mAlpha;
	}

protected:

	//virtual void InitialiseDraw();

	int mXoffset;
	int mYoffset;
	int mWidth;
	int mHeight;
	std::vector<GItem*> mItemVector;
	bool mIsActive;
	bool mIsStatic;
	float mAlpha;

};

} /* namespace TileEngine */
#endif /* GMENUITEM_H_ */
