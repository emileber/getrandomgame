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

#include "GMenuItem.h"

namespace TileEngine {

/*
 *
 */
class GMenuContainer {
public:
	GMenuContainer();
	virtual ~GMenuContainer();

	virtual void Init() = 0;
	virtual void Update();
	virtual void Draw();

	virtual void PushMenu(GMenuItem *);

protected:
	std::vector<GMenuItem*> mMenuList;
};

} /* namespace TileEngine */
#endif /* GMENUCONTAINER_H_ */
