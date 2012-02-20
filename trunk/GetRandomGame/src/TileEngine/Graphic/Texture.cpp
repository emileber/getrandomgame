/*
 * Texture.cpp
 *
 *  Created on: 2012-01-23
 *      Author: Emile
 */

#include "Texture.h"
#include "Graphic.h"
#include "Camera.h"
#include "GraphicType.h"

using namespace std;

namespace TileEngine {
//
// Default contructor
//
Texture::Texture() {
	_Width = 0;
	_Height = 0;
	_Texture = 0;
	_Surface = NULL;
}

//
// Constructor that loads a file
/// @param Filename a std::string
Texture::Texture(std::string Filename) {
	load(Filename);
}

//
// Default destructor
//
Texture::~Texture() {
	kill();
}

//
// Loads the texture to memory
/// @param filename a std::string
///
void Texture::load(std::string filename) {
	//load the image from a file via sdl_img
	SDL_Surface* surface = IMG_Load(filename.c_str());

	if (surface == NULL) {
		cout << "Failed to load the image: " << filename << ", Error: "
				<< SDL_GetError() << endl;
		_isLoaded = false;
		return;
	}

	_filename = filename; // Ressource filename

	_Surface = surface;

	makeTexture(surface);
	_isLoaded = true; // Ressource loaded
}

//
// Internal function for loading a texture from a surface
/// @param Surface a SDL_Surface pointer
///
void Texture::makeTexture(SDL_Surface* Surface) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glGenTextures(1, &_Texture);
	glBindTexture(GL_TEXTURE_2D, _Texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_PixelFormat *fmt = Surface->format;

	//setup all the information
	_Width = (GLfloat) (Surface->w);
	_Height = (GLfloat) (Surface->h);
	//setup the pixel data (used for collisions)
//	if (LoadCollision) {
//		SDL_LockSurface(Surface);
//		Uint32 *sur_pixels = (Uint32*) (Surface->pixels);
//		Uint32 pixel;
//		SDL_UnlockSurface(Surface);
//		SDL_PixelFormat *format = Surface->format;
//		Uint32 temp;
//		Uint8 alpha;
//		std::vector<bool> pixTemp;
//		for (int x = 0; x < (int) (_Width); x++) {
//			pixTemp.push_back(false);
//		}
//		for (int y = 0; y < (int) (_Height); y++) {
//			_PixelOn.push_back(pixTemp);
//		}
//		pixel = *(sur_pixels++);
//		for (int y = 0; y < (int) (_Height); y++) {
//			for (int x = 0; x < (int) (_Width); x++) {
//				temp = pixel & format->Amask;
//				temp = temp >> fmt->Ashift;
//				temp = temp << fmt->Aloss;
//				alpha = (Uint8) (temp);
//				if (alpha >= 200) {
//					_PixelOn[y][x] = true;
//				}
//				pixel = *(sur_pixels++);
//			}
//
//		}
//
//		//flip rows so it's represented right in memory
//		vector<vector<bool> > colTmp;
//		for (int y = _Height - 1; y >= 0; y--) {
//			colTmp.push_back(_PixelOn[y]);
//		}
//		_PixelOn.clear();
//		_PixelOn = colTmp;
//	}

	//if there is alpha
	if (fmt->Amask) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, _Width, _Height, GL_RGBA,
				GL_UNSIGNED_BYTE, Surface->pixels);
	} else // no alpha
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, _Width, _Height, GL_RGB,
				GL_UNSIGNED_BYTE, Surface->pixels);
	}
	//TextureManager::getInstance()->registerTexture(this);

	_isLoaded = true; // Ressource loaded

}

//
// Deletes the texture
//
void Texture::kill() {
	if (_isLoaded) {
		glDeleteTextures(1, &_Texture);
		SDL_FreeSurface(_Surface);
	}
}

//
// Reloads the texture
//
//void Texture::reload() {
//	//only reload if it's a real file
//	if (_filename != "") {
//		load(_filename);
//	}
//}

