/*
 * TileEngine.cpp
 *
 *  Created on: 2011-12-26
 *      Author: Emile
 */

#include "Engine.h"
#include <iostream>

using namespace std;

namespace TileEngine {

int frameCount = 0; // test global frame counter
Timer initTimer;

/****************************************
 * CONSTRUTOR
 */
Engine::Engine() {
	cout << "new TileEngine" << endl;

	if (DEBUG) {
		initTimer.Start();
	}

	mFrameCnt = 0; // start the frame counter
	mFps = 0;

	// default resolution
	mScreenWidth = 640;
	mScreenHeight = 480;

	mIsInit = false;
	mIsExit = false;
	printf("sizeof int: %d\n", sizeof(int));
	cout << "new TileEngine::End" << endl;
}

/****************************************
 * init(...)
 *  Call that first, then call start();
 *
 */
void Engine::Init(int screenW, int screenH, string caption, Environment * environment, InputHandler * inputHandler) {
	cout << "Engine init" << endl;

	mEnvironment = environment;
	mInputHandler = inputHandler;

	// set the custom resolution
	mScreenWidth = screenW;
	mScreenHeight = screenH;

	mFrameCnt = 0; // start the frame counter
	mIsExit = false;

	mGraphic = Graphic::getInstance();
	mGraphic->Initialize(mScreenWidth, mScreenHeight, SCREEN_BPP, caption);

	mEnvironment->Init(mScreenWidth, mScreenHeight);

	mIsInit = true;


	cout << "Engine init::End" << endl;
}

/****************************************
 * start()
 *  It literally starts the engine
 *
 */
void Engine::Start() {
	cout << "Engine start" << endl;
	if (mIsInit) {
		Run(); //start the game loop
	}
	cout << "Engine start::End" << endl;
}

/****************************************
 * run()
 *  its the actual game loop
 *
 */
void Engine::Run() {
	cout << "Engine run" << endl;
	if (DEBUG) {
		mFpsTimer.Start();
		printf("Time taken for init: %d ms\n", initTimer.GetTimerTicks());
		initTimer.Stop();
	}

	/**
	 *  GAME LOOP
	 */
	while (!mIsExit) {
		/**
		 * each iteration, do this:
		 */

		mFrameTimer.Start(); //Calcul le temps d'execution de l'iteration

		// Collect and handle inputs informations (return false on exit)
		mIsExit = mInputHandler->HandleInput(mEnvironment);

		mEnvironment->Update(); // UPDATE the environment

		if (DEBUG) {
			FpsRegulator(); // show FPS information
		}

		mGraphic->ClearScreen(); // clear the screen

		// all the draw OPs
		mEnvironment->Draw();

		mGraphic->FlipBuffers(); // flip the screen

		// wait the time left after the last loop (timeLeft = timeEachLoop - timeTakenThisLoop)
		while (mFrameTimer.GetTimerTicks() < 1000 / FRAMES_PER_SECOND)
			;
		frameCount++; // test frame count
	} // End of the GAME LOOP

	// Stop the program correctly
	Stop();

	cout << "Engine run::End" << endl;
}

/****************************************
 * fpsRegulator
 * 	show the fps
 *
 */
void Engine::FpsRegulator() {
	//printf("SDL_getTicks: %10d\n", SDL_GetTicks());
	//printf("fpsRegulator(_frame: %d, _fps: %d)\n", _frame, _fps);
	mFrameCnt++; // incremente à chaque frame


	//Si une seconde est passee depuis la derniere mise à jour de la barre caption
	if (mFpsTimer.GetTimerTicks() > 1000) {
		mFps = mFrameCnt; // get the current fps

		mFrameCnt = -1; // reset the frame counter

		mFpsTimer.Start(); // restart the timer for each second

		// Render the FPS as the window title
		mGraphic->SetCaption("FPS: " + mSdl->IntToString(mFps));

		printf("%6d Frames, %10d ms, %5d fps;\n", frameCount, mEnvironment->getTime(), mFps);
	}
	//printf("fpsRegulator END\n");
}

/****************************************
 *
 *
 */
void Engine::Stop() {
	cout << "Engine::stop()" << endl;
	mEnvironment->Close();
	mGraphic->Shutdown();
	mGraphic->kill();
	Manager<Texture>::getInstance()->DeleteAllRessource();
	Manager<Texture>::getInstance()->kill();
	cout << "Engine::stop()::END" << endl;
}

}
