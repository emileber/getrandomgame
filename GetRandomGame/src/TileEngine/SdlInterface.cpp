/*
 * SDLInterface.cpp
 *
 *  Created on: 2011-12-26
 *      Author: Emile
 *
 *
 *      DEPRACATED, its use should be avoided at all cost!
 */

#include "SDLInterface.h"
#include <iostream>
#include <sstream>

using namespace std;

namespace TileEngine {
/**
 * CONSTRUCTOR
 *
 */
SdlInterface::SdlInterface() {
	printf("new SDLInterface\n");

	_transColor.r = 0;
	_transColor.g = 255;
	_transColor.b = 255;

	printf("new SDLInterface::End\n");
}

/**
 * intialize the SDL stuff
 *
 */
//bool SDLInterface::init(int w, int h, int bpp, string caption, int nbLayer) {
//	_screenW = w;
//	_screenH = h;
//	if (nbLayer < 1) {
//		nbLayer = 1; // force to have at least ONE layer
//	}
//	_nbLayer = nbLayer;
//
//	//initialisation de tous les sous-systemes de sdl
//	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
//		return false;
//	}
//
//	//on met en place l'ecran
//	_screen = SDL_SetVideoMode(w, h, bpp, SDL_SWSURFACE);
//
//	//Si il y a une erreur lors de la mise en place de l'ecran
//	if (_screen == NULL) {
//		return false;
//	}
//
//	// set the number of layer you'll have
//	for (int i = 0; i < _nbLayer; i++) {
//		queue<Sprite*> temp;
//		_layerQueue.push_back(temp); // init the sprite queue
//	}
//
//	//Initialisation de SDL_ttf
//	if (TTF_Init() == -1) {
//		return false;
//	}
//
//	//on met en place la barre caption de la fenetre
//	SDL_WM_SetCaption(caption.c_str(), NULL);
//
//	//si tout s'est bien passé
//	return true;
//}
/**
 * intToString
 *  cast int to string...
 */
//template <typename T>
//string SdlInterface::NumberToString(T number) {
//	stringstream ss; //create a stringstream
//	ss << number; //add number to the stream
//	return ss.str(); //return a string with the contents of the stream
//}

/**
 * formatTime
 *  return a readable time format string from a milisec value
 */
string SdlInterface::FormatTime(Uint32 total) {
	// Render the FPS on screen
	Uint32 minute = abs(total / 60000);
	Uint32 second = abs((total % 60000) / 1000);
	Uint32 milisec = abs((total % 60000) - (second * 1000));

	return NumberToString(minute) + ":" + NumberToString(second) + "."
			+ NumberToString(milisec);
	//string timeString = "Time: " + intToString(total);
	//_sdl->renderText(10, 20, 3, timeString, 200);
}

void SdlInterface::SetTransparentColor(int r, int g, int b) {
	if (abs(r) <= 255) {
		_transColor.r = abs(r);
	}
	if (abs(g) <= 255) {
		_transColor.g = abs(g);
	}
	if (abs(b) <= 255) {
		_transColor.b = abs(b);
	}
}

/**
 * Create a transparent Surface
 *
 */
//SDL_Surface * SDLInterface::createSurface(int width, int height,
//		SDL_Surface* display) {
//	if (display == NULL) {
//		display = _screen;
//	}
//	// 'display' is the surface whose format you want to match
//	//  if this is really the display format, then use the surface returned from SDL_SetVideoMode
//
//	SDL_Surface * tempSurf = NULL;
//	const SDL_PixelFormat& fmt = *(display->format);
//	tempSurf = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height,
//			fmt.BitsPerPixel, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);
//	SDL_FillRect(tempSurf, NULL, SDL_MapRGB(&fmt, 0, 255, 255));
//	SDL_SetColorKey(tempSurf, SDL_RLEACCEL | SDL_SRCCOLORKEY,
//			SDL_MapRGB(tempSurf->format, 0, 255, 255));
//	return tempSurf;
//}
/**
 * load_image
 * Load an image and return an optimized SDL_Surface version of it
 *
 */
//SDL_Surface * SdlInterface::LoadImage(string filename) {
//	//printf("SDLInterface::load_image(%s)\n", filename.c_str());
//	//L'image qui est chargée
//	SDL_Surface* loadedImage = NULL;
//
//	//L'image optimisée que nous utiliserons par la suite
//	SDL_Surface* optimizedImage = NULL;
//
//	//Chargement de l'image
//	loadedImage = IMG_Load(filename.c_str());
//	//printf("IMG_Load OK\n");
//	//Si l'image est chargée correctement
//	if (loadedImage != NULL) {
//		//printf("%s != NULL\n", filename.c_str());
//		//creation de l'image optimisée
//		optimizedImage = SDL_DisplayFormat(loadedImage);
//
//		//liberation de l'ancienne image
//		SDL_FreeSurface(loadedImage);
//
//		//si l'image optimisée créé est bonne
//		if (optimizedImage != NULL) {
//			//transparence
//			SDL_SetColorKey(
//					optimizedImage,
//					SDL_RLEACCEL | SDL_SRCCOLORKEY,
//					SDL_MapRGB(optimizedImage->format, _transColor.r,
//							_transColor.g, _transColor.b));
//		}
//	}
//	//printf("SDLInterface::load_image::END\n");
//	//on retourne l'image optimisé
//	return optimizedImage;
//}
SDL_Surface * SdlInterface::LoadImage(string filename) {
	//printf("SDLInterface::load_image(%s)\n", filename.c_str());
	//L'image qui est chargée
	SDL_Surface* loadedImage = NULL;

	//Chargement de l'image
	loadedImage = IMG_Load(filename.c_str());
	//printf("IMG_Load OK\n");
	//Si l'image est chargée correctement
	if (loadedImage != NULL) {
		//transparence
		SDL_SetColorKey(
				loadedImage,
				SDL_RLEACCEL | SDL_SRCCOLORKEY,
				SDL_MapRGB(loadedImage->format, _transColor.r, _transColor.g,
						_transColor.b));

	}
	//printf("SDLInterface::load_image::END\n");
	//on retourne l'image optimisé
	return loadedImage;
}

/**
 * createTextSurface
 * Return an SDL_Surface out of a text
 * (Deprecated) see Graphic/Font that uses FTGL for OpenGL
 */
//SDL_Surface * SdlInterface::CreateTextSurface(TTF_Font * font, string text,
//		uint r, uint g, uint b) {
//	SDL_Color fontColor = { r, g, b };
//	return TTF_RenderText_Solid(font, text.c_str(), fontColor);
//}

}
