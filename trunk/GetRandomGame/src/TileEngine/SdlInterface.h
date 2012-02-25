/*
 * SDLInterface.h
 *
 *  Created on: 2011-12-26
 *      Author: Emile
 */

#ifndef SDLINTERFACE_H_
#define SDLINTERFACE_H_

#include "Global.h"

namespace TileEngine {

class SDLInterface: public Singleton<SDLInterface> {
	friend class Singleton<SDLInterface> ;
private:
	SDLInterface();
	//~SDLInterface();

	SDL_Color _transColor;

public:
	//bool init(int, int, int, std::string, int = 1);
	SDL_Surface * load_image(std::string);
	SDL_Surface * createTextSurface(TTF_Font * font, std::string text, uint r, uint g, uint b);
	SDL_Surface* createSurface(int, int, SDL_Surface* = NULL);

	void setTransparentColor(int, int, int);

	std::string intToString(Uint32);
	std::string formatTime(Uint32); // format milisec in a readable time format
};

}
#endif /* SDLINTERFACE_H_ */