//
// Moves the camera, binds the texture if nessiary and does scaling/rotation
/// @param Scale a GLfloat
/// @param Rotation a GLfloat
/// @param X a GLfloat
/// @param Y a GLfloat
///
void Texture::initializeDraw(GLfloat scale, GLfloat rotation, GLfloat x,
		GLfloat y, SectionRect *rect) {
	Graphic *graphics = Graphic::getInstance();
	//check if the right texture is bound
	if (graphics->getCurrentTexture() != _Texture) {
		//bind texture
		glBindTexture(GL_TEXTURE_2D, _Texture);

		//set graphics varible
		graphics->setCurrentTexture(_Texture);
	}
	//scale the points if needed
	glLoadIdentity();
	glTranslatef(Camera::getInstance()->getXposition() + x,
			Camera::getInstance()->getYposition() + y, 0.0f);
//	if (rotation != 0) {
//		GLfloat x, y;
//		x = ((rect->right - rect->left) / 2) * m_Width;
//		y = ((rect->top - rect->bottom) / 2) * m_Height;
//		glTranslatef(x, y, 0.0f);
//		glRotatef(rotation, 0.0f, 0.0f, 1.0f);
//		glTranslatef(-x, -y, 0.0f);
//	}
	glScaled(scale, scale, 0);
}

//
/// Returns the pixel data
/// @return
///
std::vector<std::vector<bool> > *Texture::getPixels() {
	return &_PixelOn;
}

//
// Draws the whole texture
/// @param X a GLfloat
/// @param Y a GLfloat
/// @param Scale a GLfloat
/// @param Rotation a GLfloat
/// @param red a GLfloat
/// @param green a GLfloat
/// @param blue a GLfloat
/// @param alpha a GLfloat
///
void Texture::draw(GLfloat x, GLfloat y, GLfloat scale, GLfloat rotation,
		GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	glPushMatrix();
//	RectStruct rect;
//	rect.bottom = 0.0f;
//	rect.top = 1.0f;
//	rect.right = 1.0f;
//	rect.left = 0.0f;
	initializeDraw(scale, rotation, x, y, NULL);

	//draw the quad
	glBegin(GL_QUADS);
	glColor4f(red, green, blue, alpha);
	//bottom-left vertex (corner)
	glTexCoord2f(0, 0);
	glVertex2f(0, _Height);
	//bottom-right vertex (corner)
	glTexCoord2f(1, 0);
	glVertex2f(_Width, _Height);
	//top-right vertex (corner)
	glTexCoord2f(1, 1);
	glVertex2f(_Width, 0);
	//top-left vertex (corner)
	glTexCoord2f(0, 1);
	glVertex2f(0, 0);

	glEnd();

	//reset the color
	glColor3f(1.0f, 1.0f, 1.0f);
	glPopMatrix();
}

//
// Draws a section of a texture
/// @param X a GLfloat
/// @param Y a GLfloat
/// @param Box a sRect pointer
/// @param Scale a GLfloat
/// @param Rotation a GLfloat
/// @param red a GLfloat
/// @param green a GLfloat
/// @param blue a GLfloat
/// @param alpha a GLfloat
///
void Texture::drawSection(GLfloat x, GLfloat y, SectionRect * box,
		GLfloat scale, GLfloat rotation, GLfloat red, GLfloat green,
		GLfloat blue, GLfloat alpha) {
	glPushMatrix();
	initializeDraw(scale, rotation, x, y, box);
	//width for drawing
	GLfloat box_left = 1.0f * (box->x / _Width);
	GLfloat box_right = 1.0f * ((box->x + box->w) / _Width);
	GLfloat box_top = 1.0f - (1.0f * ((box->y + box->h) / _Height));
	GLfloat box_bottom = 1.0f - (1.0f * (box->y / _Height));
	//draw the quad
	glBegin(GL_QUADS);
	//bottom-left vertex (corner)
	glColor4f(red, green, blue, alpha);
	glTexCoord2f(box_left, box_bottom);
	glVertex2f(0, 0);
	//bottom-right vertex (corner)
	glTexCoord2f(box_right, box_bottom);
	glVertex2f(box->w, 0);
	//top-right vertex (corner)
	glTexCoord2f(box_right, box_top);
	glVertex2f(box->w, box->h);
	//top-left vertex (corner)
	glTexCoord2f(box_left, box_top);
	glVertex2f(0, box->h);
	glEnd();
	//reset the color
	glColor3f(1.0f, 1.0f, 1.0f);
	glPopMatrix();
}

} // fin du namespace
