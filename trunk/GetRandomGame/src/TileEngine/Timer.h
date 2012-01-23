/*
 * Timer.h
 *
 *  Created on: 2011-12-17
 *      Author: Emile
 */

#ifndef TIMER_H_
#define TIMER_H_

class Timer {
private:
	//Le temps quand le timer est lancé
	Uint32 startTicks;

	//Le temps enregistré quand le Timer a été mis en pause
	Uint32 pausedTicks;

	//Le status du Timer
	bool paused;
	bool started;

public:
	//Initialise les variables
	Timer();
	virtual ~Timer();

	//Les différentes actions du timer
	void start();
	void stop();
	void pause();
	void unpause();

	//recupére le nombre de millisecondes depuis que le timer a été lancé
	//ou récupére le nombre de millisecondes depuis que le timer a été mis en pause
	Uint32 get_ticks();

	//Fonctions de vérification du status du timer
	bool is_started();
	bool is_paused();
};

#endif /* TIMER_H_ */
