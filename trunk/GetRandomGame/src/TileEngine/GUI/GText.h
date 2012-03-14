/*
 * GText.h
 *
 *  Created on: 2012-03-14
 *      Author: Emile
 *
 *      Define a GTextLine as a list of
 *      GWord for a fixed total width.
 */

#ifndef GTEXT_H_
#define GTEXT_H_

#include <vector>
#include <string>
#include "Graphic/GraphicType.h"
#include "Graphic/Font.h"

namespace TileEngine {

class GWord {
public:
	GWord() {
		mWord = "";
		mColor = new Color3f(1, 1, 1);
		mWidth = 0;
	}

	GWord(std::string word, int w, Color3f * color) {
		mWord = word;
		mWidth = w;
		mColor = color;
	}

	virtual ~GWord() {

	}

	virtual int Width() const {
		return mWidth;
	}

	virtual void Draw(const Font* font, GLfloat x, GLfloat y, GLfloat scale, GLfloat alpha = 1.0f) const;
protected:
	std::string mWord;
	int mWidth;
	Color3f * mColor;

};

/*
 *
 */
class GTextLine {
public:
	GTextLine();
	virtual ~GTextLine();

	virtual int GetWordCount() const {
		return mTextLine.size();
	}

	virtual int Width() const {
		return mWidth;
	}

	virtual void PushWord(const GWord * word, int width);

	virtual void Draw(const Font* font, GLfloat x, GLfloat y, GLfloat scale, GLfloat alpha = 1.0f) const;

protected:
	std::vector<const GWord*> mTextLine;
	int mWidth;
};

} /* namespace TileEngine */
#endif /* GTEXT_H_ */
