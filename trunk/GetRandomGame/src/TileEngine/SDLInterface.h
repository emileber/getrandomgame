/*
 * SDLInterface.h
 *
 *  Created on: 2011-12-26
 *      Author: Emile
 */

#ifndef SDLINTERFACE_H_
#define SDLINTERFACE_H_

#include "Sprite.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_video.h"
//#include "SDL/sprig.h"
#include "Singleton.h"
#include <string>
#include <queue>
#include <vector>

class SDLInterface: public Singleton<SDLInterface> {
	friend class Singleton<SDLInterface> ;
private:
	SDLInterface();
	//~SDLInterface();
	SDL_Surface * _screen;
	std::vector<std::queue<Sprite *> > _layer;
	TTF_Font * _font;
	int _fontSize, _nbLayer;
	SDL_Color _fontColor;
	SDL_Color _transColor;

public:
	bool init(int, int, int, std::string, int = 1);
	SDL_Surface * load_image(std::string);
	SDL_Surface * createTextSurface(std::string);
	SDL_Surface* createSurface(int, int, SDL_Surface*);

	bool setFont(std::string, int);
	void setTextColor(Uint8, Uint8, Uint8);
	void setTransparentColor(int, int, int);

	void pushSprite(Sprite *, int = 0);
	void apply_surface(int, int, SDL_Surface*, int = 255, SDL_Rect* = NULL);
	bool renderText(int, int, std::string, int = 255, SDL_Rect * = NULL);

	void render();
	void cleanUp();
};

#endif /* SDLINTERFACE_H_ */
