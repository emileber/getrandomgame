/*
 * Environment.h
 *
 *  Created on: 2011-12-18
 *      Author: Emile
 *
 *      Abstract class, to handle basic game stuff.
 *      A game is in fact a defined environment.
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Manager.h"

#include "World.h"
#include "Timer.h"
#include "Graphic/Graphic.h"
#include "Graphic/Texture.h"
#include "GUI/GuiContainer.h"



namespace TileEngine {

class Environment {
public:
	Environment(); // generic constructor
	virtual ~Environment() {
	}
	virtual void Init(int, int); // generic initialization

	virtual void Update() = 0; // generic function, redefine by the subclass
	virtual void Draw() = 0; // generic function, redefine by the subclass
	virtual void Close() = 0; // generic function, redefine by the subclass

	virtual Uint32 getTime() {
		return mGameTime.GetTimerTicks();
	}

protected:

	int mScreenWidth, mScreenHeight;
	Timer mGameTime;
	Uint32 mFrameCount;

	World * mWorld;
	Graphic * mGraphic;
	Manager<Texture> * mTextureManager;
	GuiContainer* mGuiContainer;

};
}
#endif /* ENVIRONMENT_H_ */
