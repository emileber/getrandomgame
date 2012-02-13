/*
 * Enumeration.h
 *
 *  Created on: 2012-01-11
 *      Author: Emile
 */
 

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <list>
#include <map>
#include <stack>

#include "Singleton.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
//#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_video.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

/**
 * Layer enum
 *  Layers go from 0 to 11 (makes a total of 12)
 *  Somes are not define, wich let them available for future uses
 */
 enum Layer {
	 BACKGROUND_LAYER = 1,
	 GROUND_LAYER = 4,
	 PEOPLE_LAYER = 6,
	 FOREGROUND_LAYER = 8,
	 MENU_LAYER = 10,
	 DEBUG_LAYER = 11,
	 TOTAL_LAYER = 12
 };


#define uint unsigned int

 /**
  * CONSTANTS
  */
 const bool DEBUG = true;
 const int SCREEN_BPP = 32; // (bit per pixel)
 const int FRAMES_PER_SECOND = 200;  // Le nombre de frames par seconde
 const int MOVE_TIME = 12;
 const int MOVE_DISTANCE = 3;


 /**********************************
  * TEST ZONE
  */

 /**
  * FIN DE LA TEST ZONE
  *********************************/

#endif /* GLOBAL_H_ */
