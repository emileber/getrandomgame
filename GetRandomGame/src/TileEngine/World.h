/*
 * World.h
 *
 *  Created on: 2011-12-18
 *      Author: Emile
 */

#ifndef WORLD_H_
#define WORLD_H_

namespace TileEngine{

class World {
public:
	World();
	virtual ~World();
	virtual void update(){

	}
	virtual void draw(){

	}
};

}
#endif /* WORLD_H_ */
