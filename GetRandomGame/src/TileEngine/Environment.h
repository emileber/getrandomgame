/*
 * Environment.h
 *
 *  Created on: 2011-12-18
 *      Author: Emile
 *
 *      Abstract class, to handle basic game stuff.
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "World.h"
//#include "Singleton.h"
#include "SdlInterface.h"
#include "Timer.h"
#include "Graphic.h"
#include "Texture.h"
#include "Global.h"
#include "IApplication.h"

namespace TileEngine {

class Environment: public IApplication {
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

	World * mWorld;
	SdlInterface * mSdlInterface;
	Graphic * mGraphic;
	Manager<Texture> * mTextureManager;
	Timer mGameTime;
	int mScreenWidth, mScreenHeight;
	Uint32 mFrameCount;

};
}
#endif /* ENVIRONMENT_H_ */
