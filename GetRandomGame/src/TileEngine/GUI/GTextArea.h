/*
 * GTextArea.h
 *
 *  Created on: 2012-03-13
 *      Author: Emile
 */

#ifndef GTEXTAREA_H_
#define GTEXTAREA_H_

#include "GItem.h"
#include "Graphic/Font.h"
#include "Graphic/GraphicType.h"
#include "GText.h"
#include <vector>

namespace TileEngine {

/*
 *
 */
class GTextArea: public GItem {
public:
	GTextArea();
	virtual ~GTextArea();

	virtual void Init();
	virtual void Update();
	virtual void Draw(int x, int y);

	virtual void SetFont(std::string);
	virtual void SetFont(const Font* font);

	virtual const Font *GetFont() const {
		return mFont;
	}

//	virtual void IsStatic(bool isStatic) {
//		GItem::IsStatic(isStatic);
//		//mFont->IsStatic(isStatic);
//	}

	/**
	 * SetFontSize
	 * In pixel, right now it defines the
	 * height as well
	 *
	 */
	virtual void SetFontSize(int size) {
		mPointSize = size;
		Height(size);
	}

	virtual void PrintLine() {

	}
	virtual void PrintLine(std::string text, Color3f *color = NULL);
	//virtual void AppendLine(std::string text, Color3f *color = NULL);

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

private:
	const Font* mFont;
	std::vector<GTextLine*> mTextVector;
	GTextLine* mCurrentLine;
	Color3f *mColorDefault;
	int mSpaceWidth;
	int mPointSize;

};

} /* namespace TileEngine */
#endif /* GTEXTAREA_H_ */
