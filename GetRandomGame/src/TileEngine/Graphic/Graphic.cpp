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
#include "Texture.h"
#include "Font.h"
#include "Camera.h"

using namespace std;

namespace TileEngine {
//
// Default constructor
//
Graphic::Graphic() {
	mIsLoaded = false;
	mWindowTitle = "";
	mSdlFlags = 0;
	mIsFullscreen = false;
	mWidthCurrent = 0;
	mWidthScreen = 0;
	mHeightCurrent = 0;
	mHeightScreen = 0;
}

//
// Default destructor
//
Graphic::~Graphic() {
	Shutdown();
}

//
// Sets up a windows properties
/// must be called before CreateWindow towork properly
/// @param Width a int
/// @param Height a int
/// @param Bpp a int
/// @param WindowTitle a std::string
bool Graphic::Initialize(int Width, int Height, int Bpp,
		std::string WindowTitle) {
	mWidthCurrent = mWidthScreen = Width;
	mHeightCurrent = mHeightScreen = Height;
	mBpp = Bpp;
	//mIsFullscreen = false;
	mSurface = NULL;
	if (WindowTitle != "") {
		mWindowTitle = WindowTitle;
	}
	//if we reinitalize then reload the textures
	if (mIsLoaded) {
		Manager<Texture>::getInstance()->ReloadAllRessource();
	}
	mIsLoaded = MakeWindow();
	glScissor(0, 0, mWidthScreen, mHeightScreen);
	return mIsLoaded;
}

//
// Creates a window from drawing on
/// Intialize must be called first and a window must be created
/// before you can use any drawing functions
/// @return Success or failure
///
bool Graphic::MakeWindow() {
	//initalize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "Unable to initialize SDL: " << SDL_GetError() << endl;
		exit(1);
	}
	if (mSdlFlags == 0) {
		mSdlFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE;
		const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();

		if (videoInfo->hw_available) {
			mSdlFlags |= SDL_HWSURFACE;
		} else {
			mSdlFlags |= SDL_SWSURFACE;
		}

		// This checks if hardware blits can be done
		if (videoInfo->blit_hw) {
			mSdlFlags |= SDL_HWACCEL;
		}
	}
	//| SDL_RESIZABLE;
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
	// Sets up OpenGL double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Anti-aliasing
	if (SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1) == -1) {
		printf("Impossible d'initialiser SDL_GL_MULTISAMPLEBUFFERS à 1\n");
	} else {
		// A-Alias x2 ou x4 ou etc
		if (SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2) == -1) {
			printf("Impossible d'initialiser SDL_GL_MULTISAMPLESAMPLES à 2\n");
		}
	}

	//kill sdl on exiting
	atexit(SDL_Quit);
	//create the surface
	mSurface = SDL_SetVideoMode(mWidthScreen, mHeightScreen, mBpp, mSdlFlags);
	if (mSurface == NULL) {
		cout << "Video mode set failed: " << SDL_GetError() << endl;
		return false;
	}
	InitGl();
	//set the window title
	SDL_WM_SetCaption(mWindowTitle.c_str(), NULL);
	return true;
}

//
// Returns the width of the drawing area
/// @return Width of the drawing area
///
int Graphic::GetWidth() {
	return mWidthCurrent;
}

//
// Returns the height of the drawing area
/// @return Height of the drawing area
///
int Graphic::GetHeight() {
	return mHeightCurrent;
}

void Graphic::SetCaption(string caption) {
	SDL_WM_SetCaption(caption.c_str(), NULL);
}

