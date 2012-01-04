/*
 * SDLInterface.cpp
 *
 *  Created on: 2011-12-26
 *      Author: Emile
 */

#include "SDLInterface.h"
#include <iostream>

using namespace std;

/**
 * CONSTRUCTOR
 *
 */
SDLInterface::SDLInterface() {
	cout << "new SDLInterface" << endl;
	//font variables init
	_font = NULL;
	_fontSize = 15; // default 15
	SDL_Color color = { 255, 255, 255 };
	_fontColor = color; // default white
	_transColor.r = 0;
	_transColor.g = 255;
	_transColor.b = 255;
	cout << "new SDLInterface::End" << endl;
}

/**
 * intialize the SDL stuff
 *
 */
bool SDLInterface::init(int w, int h, int bpp, string caption) {
	//initialisation de tous les sous-systemes de sdl
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		return false;
	}

	//on met en place l'ecran
	_screen = SDL_SetVideoMode(w, h, bpp, SDL_SWSURFACE);

	//Si il y a une erreur lors de la mise en place de l'ecran
	if (_screen == NULL) {
		return false;
	}

	//Initialisation de SDL_ttf
	if (TTF_Init() == -1) {
		return false;
	}

	//on met en place la barre caption de la fenetre
	SDL_WM_SetCaption(caption.c_str(), NULL);

	//si tout s'est bien passé
	return true;
}

/**
 * Set the font to use and its size
 *
 */
bool SDLInterface::setFont(string filename, int size) {
	if (_font != NULL) {
		//quitte le font utilisé
		TTF_CloseFont(_font);
	}
	//Ouverture du font
	_font = TTF_OpenFont(filename.c_str(), size);

	if (_font == NULL) {
		return false;
	}

	return true;
}

/**
 * Set the font color
 *
 */
void SDLInterface::setTextColor(Uint8 r, Uint8 g, Uint8 b) {
	_fontColor.r = r;
	_fontColor.g = g;
	_fontColor.b = b;
}

void SDLInterface::setTransparentColor(int r, int g, int b) {
	_transColor.r = r;
	_transColor.g = g;
	_transColor.b = b;
}

/**
 * Load an image and return an optimized SDL_Surface version of it
 *
 */
SDL_Surface * SDLInterface::load_image(string filename) {
	//L'image qui est chargée
	SDL_Surface* loadedImage = NULL;

	//L'image optimisée que nous utiliserons par la suite
	SDL_Surface* optimizedImage = NULL;

	//Chargement de l'image
	loadedImage = IMG_Load(filename.c_str());

	//Si l'image est chargée correctement
	if (loadedImage != NULL) {
		//creation de l'image optimisée
		optimizedImage = SDL_DisplayFormat(loadedImage);

		//liberation de l'ancienne image
		SDL_FreeSurface(loadedImage);

		//si l'image optimisée créé est bonne
		if (optimizedImage != NULL) {
			//transparence
			SDL_SetColorKey(
					optimizedImage,
					SDL_RLEACCEL | SDL_SRCCOLORKEY,
					SDL_MapRGB(optimizedImage->format, _transColor.r,
							_transColor.g, _transColor.b));
		}
	}

	//on retourne l'image optimisé
	return optimizedImage;
}

/**
 * Apply an image "source" onto an image "destination"
 * Set "destination" to Null to apply on screen by default
 */
void SDLInterface::apply_surface(int x, int y, SDL_Surface* source, int alpha,
		SDL_Surface* destination, SDL_Rect* clip) {

	if ((alpha < 0) || (alpha > 255)) {
		return;
	}

	SDL_SetAlpha(source, SDL_SRCALPHA | SDL_RLEACCEL, alpha);

	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	// apply the image on the screen by default
	if (destination == NULL) {
		destination = _screen;
	}

	//on blit la surface
	SDL_BlitSurface(source, clip, destination, &offset);
}

bool SDLInterface::renderText(int x, int y, string text,
		int alpha, SDL_Surface * destination, SDL_Rect* clip) {

	if ((alpha < 0) || (alpha > 255)) {
		return false;
	}

	// Create a temp surface with the text
	SDL_Surface * textSurface = TTF_RenderText_Solid(_font, text.c_str(),
			_fontColor);

	if (textSurface == NULL) {
		return false;
	}

	// Apply that text surface on the destination
	apply_surface(x, y, textSurface, alpha, destination, clip);

	// then free the text surface
	SDL_FreeSurface(textSurface);

	return true;
}

/**
 * Flip the screen
 *
 */
void SDLInterface::render() {
	SDL_Flip(_screen);
}

/**
 * Close all the SDL stuff
 *
 */
void SDLInterface::cleanUp() {

	//On ferme le font qu'on a utilisé
	TTF_CloseFont(_font);

	//On quitte SDL_ttf
	TTF_Quit();

	//On quitte SDL
	SDL_Quit();
}
