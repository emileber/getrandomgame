/*
 * Timer.cpp
 *
 *  Created on: 2011-12-17
 *      Author: Emile
 */
#include "SDL/SDL.h"
#include "Timer.h"

namespace TileEngine {

Timer::Timer() {
	//Initialisation des variables
	mStartTicks = 0;
	mPausedTicks = 0;
	mIsPaused = false;
	mIsStarted = false;
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void Timer::Start() {
	//On demarre le timer
	mIsStarted = true;

	//On enlève la pause du timer
	mIsPaused = false;

	//On récupére le temps courant
	mStartTicks = SDL_GetTicks();
}

void Timer::Stop() {
	//On stoppe le timer
	mIsStarted = false;

	//On enlève la pause
	mIsPaused = false;
}

uint32_t Timer::GetTimerTicks() {
	//Si le timer est en marche
	if (mIsStarted == true) {
		//Si le timer est en pause
		if (mIsPaused == true) {
			//On retourne le nombre de ticks quand le timer a été mis en pause
			return mPausedTicks;
		} else {
			//On retourne le temps courant moins le temps quand il a démarré
			return SDL_GetTicks() - mStartTicks;
		}
	}

	//Si le timer n'est pas en marche
	return 0;
}

void Timer::Pause() {
	//Si le timer est en marche et pas encore en pause
	if ((mIsStarted == true) && (mIsPaused == false)) {
		//On met en pause le timer
		mIsPaused = true;

		//On calcul le pausedTicks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
	}
}

void Timer::Unpause() {
	//Si le timer est en pause
	if (mIsPaused == true) {
		//on enlève la pause du timer
		mIsPaused = false;

		//On remet à zero le startTicks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//Remise à zero du pausedTicks
		mPausedTicks = 0;
	}
}

bool Timer::IsStarted() {
	return mIsStarted;
}

bool Timer::IsPaused() {
	return mIsPaused;
}
} // end of namespace
