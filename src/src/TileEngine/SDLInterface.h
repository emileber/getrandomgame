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

public:
	bool init(int w, int h, int bpp, std::string);

	bool setFont(std::string, int);
	void setTextColor(Uint8, Uint8, Uint8);
	void apply_surface(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect*);

	bool renderText(int, int, std::string, SDL_Surface*, SDL_Rect*);

	SDL_Surface * load_image(std::string filename);
	void render();
	void cleanUp();
};

#endif /* SDLINTERFACE_H_ */
