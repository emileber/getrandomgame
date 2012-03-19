/*
 * SDLInterface.h
 *
 *  Created on: 2011-12-26
 *      Author: Emile
 */

#ifndef SDLINTERFACE_H_
#define SDLINTERFACE_H_

#include "Global.h"
#include <iostream>
#include <sstream>

namespace TileEngine {

class SdlInterface: public Singleton<SdlInterface> {
	friend class Singleton<SdlInterface> ;
private:
	SdlInterface();
	//~SDLInterface();

	SDL_Color _transColor;

public:
	//bool init(int, int, int, std::string, int = 1);
	SDL_Surface * LoadImage(std::string);
	//SDL_Surface * CreateTextSurface(TTF_Font * font, std::string text, uint r,
	//		uint g, uint b);
	SDL_Surface* CreateSurface(int, int, SDL_Surface* = NULL);

	void SetTransparentColor(int, int, int);

	/**
	 * NumberToString
	 *  cast any Number base type to string...
	 */
	template<typename T>
	std::string NumberToString(T number) {
		std::stringstream ss; //create a stringstream
		ss << number; //add number to the stream
		return ss.str(); //return a string with the contents of the stream
	}
	std::string FormatTime(Uint32); // format milisec in a readable time format
};

/**
 * intToString
 *  cast int to string...
 */
//template<typename T>
//string SdlInterface::NumberToString(T number) {
//	stringstream ss; //create a stringstream
//	ss << number; //add number to the stream
//	return ss.str(); //return a string with the contents of the stream
//}

}
#endif /* SDLINTERFACE_H_ */
