/*
 * WorldMap.h
 *
 *  Created on: 2012-02-14
 *      Author: Emile
 */

#ifndef WORLDMAP_H_
#define WORLDMAP_H_
#include "World.h"

/*
 *
 */
class WorldMap: public TileEngine::World {
public:
	WorldMap();
	virtual ~WorldMap();
	virtual void update();
	virtual void draw();

};

#endif /* WORLDMAP_H_ */
