/*
 * IClickable.h
 *
 *  Created on: 2012-02-27
 *      Author: Emile
 */

#ifndef ICLICKABLE_H_
#define ICLICKABLE_H_

/*
 *
 */
class IClickable {
public:
	virtual ~IClickable(){

	}
	virtual bool MouseHover(int x, int y) = 0;
	virtual bool MouseClick(int x, int y) = 0;
	virtual bool MousePressed(int x, int y) = 0;
	virtual bool MouseReleased(int x, int y) = 0;

};

#endif /* ICLICKABLE_H_ */
