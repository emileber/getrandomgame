/*
 * Timer.cpp
 *
 *  Created on: 2011-12-17
 *      Author: Emile
 */

#include <iostream>
#include <sstream>
#include <string>

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

/**
 * formatTime
 *  return a readable time format string from a milisec value
 */
std::string Timer::FormatTime(uint32_t total) {
	// Render the FPS on screen
	uint32_t minute = abs(total / 60000);
	uint32_t second = abs((total % 60000) / 1000);
	uint32_t milisec = abs((total % 60000) - (second * 1000));

	return NumberToString(minute) + ":" + NumberToString(second) + "."
			+ NumberToString(milisec);
	//string timeString = "Time: " + intToString(total);
	//_sdl->renderText(10, 20, 3, timeString, 200);
}

} // end of namespace
