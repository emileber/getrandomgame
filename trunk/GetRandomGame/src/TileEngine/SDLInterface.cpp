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
	_fontFilename = "";
	_fontSize = 15; // default 15
	SDL_Color color = { 255, 255, 255 };
	_fontColor = color; // default white
	_transColor.r = 0;
	_transColor.g = 255;
	_transColor.b = 255;

	_nbLayer = 1;
	cout << "new SDLInterface::End" << endl;
}

/**
 * intialize the SDL stuff
 *
 */
bool SDLInterface::init(int w, int h, int bpp, string caption, int nbLayer) {
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
		queue<Animation*> temp;
		_layer.push_back(temp);
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

string SDLInterface::intToString(int number) {
	stringstream ss; //create a stringstream
	ss << number; //add number to the stream
	return ss.str(); //return a string with the contents of the stream
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

	_fontFilename = filename;

	return true;
}

void SDLInterface::setFontSize(int size){
	_font = TTF_OpenFont(_fontFilename.c_str(), size);
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

SDL_Surface * SDLInterface::createSurface(int width, int height,
		SDL_Surface* display) {
	// 'display' is the surface whose format you want to match
	//  if this is really the display format, then use the surface returned from SDL_SetVideoMode

	const SDL_PixelFormat& fmt = *(display->format);
	return SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, fmt.BitsPerPixel,
			fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);
}

/**
 * load_image
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
void SDLInterface::pushSprite(Animation * sprite, int layer) {
	//cout << "pushSprite layer: " << layer << endl;
	if ((layer >= 0) && (layer < _nbLayer)) {
		_layer.at(layer).push(sprite);
	}
	//cout << "pushSprite::END" << endl;
}

/**
 * Apply an image "source" onto the Surface[layer]
 * Apply on screen by default
 */

void SDLInterface::apply_surface(int x, int y, SDL_Surface* source, int alpha,
		SDL_Rect* clip) {

	if ((alpha < 0) || (alpha > 255)) {
		return;
	}

	if (source == NULL){
		return;
	}

	SDL_SetAlpha(source, SDL_SRCALPHA | SDL_RLEACCEL, alpha);

	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	//on blit la surface
	SDL_BlitSurface(source, clip, _screen, &offset);
}

/**
 * Apply a text "text" onto the Surface[layer]
 * Apply on screen by default
 */
bool SDLInterface::renderText(int x, int y, string text, int alpha, int size,
		SDL_Rect* clip) {

	if ((alpha < 0) || (alpha > 255)) {
		alpha = 255;
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
	pushSprite(new Animation(x, y, textSurface, alpha), _nbLayer-1);

	return true;
}

/**
 * Flip the screen
 * but apply all the layer on the sreen first
 */
void SDLInterface::render() {
	//cout << "SDLInterface::render()" << endl;
	for (int i = 0; i < _nbLayer; i++) {
		//cout << "_layer at (" << i << ") = " << _layer.at(i).empty() << endl;
		if (!_layer.at(i).empty()) {
			queue<Animation*> * tempSpriteQu = &_layer.at(i);

			// Apply all the sprites
			while (!tempSpriteQu->empty()) {
				// Handle the next Sprite
				Animation * tSprite = tempSpriteQu->front();

				// Apply the temp sprite on the screen
				apply_surface(tSprite->getX(), tSprite->getY(),
						tSprite->getSurface(), tSprite->getAlpha(), tSprite->getClip());

				tempSpriteQu->pop(); // remove pointer to the applied sprite
			} // do that until it has been emptied
		}
	}

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