//
// internal function to setup opengl's othomode
//
void Graphic::InitGl() {
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
	// Anti-Aliasing
	glEnable(GL_MULTISAMPLE);
	//	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
	//	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	//
	//	glEnable(GL_LINE_SMOOTH);
	//	glEnable(GL_POLYGON_SMOOTH);
	//glEnable(GL_SCISSOR_TEST);
	// get view port values
	GLint vPort[4];
	glGetIntegerv(GL_VIEWPORT, vPort);
	//setup ortho mode
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//glOrtho(0, (GLfloat) (m_Width), 0, (GLfloat) (m_Height), -1, 1);
	glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

//
// Turns fullscreen on or off
//
void Graphic::ToggleFullScreen() {
	mIsFullscreen = !mIsFullscreen;
	if (mSurface != NULL) {
		if (SDL_WM_ToggleFullScreen(mSurface)) {
			cout << "SDL_WM_ToggleFullScreen OK" << endl;
		} else {
			cout
					<< "SDL_WM_ToggleFullScreen NOT WORKING, trying with flag SDL_FULLSCREEN"
					<< endl;

			// trying with the SDL_FULLSCREEN flag
			//uint32_t flags = mSurface->flags; /* Save the current flags in case toggling fails */
			mSdlFlags = mSdlFlags ^ SDL_FULLSCREEN;
			if (mIsFullscreen) {
				cout << "toggle Fullscreen: mIsFullscreen = " << mIsFullscreen
						<< endl;
				mSurface = SDL_SetVideoMode(FULL_SCREEN_WIDTH,
						FULL_SCREEN_HEIGHT, 0, mSdlFlags);
			} else {
				cout << "toggle Screen Mode: mIsFullscreen = " << mIsFullscreen
						<< endl;
				mSurface = SDL_SetVideoMode(mWidthScreen, mHeightScreen, mBpp,
						mSdlFlags); /*Toggles Screen Mode */
			}

			// if toggling to fullscreen or screen have screwed up
			if (mSurface == NULL) {
				cout << "Flag NOT WORKING, switching back" << endl;
				// toggle back
				mSdlFlags = mSdlFlags ^ SDL_FULLSCREEN;
				mSurface = SDL_SetVideoMode(0, 0, 0, mSdlFlags); /* If toggle FullScreen failed, then switch back */
			}
			if (mSurface == NULL) {
				cout << "Switching Back ERROR, exit(1)" << endl;
				exit(1); /* If you can't switch back for some reason, then epic fail */
			}

			if (mIsFullscreen) {
				mWidthCurrent = FULL_SCREEN_WIDTH;
				mHeightCurrent = FULL_SCREEN_HEIGHT;
			} else {
				mWidthCurrent = mWidthScreen;
				mHeightCurrent = mHeightScreen;
			}

		}

		Reload(); // reload the ressource

		// to hide the cursor
//		if (!_isFullscreen) {
//			SDL_ShowCursor(SDL_ENABLE);
//		} else {
//			SDL_ShowCursor(SDL_DISABLE);
//		}
	}
}

//
// Resizes the window to the given size
/// @param width a int
/// @param height a int
///
bool Graphic::ResizeWindow(int width, int height) {
	cout << "Window is being resized" << endl;
	// Protect against a divide by zero
	if (height == 0) {
		height = 1;
	}
	//resize sdl surface
	mSurface = SDL_SetVideoMode(width, height, mBpp, mSdlFlags);
	if (mSurface == NULL) {
		cout << "Could not get a surface after resize: " << SDL_GetError()
				<< endl;
		return false;
	}
	//reinitalize opengl
	InitGl();
	//reload textures
	Manager<Texture>::getInstance()->ReloadAllRessource();
	return true;
}

void Graphic::Reload() {
	InitGl();
	Manager<Texture>::getInstance()->ReloadAllRessource();
	Manager<Font>::getInstance()->ReloadAllRessource();
}

void Graphic::InitialiseDraw(float x, float y, float scale, bool isStatic) {
	glPushMatrix();
	//
	//	if (mCurrentTexture == mLastTexture) {
	//		//bind texture
	//		glBindTexture(GL_TEXTURE_2D, mCurrentTexture);
	//	}
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_MULTISAMPLE);
	glLoadIdentity();
	if (!isStatic) {
		x += Camera::getInstance()->GetX();
		y += Camera::getInstance()->GetY();
	}
	glTranslatef(x, y, 0.0f);
	glScaled(scale, scale, 0);
}

void Graphic::ResetDraw() {
	glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
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
void Graphic::DrawRectangle(float x, float y, float width, float height,
		float red, float green, float blue, float alpha, float thickness,
		bool isStatic) {
	//
	InitialiseDraw(x, y, 1, isStatic);
	if (thickness > 0) {
		glLineWidth(thickness);
	}
	//GLfloat thicknessOffset = thickness/2;
	glColor4f(red, green, blue, alpha);
	glBegin(GL_LINE_LOOP);
	//	glVertex2f(x, y);
	//	glVertex2f(x + width, y);
	//	glVertex2f(x + width, y + height);
	//	glVertex2f(x, y + height);
	glVertex2f(0, 0);
	glVertex2f(width, 0);
	glVertex2f(width, height);
	glVertex2f(0, height);
	glEnd();
	ResetDraw();
}

//
// Draws an empty Rectangle
/// @param rect a SectionRect*
/// @param color a Color3f*
/// @param alpha a GLfloat
/// @param thickness a GLfloat
/// @param isStatic a Bool
///
void Graphic::DrawRectangle(SectionRect *rect, Color3f *color, float alpha,
		float thickness, bool isStatic) {
	InitialiseDraw(rect->x, rect->y, 1, isStatic);
	if (thickness > 0) {
		glLineWidth(thickness);
	}
	//GLfloat thicknessOffset = thickness/2;
	glColor4f(color->r, color->g, color->b, alpha);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0, 0);
	glVertex2f(rect->w, 0);
	glVertex2f(rect->w, rect->h);
	glVertex2f(0, rect->h);
	glEnd();
	ResetDraw();
}

