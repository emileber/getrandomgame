/*
 * GLabel.h
 *
 *  Created on: 2012-02-29
 *      Author: Emile
 */

#ifndef GLABEL_H_
#define GLABEL_H_

#include "GItem.h"
#include "Graphic/Font.h"
#include "Graphic/GraphicType.h"
#include <string>

namespace TileEngine {

/*
 *
 */
class GLabel: public GItem {
public:
	GLabel();
	GLabel(std::string text, std::string fontFileName);
	virtual ~GLabel();

	virtual void Init();
	virtual void Update();
	virtual void Draw(int x, int y);

	virtual void SetFont(std::string);
	virtual void SetFont(const Font* font);

	virtual const Font *GetFont() const {
		return mFont;
	}

	virtual void SetText(std::string text = "");

	virtual void SetColor(Color3f* color) {
		mColor = color;
	}

	virtual void SetColor(float r = 255, float g = 255, float b = 255);

	/**
	 * SetFontSize
	 * In pixel, right now it defines the
	 * height as well
	 *
	 */
	virtual void SetFontSize(int size) {
		mPointSize = size;
		Height(size);
		Width(mWidth * (mPointSize / mFont->GetHeight()));
	}

	virtual void IsStatic(bool isStatic) {
		GItem::IsStatic(isStatic);
		//mFont->IsStatic(isStatic);
	}

	virtual bool IsMouseIn(int x, int y) {
		return false;
	}

	virtual bool MouseHover(int x, int y) {
		return false;
	}
	virtual bool MouseClick(int x, int y) {
		return false;
	}
	virtual bool MousePressed(int x, int y) {
		return false;
	}
	virtual bool MouseReleased(int x, int y) {
		return false;
	}

protected:
	const Font* mFont;
	std::string mText;
	Color3f* mColor;
	int mPointSize;
};

} /* namespace TileEngine */
#endif /* GLABEL_H_ */
