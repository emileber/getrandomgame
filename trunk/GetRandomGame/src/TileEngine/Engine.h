/*
 * TileEngine.h
 *
 *  Created on: 2011-12-26
 *      Author: Emile
 *
 *      Generic Game loop and program flow controller.
 *
 *      To use:
 *      Init(width, height, caption, YourEnvironmentSubClass, YourInputHandlerSubClass);
 *
 *      // when you are ready:
 *      Start();
 *
 */

#ifndef TILEENGINE_H_
#define TILEENGINE_H_

#include "Singleton.h"
#include "SdlInterface.h"
#include "Environment.h"
#include "InputHandler.h"
#include "Global.h"
#include "Graphic/Graphic.h"
#include "Timer.h"

namespace TileEngine {

class Engine: public Singleton<Engine> {
	friend class Singleton<Engine> ;
protected:
	Engine();

	SdlInterface * mSdl;
	Graphic * mGraphic;
	Environment * mEnvironment;
	InputHandler * mInputHandler;
	Timer mFrameTimer; // used to calculate the time taken each game loop
	Timer mFpsTimer; // used to calculate the FPS of the game
	int mFrameCnt, mFps, mScreenWidth, mScreenHeight;
	bool mIsExit, mIsInit;

	void Run();
	void FpsRegulator();

public:
	void Init(int, int, std::string, Environment *, InputHandler *);
	void Start();
	void Stop();

};
}
#endif /* TILEENGINE_H_ */
