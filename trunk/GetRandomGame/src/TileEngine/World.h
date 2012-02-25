/*
 * World.h
 *
 *  Created on: 2011-12-18
 *      Author: Emile
 *
 *      Generic class for Game World, you should (must)
 *      redefine Update, Draw and Close
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "IApplication.h"

namespace TileEngine{

class World: public IApplication {
public:
	World();
	virtual ~World();
	virtual void Update(){

	}
	virtual void Draw(){

	}
	virtual void Close(){

	}
};

}
#endif /* WORLD_H_ */
