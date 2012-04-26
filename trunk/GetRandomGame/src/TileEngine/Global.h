/*
 * Enumeration.h
 *
 *  Created on: 2012-01-11
 *      Author: Emile
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "SDL/SDL.h"
#include "SDL_image.h"
//#include "SDL/SDL_mixer.h" (to be implemented)
//#include "SDL/SDL_ttf.h" (deprecated) no more included
#include "SDL/SDL_video.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#define uint unsigned int

/**
 * CONSTANTS
 */
const bool DEBUG = true;
const int SCREEN_BPP = 32; // (bit per pixel)
const int FRAMES_PER_SECOND = 999; // Le nombre de frames par seconde
const int MOVE_TIME = 12;
const int MOVE_DISTANCE = 3;

const int DEFAULT_FONT_SIZE = 15;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

const int FULL_SCREEN_WIDTH = 1366;
const int FULL_SCREEN_HEIGHT = 768;

/**********************************
 * TEST ZONE
 */

/**
 * FIN DE LA TEST ZONE
 *********************************/

#endif /* GLOBAL_H_ */
