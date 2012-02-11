/**
 *  File: Graphic.cpp
 *  Project: Kore-Engine
 *
 *  Description: This file contains handles all the graphic subsytems and
 *		basic window management.
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "Global.h"
#include "Graphic.h"
//#include "Singleton.h"
#include "TextureManager.h"
#include "Camera.h"

using namespace std;

namespace TileEngine {
//
// Default constructor
//
Graphic::Graphic() {
	glScissor(0, 0, m_Width, m_Height);
	_isLoaded = false;
}

//
// Default destructor
//
Graphic::~Graphic() {
	shutdown();
}

//
// Sets up a windows properties
/// must be called before CreateWindow towork properly
/// @param Width a int
/// @param Height a int
/// @param Bpp a int
/// @param WindowTitle a std::string
bool Graphic::initialize(int Width, int Height, int Bpp,
		std::string WindowTitle) {
	m_Width = Width;
	m_Height = Height;
	m_Bpp = Bpp;
	m_WindowTitle = WindowTitle;
	_isFullscreen = false;
	m_Surface = NULL;

	//if we reinitalize then reload the textures
	if (_isLoaded) {
		TextureManager::getInstance()->ReloadTextures();
	}

	_isLoaded = true;

	return 1;
}

//
// Creates a window from drawing on
/// Intialize must be called first and a window must be created
/// before you can use any drawing functions
/// @return Success or failure
///
bool Graphic::makeWindow() {
	//initalize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "Unable to initialize SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	m_SdlFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE
			| SDL_RESIZABLE;
	_isFullscreen = false;

	const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();

	if (videoInfo->hw_available) {
		m_SdlFlags |= SDL_HWSURFACE;
	} else {
		m_SdlFlags |= SDL_SWSURFACE;
	}

	// This checks if hardware blits can be done
	if (videoInfo->blit_hw) {
		m_SdlFlags |= SDL_HWACCEL;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);

	// Anti-aliasing
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	// A-Alias x2 ou x4 ou etc
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

	// Sets up OpenGL double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//kill sdl on exiting
	atexit(SDL_Quit);

	//create the surface
	m_Surface = SDL_SetVideoMode(m_Width, m_Height, m_Bpp, m_SdlFlags);

	if (m_Surface == NULL) {
		cout << "Video mode set failed: " << SDL_GetError() << endl;
		SDL_Quit();
	}

	initGl();

	//set the window title
	SDL_WM_SetCaption(m_WindowTitle.c_str(), NULL);

	return 1;
}

//
// Resizes the window to the given size
/// @param width a int
/// @param height a int
///
void Graphic::resizeWindow(int width, int height) {
	// Protect against a divide by zero
	if (height == 0) {
		height = 1;
	}

	//resize sdl surface
	m_Surface = SDL_SetVideoMode(width, height, m_Bpp, m_SdlFlags);

	if (m_Surface == NULL) {
		cout << "Could not get a surface after resize: " << SDL_GetError()
				<< endl;
		exit(1);
	}

	//reinitalize opengl
	initGl();

	//reload textures
	TextureManager::getInstance()->ReloadTextures();
}

//
// Returns the width of the drawing area
/// @return Width of the drawing area
///
int Graphic::getWidth() {
	return m_Width;
}

//
// Returns the height of the drawing area
/// @return Height of the drawing area
///
int Graphic::getHeight() {
	return m_Height;
}

void Graphic::setCaption(string caption) {
	SDL_WM_SetCaption(caption.c_str(), NULL);
}

//
// internal function to setup opengl's othomode
//
void Graphic::initGl() {
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f); // cyan in the background by default
	glClearDepth(0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_SCISSOR_TEST);
	//setup ortho mode
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, (GLfloat) (m_Width), 0, (GLfloat) (m_Height), -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

//
// Turns fullscreen on or off
//
void Graphic::toggleFullScreen() {
	_isFullscreen = !_isFullscreen;
	if (m_Surface != NULL) {
		SDL_WM_ToggleFullScreen(m_Surface);

		if (!_isFullscreen) {
			SDL_ShowCursor(SDL_ENABLE);
		} else {
			SDL_ShowCursor(SDL_DISABLE);
		}
	}
}

//
// Draws an empty Rectangle
/// @param x a GLfloat
/// @param y a GLfloat
/// @param width a GLfloat
/// @param height a GLfloat
/// @param red a GLfloat
/// @param green a GLfloat
/// @param blue a GLfloat
/// @param alpha a GLfloat
///
void Graphic::drawRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height,
		GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(Camera::getInstance()->getXposition() + x,
			Camera::getInstance()->getYposition() + y, 0.0);
	glBegin(GL_LINE_LOOP);
	glColor4f(red, green, blue, alpha);
	glVertex2f(x, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glVertex2f(x + width, y);
	glEnd();
	glPopMatrix();
}

//
// Draws an filled rectangle
/// @param x a GLfloat
/// @param y a GLfloat
/// @param width a GLfloat
/// @param height a GLfloat
/// @param red a GLfloat
/// @param green a GLfloat
/// @param blue a GLfloat
/// @param alpha a GLfloat
///
void Graphic::drawFilledRectangle(GLfloat x, GLfloat y, GLfloat width,
		GLfloat height, GLfloat red, GLfloat green, GLfloat blue,
		GLfloat alpha) {
	glColor4f(red, green, blue, alpha);
	glBegin(GL_QUADS);
	glVertex3f(x, y, 0);
	glVertex3f(x + width, y, 0);
	glVertex3f(x + width, y + height, 0);
	glVertex3f(x, y + height, 0);
	glEnd();
}

//
// Draws a line
/// @param x a GLfloat
/// @param y a GLfloat
/// @param width a GLfloat
/// @param height a GLfloat
/// @param red a GLfloat
/// @param green a GLfloat
/// @param blue a GLfloat
/// @param alpha a GLfloat
///
void Graphic::drawLine(GLfloat x, GLfloat y, GLfloat x2, GLfloat y2,
		GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	glColor4f(red, green, blue, alpha);
	glBegin(GL_LINES);
	glVertex3f(x, y, 0);
	glVertex3f(x2, y2, 0);
	glEnd();
}

//
// Flips the screen from the backbuffer to the screen
//
void Graphic::flipBuffers() {
	SDL_GL_SwapBuffers();
}

//
// clears the screen with a grey color
//
void Graphic::clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//
// Kills all graphic subsystems
//
void Graphic::shutdown() {
}

//
// returns the current texture in memory
/// @return the current texture
///
GLuint Graphic::getCurrentTexture() {
	return m_CurrentTexture;
}

//
// set the current texture in memory
/// @param texture a Gluint
///
void Graphic::setCurrentTexture(GLuint texture) {
	m_CurrentTexture = texture;
}

//
// Pushes a clipping area on the stack for drawing
/// @param area a sRect
///
void Graphic::pushClippingArea(RectStruct area) {
	RectStruct newArea;
	RectStruct currentArea;
	//get the current clipping area
	if (!m_ClippingArea.empty()) {
		currentArea = m_ClippingArea.top();
	} else {
		RectStruct fullArea;
		fullArea.bottom = (GLfloat) (0);
		fullArea.top = (GLfloat) (m_Height);
		fullArea.left = (GLfloat) (0);
		fullArea.right = (GLfloat) (m_Width);
		currentArea = fullArea;
	}
	//make the new clipping area
	//bottom
	if (currentArea.bottom > area.bottom) {
		newArea.bottom = currentArea.bottom;
	} else {
		newArea.bottom = area.bottom;
	}
	//top
	if (currentArea.top < area.top) {
		newArea.top = currentArea.top;
	} else {
		newArea.top = area.top;
	}
	//left
	if (currentArea.left > area.left) {
		newArea.left = currentArea.left;
	} else {
		newArea.left = area.left;
	}
	//right
	if (currentArea.right < area.right) {
		newArea.right = currentArea.right;
	} else {
		newArea.right = area.right;
	}
	m_ClippingArea.push(newArea);
	glScissor((GLsizei) (newArea.left), (GLsizei) (newArea.bottom),
			(GLint) ((newArea.right - newArea.left)),
			(GLint) ((newArea.top - newArea.bottom)));
}

/// Pops a clipping area off the stack
void Graphic::popClippingArea() {
	RectStruct newArea;
	m_ClippingArea.pop();
	if (m_ClippingArea.empty()) {
		RectStruct fullArea;
		fullArea.bottom = (GLfloat) (0);
		fullArea.top = (GLfloat) (m_Height);
		fullArea.left = (GLfloat) (0);
		fullArea.right = (GLfloat) (m_Width);
		newArea = fullArea;
	} else {
		newArea = m_ClippingArea.top();
	}
	glScissor((GLsizei) (newArea.left), (GLsizei) (newArea.bottom),
			(GLint) ((newArea.right - newArea.left)),
			(GLint) ((newArea.top - newArea.bottom)));
}
}
