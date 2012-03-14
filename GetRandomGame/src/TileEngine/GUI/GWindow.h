/*
 * GMenu.h
 *
 *  Created on: 2012-02-27
 *      Author: Emile
 *
 *      A typical menu, add to it some button and label
 */

#ifndef GMENU_H_
#define GMENU_H_

#include "Graphic/Sprite.h" // for background image and other stuff;
#include "GItem.h"

namespace TileEngine {

/*
 *
 */
class GWindow : public GItem{
public:
	GWindow();
	GWindow(Sprite* sprite);
	virtual ~GWindow();

	virtual void Init();
	virtual void Update();
	virtual void Draw(int x = 0, int y = 0);

	//virtual bool MouseClick(int x, int y);
	//virtual bool MouseHover(int x, int y);
protected:
	Sprite * mBackground;
};

} /* namespace TileEngine */
#endif /* GMENU_H_ */
