/*
 * Enumeration.h
 *
 *  Created on: 2012-01-11
 *      Author: Emile
 */
 

#ifndef ENUMERATION_H_
#define ENUMERATION_H_

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

//#define

#endif /* ENUMERATION_H_ */
