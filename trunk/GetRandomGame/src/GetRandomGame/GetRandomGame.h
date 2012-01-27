/*
 * GetRandomGame.h
 *
 *  Created on: 2012-01-03
 *      Author: Emile
 */

#ifndef GETRANDOMGAME_H_
#define GETRANDOMGAME_H_

#include "Environment.h"
#include "Enumeration.h"

class GetRandomGame: public Environment {

public:
	GetRandomGame();
	virtual ~GetRandomGame(){}
	virtual void update();
	virtual void close();
	virtual void init(int, int);
	void testFunction(int,int);

};

#endif /* GETRANDOMGAME_H_ */