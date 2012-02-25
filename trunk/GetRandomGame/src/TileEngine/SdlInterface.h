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

class SdlInterface: public Singleton<SdlInterface> {
	friend class Singleton<SdlInterface> ;
private:
	SdlInterface();
	//~SDLInterface();

	SDL_Color _transColor;

public:
	//bool init(int, int, int, std::string, int = 1);
	SDL_Surface * LoadImage(std::string);
	SDL_Surface * CreateTextSurface(TTF_Font * font, std::string text, uint r, uint g, uint b);
	SDL_Surface* CreateSurface(int, int, SDL_Surface* = NULL);

	void SetTransparentColor(int, int, int);

	std::string IntToString(Uint32);
	std::string FormatTime(Uint32); // format milisec in a readable time format
};

}
#endif /* SDLINTERFACE_H_ */
