/*
 * GLabel.h
 *
 *  Created on: 2012-02-29
 *      Author: Emile
 */

#ifndef GLABEL_H_
#define GLABEL_H_

#include "GMenuItem.h"
#include "Graphic/Font.h"
#include "Graphic/GraphicType.h"
#include <string>

namespace TileEngine {

/*
 *
 */
class GLabel: public GMenuItem {
public:
	GLabel();
	GLabel(std::string text, std::string fontFileName);
	virtual ~GLabel();

	virtual void Init();
	virtual void Update();
	virtual void Draw(int x, int y);

	virtual void SetFont(std::string);
	virtual void SetFont(Font* font) {
		mFont = font;
	}

	virtual void SetText(std::string text = "") {
		mText = text;
	}

	virtual void SetColor(Color3f* color) {
		mColor = color;
	}

	virtual void SetColor(int r = 255, int g = 255, int b = 255);

	virtual void SetAlpha(int alpha = 255);

	virtual bool MouseHover(int x, int y){
		return false;
	}
	virtual bool MouseClick(int x, int y){
		return false;
	}
	virtual bool MousePressed(int x, int y){
		return false;
	}
	virtual bool MouseReleased(int x, int y){
		return false;
	}

protected:
	Font* mFont;
	std::string mText;
	Color3f* mColor;
	GLfloat mAlpha;
	int mPointSize;
};

} /* namespace TileEngine */
#endif /* GLABEL_H_ */
