/*
 * GMenuContainer.h
 *
 *  Created on: 2012-02-29
 *      Author: Emile
 *
 *      This is a generic menu container, you must redefine
 *      it in order to use the menu fonctionnality properly.
 *
 *      Add come GMenu to it.
 */

#ifndef GMENUCONTAINER_H_
#define GMENUCONTAINER_H_

#include "GItem.h"
#include <list>

namespace TileEngine {

/*
 *
 */
class GuiContainer {
public:
	GuiContainer();
	virtual ~GuiContainer();

	virtual void Init() = 0;
	virtual void Update();
	virtual void Draw();

	virtual void PushMenu(GItem *);

protected:

	std::list<GItem*> mItemList;

};

} /* namespace TileEngine */
#endif /* GMENUCONTAINER_H_ */