//
// Draws an filled rectangle
/// @param rect a SectionRect*
/// @param color a Color3f*
/// @param alpha a GLfloat
/// @param thickness a GLfloat
/// @param isStatic a Bool
///
void Graphic::DrawFilledRectangle(SectionRect *rect, Color3f *color,
		float alpha, bool isStatic) {
	InitialiseDraw(rect->x, rect->y, 1, isStatic);
	glColor4f(color->r, color->g, color->b, alpha);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(rect->w, 0);
	glVertex2f(rect->w, rect->h);
	glVertex2f(0, rect->h);
	glEnd();
	ResetDraw();
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
void Graphic::DrawFilledRectangle(float x, float y, float width, float height,
		float red, float green, float blue, float alpha, bool isStatic) {
	InitialiseDraw(x, y, 1, isStatic);
	glColor4f(red, green, blue, alpha);
	//	glBegin(GL_QUADS);
	//	glVertex3f(x, y, 0);
	//	glVertex3f(x + width, y, 0);
	//	glVertex3f(x + width, y + height, 0);
	//	glVertex3f(x, y + height, 0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(width, 0);
	glVertex2f(width, height);
	glVertex2f(0, height);
	glEnd();
	ResetDraw();
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
void Graphic::DrawLine(float x, float y, float x2, float y2, float red,
		float green, float blue, float alpha, float thickness, bool isStatic) {
	InitialiseDraw(x, y, 1, isStatic);
	if (thickness > 0) {
		glLineWidth(thickness);
	}
	glColor4f(red, green, blue, alpha);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(x2 - x, y2 - y);
	glEnd();
	ResetDraw();
}

//
// clears the screen with a grey color
//
void Graphic::ClearScreen() {
	//SetCurrentTexture(-1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * Flush the buffers so all the data is sent
 * to the graphic device.
 * Note: this returns imediatly.
 */
void Graphic::FlushBuffers() {
	glFlush();
}

//
// Flips the screen from the backbuffer to the screen
//
void Graphic::FlipBuffers() {
	//glFlush();
	SDL_GL_SwapBuffers();
}

//
// Kills all graphic subsystems
//
void Graphic::Shutdown() {
	//SDL_quit cleans up the video surface
	SDL_Quit();
}

//
// returns the current texture in memory
/// @return the current texture
///
GLuint Graphic::GetCurrentTexture() {
	return mCurrentTexture;
}

//
// set the current texture in memory
/// @param texture a Gluint
///
void Graphic::SetCurrentTexture(GLuint texture) {
	mCurrentTexture = texture;
}

void Graphic::EnableClipping() {
	glEnable(GL_SCISSOR_TEST);
	//set scissor to the current area
	Rectangle area;
	if (mClippingArea.empty()) {
		area.y1 = 0.0f;
		area.y2 = (float) ((mHeightScreen));
		area.x1 = 0.0f;
		area.x2 = (float) ((mWidthScreen));
	} else {
		area = mClippingArea.top();
	}
	glScissor((GLsizei) ((area.x1)), (GLsizei) ((area.y1)), (GLint) ((area.x2)),
			(GLint) ((area.y2)));
}

void Graphic::DisableClipping() {
	glDisable(GL_SCISSOR_TEST);
}

//
// Pushes a clipping area on the stack for drawing
/// @param area a sRect
///
void Graphic::PushClippingArea(Rectangle area) {
	Rectangle newArea;
	Rectangle currentArea;
	//get the current clipping area
	if (!mClippingArea.empty()) {
		currentArea = mClippingArea.top();
	} else {
		currentArea.y1 = 0.0f;
		currentArea.y2 = (float) ((mHeightScreen));
		currentArea.x1 = 0.0f;
		currentArea.x2 = (float) ((mWidthScreen));
	}
	//make the new clipping area from the rectangle intersection
	//bottom
	if (currentArea.y1 > area.y1) {
		newArea.y1 = currentArea.y1;
	} else {
		newArea.y1 = area.y1;
	}
	//top
	if ((currentArea.y1 + currentArea.y2) < (area.y1 + area.y2)) {
		newArea.y2 = (currentArea.y1 + currentArea.y2) - newArea.y1;
	} else {
		newArea.y2 = (area.y1 + area.y2) - newArea.y1;
	}
	//left
	if (currentArea.x1 > area.x1) {
		newArea.x1 = currentArea.x1;
	} else {
		newArea.x1 = area.x1;
	}
	//right
	if ((currentArea.x1 + currentArea.x2) < (area.x1 + area.x2)) {
		newArea.x2 = (currentArea.x1 + currentArea.x2) - newArea.x1;
	} else {
		newArea.x2 = (area.x1 + area.x2) - newArea.x1;
	}
	mClippingArea.push(newArea);
	glScissor((GLsizei) ((newArea.x1)), (GLsizei) ((newArea.y1)),
			(GLint) ((newArea.x2)), (GLint) ((newArea.y2)));
}

void Graphic::PopClippingArea() {
	Rectangle newArea;
	mClippingArea.pop();
	if (mClippingArea.empty()) {
		newArea.y1 = 0.0f;
		newArea.y2 = (float) ((mHeightScreen));
		newArea.x1 = 0.0f;
		newArea.x2 = (float) ((mWidthScreen));
	} else {
		newArea = mClippingArea.top();
	}
	glScissor((GLsizei) ((newArea.x1)), (GLsizei) ((newArea.y1)),
			(GLint) ((newArea.x2)), (GLint) ((newArea.y2)));
}
}
