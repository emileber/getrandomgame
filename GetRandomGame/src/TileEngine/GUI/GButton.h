/*
 * GButton.h
 *
 *  Created on: 2012-02-29
 *      Author: Emile
 */

#ifndef GBUTTON_H_
#define GBUTTON_H_

#include "GMenuItem.h"
#include "GLabel.h"
#include "Graphic/Sprite.h"

namespace TileEngine {

/*
 *
 */
class GButton: public GMenuItem {
public:
	GButton();
	virtual ~GButton();

	virtual void Init();
	virtual void Update();
	virtual void Draw(int,int);

protected:
	GLabel* mLabel;
	Sprite* mBackground;

};

} /* namespace TileEngine */
#endif /* GBUTTON_H_ */
