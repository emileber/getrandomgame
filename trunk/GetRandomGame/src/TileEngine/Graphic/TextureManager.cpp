/**
 *  File: TextureManager.cpp
 *  Project: Kore-Engine
 *
 *  Description: This file contains all the texture functions
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "TextureManager.h"
#include "Graphic.h"
#include "Camera.h"
#include "GraphicType.h"
#include "SDLInterface.h"
//#include "SDL_rwops_zzip.h"
#include "Singleton.h"

using namespace std;

namespace TileEngine {
//
// Default contructor
//
Texture::Texture() {
	m_Width = 0;
	m_Height = 0;
	m_Texture = 0;
	m_Filename = "";
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
	deleteTexture();
}

//
// Returns the width of the texture
/// @return The width of the texture
///
GLfloat Texture::getWidth() {
	return m_Width;
}

//
// Returns the height of the texture
/// @return the height of the texture
///
GLfloat Texture::getHeight() {
	return m_Height;
}

//
// Loads file from a zip file
/// @param filename s std::string
/// Note: format is packname/filename,
///	 a packfile can not have directories within it
//	void Texture::LoadFromZip(std::string filename)
//	{
//		string mode = "rb";
//
//		SDL_RWops* ImageData = SDL_RWFromZZIP(filename.c_str(), mode.c_str());
//
//		if(ImageData == NULL)
//		{
//			cout << "Failed to load the image from zip: " << filename << endl;
//			return;
//		}
//
//		SDL_Surface* Surface = IMG_Load_RW(ImageData, 0);
//		SDL_FreeRW(ImageData);
//
//		m_Filename = filename;
//		MakeTexture(Surface);
//	}

//
// Loads the texture to memory
/// @param filename a std::string
///
void Texture::load(std::string filename, bool LoadCollision) {
	//load the image from a file via sdl_img
	//SDL_Surface* surface = SDLInterface::getInstance()->load_image(
	//		filename.c_str());
	SDL_Surface* surface = IMG_Load(filename.c_str());

	if (surface == NULL) {
		cout << "Failed to load the image: " << filename << ", Error: "
				<< SDL_GetError() << endl;
		return;
	}

	//int w = pow(2, ceil(log(surface->w) / log(2)));
	//int h = pow(2, ceil(log(surface->h) / log(2)));

	SDL_Surface* newSurface = SDL_CreateRGBSurface(0, surface->w, surface->h,
			24, 0x0000ff00, 0x00ff0000, 0xff000000, 0);
	SDL_BlitSurface(surface, 0, newSurface, 0); // Blit onto a purely RGB Surface

	m_Filename = filename;
	makeTexture(newSurface, LoadCollision);

	//free the image
	SDL_FreeSurface(newSurface);
	SDL_FreeSurface(surface);
}

//
// Internal function for loading a texture from a surface
/// @param Surface a SDL_Surface pointer
///
//void Texture::makeTexture(SDL_Surface* Surface, bool LoadCollision) {
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
//
//	glGenTextures(1, &m_Texture);
//	glBindTexture(GL_TEXTURE_2D, m_Texture);
//
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//	SDL_PixelFormat *fmt = Surface->format;
//
//	//setup all the information
//	m_Width = (GLfloat) (Surface->w);
//	m_Height = (GLfloat) (Surface->h);
//	//setup the pixel data (used for collisions)
//	if (LoadCollision) {
//		SDL_LockSurface(Surface);
//		Uint32 *sur_pixels = (Uint32*) (Surface->pixels);
//		Uint32 pixel;
//		SDL_UnlockSurface(Surface);
//		SDL_PixelFormat *format = Surface->format;
//		Uint32 temp;
//		Uint8 alpha;
//		std::vector<bool> pixTemp;
//		for (int x = 0; x < (int) (m_Width); x++) {
//			pixTemp.push_back(false);
//		}
//		for (int y = 0; y < (int) (m_Height); y++) {
//			m_PixelOn.push_back(pixTemp);
//		}
//		pixel = *(sur_pixels++);
//		for (int y = 0; y < (int) (m_Height); y++) {
//			for (int x = 0; x < (int) (m_Width); x++) {
//				temp = pixel & format->Amask;
//				temp = temp >> fmt->Ashift;
//				temp = temp << fmt->Aloss;
//				alpha = (Uint8) (temp);
//				if (alpha >= 200) {
//					m_PixelOn[y][x] = true;
//				}
//				pixel = *(sur_pixels++);
//			}
//
//		}
//
//		//flip rows so it's represented right in memory
//		vector<vector<bool> > colTmp;
//		for (int y = m_Height - 1; y >= 0; y--) {
//			colTmp.push_back(m_PixelOn[y]);
//		}
//		m_PixelOn.clear();
//		m_PixelOn = colTmp;
//	}
//
//	//if there is alpha
//	if (fmt->Amask) {
//		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, m_Width, m_Height, GL_RGBA,
//				GL_UNSIGNED_BYTE, Surface->pixels);
//	} else // no alpha
//	{
//		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Width, m_Height, GL_RGB,
//				GL_UNSIGNED_BYTE, Surface->pixels);
//	}
//	TextureManager::getInstance()->RegisterTexture(this);
//}

void Texture::makeTexture(SDL_Surface* surface, bool LoadCollision) {
	cleanup();

	if (surface == NULL) {
		return;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glGenTextures(1, &m_Texture);

	glBindTexture(GL_TEXTURE_2D, m_Texture);

	SDL_LockSurface(surface);

	printf("%s BPP: %d\n", m_Filename.c_str(), surface->format->BytesPerPixel);

//	int Mode = GL_RGB;
//
//	if (surface->format->BytesPerPixel == 4) {
//		Mode = GL_RGBA;
//	} else if (surface->format->BytesPerPixel == 1) {
//		//Mode = GL_BGR;
//	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//			GL_LINEAR_MIPMAP_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
//			GL_LINEAR_MIPMAP_LINEAR);

//	glTexImage2D(GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, GL_RGB,
//			GL_UNSIGNED_BYTE, surface->pixels);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, surface->w, surface->h, GL_RGB,
			GL_UNSIGNED_BYTE, surface->pixels);

	m_Width = surface->w;
	m_Height = surface->h;

	TextureManager::getInstance()->RegisterTexture(this);

	SDL_UnlockSurface(surface);
}

//-----------------------------------------------------------------------------
void Texture::cleanup() {
	if (m_Texture > 0) {
		glDeleteTextures(1, &m_Texture);
		m_Texture = 0;
	}
}

//
// Deletes the texture
//
void Texture::deleteTexture() {
	// this line has a BUG fix it!
	TextureManager::getInstance()->UnRegisterTexture(this);
}

//
// Reloads the texture
//
void Texture::reload() {
	//only reload if it's a real file
	if (m_Filename != "") {
		load(m_Filename);
	}
}

//
// Moves the camera, binds the texture if nessiary and does scaling/rotation
/// @param Scale a GLfloat
/// @param Rotation a GLfloat
/// @param X a GLfloat
/// @param Y a GLfloat
///
void Texture::initializeDraw(GLfloat scale, GLfloat rotation, GLfloat x,
		GLfloat y, sRect *rect) {
	Graphic *graphics = Graphic::getInstance();
	//check if the right texture is bound
	if (graphics->getCurrentTexture() != m_Texture) {
		//bind texture
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		//set graphics varible
		graphics->setCurrentTexture(m_Texture);
	}
	//scale the points if needed
	glLoadIdentity();
	glTranslatef(Camera::getInstance()->getXposition() + x,
			Camera::getInstance()->getYposition() + y, 0.0f);
	if (rotation != 0) {
		GLfloat x, y;
		x = ((rect->Right - rect->Left) / 2) * m_Width;
		y = ((rect->Top - rect->Bottom) / 2) * m_Height;
		glTranslatef(x, y, 0.0f);
		glRotatef(rotation, 0.0f, 0.0f, 1.0f);
		glTranslatef(-x, -y, 0.0f);
	}
	glScaled(scale, scale, 0);
}

//
/// Returns the pixel data
/// @return
///
std::vector<std::vector<bool> > *Texture::getPixels() {
	return &m_PixelOn;
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
	sRect rect;
	rect.Bottom = 0.0f;
	rect.Top = 1.0f;
	rect.Right = 1.0f;
	rect.Left = 0.0f;
	initializeDraw(scale, rotation, x, y, &rect);

	glColor4f(red, green, blue, alpha);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	//draw the quad
	glBegin(GL_QUADS);
	//bottom-left vertex (corner)
	glTexCoord2f(0, 0);
	glVertex2f(0, m_Height);
	//bottom-right vertex (corner)
	glTexCoord2f(1, 0);
	glVertex2f(m_Width, m_Height);
	//top-right vertex (corner)
	glTexCoord2f(1, 1);
	glVertex2f(m_Width, 0);
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
void Texture::drawSection(GLfloat X, GLfloat Y, sRect *Box, GLfloat Scale,
		GLfloat Rotation, GLfloat red, GLfloat green, GLfloat blue,
		GLfloat alpha) {
	glPushMatrix();
	initializeDraw(Scale, Rotation, X, Y, Box);
	//width for drawing
	GLfloat box_width = m_Width * (Box->Right - Box->Left);
	GLfloat box_height = m_Height * (Box->Top - Box->Bottom);
	GLfloat box_top = 1.0f - Box->Top;
	GLfloat box_bottom = 1.0f - Box->Bottom;
	//draw the quad
	glBegin(GL_QUADS);
	//bottom-left vertex (corner)
	glColor4f(red, green, blue, alpha);
	glTexCoord2f(Box->Left, box_bottom);
	glVertex2f(0, 0);
	//bottom-right vertex (corner)
	glTexCoord2f(Box->Right, box_bottom);
	glVertex2f(box_width, 0);
	//top-right vertex (corner)
	glTexCoord2f(Box->Right, box_top);
	glVertex2f(box_width, box_height);
	//top-left vertex (corner)
	glTexCoord2f(Box->Left, box_top);
	glVertex2f(0, box_height);
	glEnd();
	//reset the color
	glColor3f(1.0f, 1.0f, 1.0f);
	glPopMatrix();
}

//////////////////////////////////////////////////////////////
//	start texture manager code
//////////////////////////////////////////////////////////////
//
// Default Constructor
//
TextureManager::TextureManager() {
	m_Textures.clear();
}

//
// Default Destructor
//
TextureManager::~TextureManager() {
	DeleteTextures();
}

//
// Reloads all textures
//
void TextureManager::ReloadTextures() {
	//reload all textures
	for (uint i = 0; i < m_Textures.size(); i++) {
		m_Textures[i]->reload();
	}
}

//
// Deletes all textures
//
void TextureManager::DeleteTextures() {
	//delete all textures
	for (uint i = 0; i < m_Textures.size(); i++) {
		m_Textures[i]->deleteTexture();
	}
}

//
// Registers a texture for management
//
void TextureManager::RegisterTexture(Texture *Texture) {
	//check to see if the texture isn't actually just been reloaded
	for (uint i = 0; i < m_Textures.size(); i++) {
		if (m_Textures[i]->m_Texture == Texture->m_Texture) {
			return;
		}
	}
	//add the texture to the vector
	m_Textures.push_back(Texture);
}

Texture *TextureManager::loadTextureFromFile(std::string filename) {

	return new Texture(filename);
}

//
// Removes a texture from the texture manager
//
void TextureManager::UnRegisterTexture(Texture *Texture) {
	int place = -1;
	//lets find where the texture is in the vector
	for (uint i = 0; i < m_Textures.size(); i++) {
		if (m_Textures[i]->m_Texture == Texture->m_Texture) {
			place = i;
		}
	}
	//if its not registed then do nothing
	if (place == -1) {
		return;
	}
	//if the place is at the end just remove the texture
	if ((place + 1) == (int) (m_Textures.size())) {
		m_Textures.erase(m_Textures.begin() + place);
	} else // move the last place to the empty slot and remove the last one element
	{
		m_Textures[place] = m_Textures[m_Textures.size() - 1];
		m_Textures.erase(m_Textures.begin() + place);
	}

	delete Texture;
}
}
