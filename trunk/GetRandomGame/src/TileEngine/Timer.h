/*
 * Timer.h
 *
 *  Created on: 2011-12-17
 *      Author: Emile
 *
 *      calculate the time in milisec using
 *      SDL_GetTicks();
 *
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "SDL/SDL.h"

namespace TileEngine {

class Timer {

public:
	//Initialise les variables
	Timer();
	virtual ~Timer();

	//Les différentes actions du timer
	void Start();
	void Stop();
	void Pause();
	void Unpause();

	//recupére le nombre de millisecondes depuis que le timer a été lancé
	//ou récupére le nombre de millisecondes depuis que le timer a été mis en pause
	uint32_t GetTimerTicks();

	//Fonctions de vérification du status du timer
	bool IsStarted();
	bool IsPaused();

private:
	//Le temps quand le timer est lancé
	uint32_t mStartTicks;

	//Le temps enregistré quand le Timer a été mis en pause
	uint32_t mPausedTicks;

	//Le status du Timer
	bool mIsPaused;
	bool mIsStarted;
};

} // end of namespace

#endif /* TIMER_H_ */
