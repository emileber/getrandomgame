/*
 * GetRandomGame.h
 *
 *  Created on: 2012-01-03
 *      Author: Emile
 *
 *      Sub-class of Environment, it serves as
 *      the game specific environement.
 *
 */

#ifndef GETRANDOMGAME_H_
#define GETRANDOMGAME_H_

#include "Environment.h"

using namespace TileEngine;



class GetRandomGame: public Environment {

public:
	GetRandomGame();
	virtual ~GetRandomGame(){}
	virtual void Update(); // MUST be implement
	virtual void Draw(); // MUST be implement
	virtual void Close(); // MUST be implement
	virtual void Init(int, int);
	void testFunction(int,int);

};

#endif /* GETRANDOMGAME_H_ */
