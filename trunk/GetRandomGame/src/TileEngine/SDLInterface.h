/*
 * SDLInterface.h
 *
 *  Created on: 2011-12-26
 *      Author: Emile
 */

#ifndef SDLINTERFACE_H_
#define SDLINTERFACE_H_

#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_video.h"
//#include "SDL/sprig.h"
#include "Singleton.h"

class SDLInterface: public Singleton<SDLInterface> {
	friend class Singleton<SDLInterface> ;
private:
	SDLInterface();
	//~SDLInterface();
	SDL_Surface * _screen;
	TTF_Font * _font;
	int _fontSize;
	SDL_Color _fontColor;
	SDL_Color _transColor;

public:
	bool init(int w, int h, int bpp, std::string);

	bool setFont(std::string, int);
	void setTextColor(Uint8, Uint8, Uint8);
	void setTransparentColor(int,int,int);
	void apply_surface(int, int, SDL_Surface*, int = 255, SDL_Surface* = NULL, SDL_Rect* = NULL);

	bool renderText(int, int, std::string, int = 255, SDL_Surface * = NULL, SDL_Rect * = NULL);

	SDL_Surface * load_image(std::string filename);
	void render();
	void cleanUp();
};

#endif /* SDLINTERFACE_H_ */
