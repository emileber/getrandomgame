/*
 * SDLInterface.cpp
 *
 *  Created on: 2011-12-26
 *      Author: Emile
 */

#include "SDLInterface.h"
#include "Enumeration.h"
#include <cstdio>
#include <iostream>

using namespace std;

/**
 * CONSTRUCTOR
 *
 */
SDLInterface::SDLInterface() {
	printf("new SDLInterface\n");
	_screenW = 0;
	_screenH = 0;

	//font variables init
	_font = NULL;
	_fontFilename = "";
	_fontSize = 15; // default 15
	SDL_Color color = { 255, 255, 255 };
	_fontColor = color; // default white
	_transColor.r = 0;
	_transColor.g = 255;
	_transColor.b = 255;

	_nbLayer = 1;
	printf("new SDLInterface::End\n");
}

/**
 * intialize the SDL stuff
 *
 */
bool SDLInterface::init(int w, int h, int bpp, string caption, int nbLayer) {
	_screenW = w;
	_screenH = h;
	if (nbLayer < 1) {
		nbLayer = 1; // force to have at least ONE layer
	}
	_nbLayer = nbLayer;

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

	// set the number of layer you'll have
	for (int i = 0; i < _nbLayer; i++) {
		queue<Sprite*> temp;
		_layerQueue.push_back(temp); // init the sprite queue
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
 * intToString
 *  cast int to string...
 */
string SDLInterface::intToString(Uint32 number) {
	stringstream ss; //create a stringstream
	ss << number; //add number to the stream
	return ss.str(); //return a string with the contents of the stream
}

/**
 * formatTime
 *  return a readable time format string from a milisec value
 */
string SDLInterface::formatTime(Uint32 total) {
	// Render the FPS on screen
	Uint32 minute = abs(total / 60000);
	Uint32 second = abs((total % 60000) / 1000);
	Uint32 milisec = abs((total % 60000) - (second * 1000));

	return intToString(minute) + ":" + intToString(second) + "."
			+ intToString(milisec);
	//string timeString = "Time: " + intToString(total);
	//_sdl->renderText(10, 20, 3, timeString, 200);
}

/**
 * Set the font to use and its size
 *
 */
bool SDLInterface::setFont(string filename, int size) {
	//printf("SDLInterface::setFont(%s, %d)\n", filename.c_str(), size);
	if (_font != NULL) {
		//quitte le font utilisé
		TTF_CloseFont(_font);
	}
	//Ouverture du font
	_font = TTF_OpenFont(filename.c_str(), size);

	if (_font == NULL) {
		printf("setFont retourne NULL\n");
		return false;
	}

	_fontFilename = filename;

	return true;
}

void SDLInterface::setFontSize(int size) {
	setFont(_fontFilename.c_str(), size);
}

/**
 * Set the font color
 *
 */
void SDLInterface::setTextColor(Uint8 r, Uint8 g, Uint8 b) {
	if (abs(r) <= 255) {
		_fontColor.r = abs(r);
	}
	if (abs(g) <= 255) {
		_fontColor.g = abs(g);
	}
	if (abs(b) <= 255) {
		_fontColor.b = abs(b);
	}
}

void SDLInterface::setTransparentColor(int r, int g, int b) {
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
SDL_Surface * SDLInterface::createSurface(int width, int height,
		SDL_Surface* display) {
	if (display == NULL) {
		display = _screen;
	}
	// 'display' is the surface whose format you want to match
	//  if this is really the display format, then use the surface returned from SDL_SetVideoMode

	SDL_Surface * tempSurf = NULL;
	const SDL_PixelFormat& fmt = *(display->format);
	tempSurf = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height,
			fmt.BitsPerPixel, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);
	SDL_FillRect(tempSurf, NULL, SDL_MapRGB(&fmt, 0, 255, 255));
	SDL_SetColorKey(tempSurf, SDL_RLEACCEL | SDL_SRCCOLORKEY,
			SDL_MapRGB(tempSurf->format, 0, 255, 255));
	return tempSurf;
}

/**
 * load_image
 * Load an image and return an optimized SDL_Surface version of it
 *
 */
SDL_Surface * SDLInterface::load_image(string filename) {
	//printf("SDLInterface::load_image(%s)\n", filename.c_str());
	//L'image qui est chargée
	SDL_Surface* loadedImage = NULL;

	//L'image optimisée que nous utiliserons par la suite
	SDL_Surface* optimizedImage = NULL;

	//Chargement de l'image
	loadedImage = IMG_Load(filename.c_str());
	//printf("IMG_Load OK\n");
	//Si l'image est chargée correctement
	if (loadedImage != NULL) {
		//printf("%s != NULL\n", filename.c_str());
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
	//printf("SDLInterface::load_image::END\n");
	//on retourne l'image optimisé
	return optimizedImage;
}

/**
 * createTextSurface
 * Return an SDL_Surface out of a text
 */
SDL_Surface * SDLInterface::createTextSurface(string text) {
	return TTF_RenderText_Solid(_font, text.c_str(), _fontColor);
}

/**
 * pushSprite
 * Add sprite to the desired int Layer.
 *
 */
void SDLInterface::pushSprite(Sprite * sprite, int layer) {
	//cout << "pushSprite layer: " << layer << endl;

	if ((layer >= 0) && (layer < _nbLayer)) {
		_layerQueue.at(layer).push(sprite);
	}
	//cout << "pushSprite::END" << endl;
}

/**
 * Apply an image "source" onto the Surface[layer]
 * Apply on screen by default
 */

void SDLInterface::apply_surface(int x, int y, SDL_Surface* source, int alpha,
		SDL_Rect* clip, SDL_Surface * destination) {

	if (destination == NULL) {
		destination = _screen;
	}

	if ((alpha < 0) || (alpha > 255)) {
		return;
	}

	if (source == NULL) {
		return;
	}

	SDL_SetAlpha(source, SDL_SRCALPHA | SDL_RLEACCEL, alpha);

	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	//on blit la surface
	SDL_BlitSurface(source, clip, destination, &offset);
}

/**
 * Apply a text "text" onto the Surface[layer]
 * Apply on screen by default
 */
bool SDLInterface::renderText(int x, int y, int layer, string text, int alpha,
		int size, SDL_Rect* clip) {

	if ((alpha < 0) || (alpha > 255)) {
		alpha = 255;
	}

	if ((layer < 0) || (layer >= _nbLayer)) {
		layer = _nbLayer - 1;
	}

	setFontSize(size);

	// Create a temp surface with the text
	SDL_Surface * textSurface = createTextSurface(text);

	if (textSurface == NULL) {
		return false;
	}

	setFontSize(15);
	// Apply that text surface on the destination
	//apply_surface(x, y, textSurface, alpha, clip);
	pushSprite(new Sprite(x, y, textSurface, alpha), layer);

	return true;
}

/**
 * Flip the screen
 * but apply all the layer on the sreen first
 */
void SDLInterface::render() {
	//printf("SDLInterface::render()\n");

	for (int i = 0; i < _nbLayer; i++) {
		//printf("_layer at (%d) = %d\n", i, _layerQueue.at(i).empty());

		if (!_layerQueue.at(i).empty()) {
			queue<Sprite*> * tempSpriteQu = &_layerQueue.at(i);

			// Apply all the sprites
			while (!tempSpriteQu->empty()) {
				// Handle the next Sprite
				Sprite * tSprite = tempSpriteQu->front();

				// Apply the temp sprite on the screen
				apply_surface(tSprite->getX(), tSprite->getY(),
						tSprite->getSurface(), tSprite->getAlpha(),
						tSprite->getClip());

				tempSpriteQu->pop(); // remove pointer to the applied sprite
			} // do that until it has been emptied

			//printf("just emptied: %d\n",i);

		}
	}

	//printf("before flip screen\n");
// Show the updated screen
	SDL_Flip(_screen);
}

/**
 * Close all the SDL stuff
 *
 */
void SDLInterface::cleanUp() {
	for (int i = 0; i < _nbLayer; i++) {
		//SDL_FreeSurface(&_layer[i]);
	}
//On ferme le font qu'on a utilisé
	TTF_CloseFont(_font);

//On quitte SDL_ttf
	TTF_Quit();

//On quitte SDL
	SDL_Quit();
}
