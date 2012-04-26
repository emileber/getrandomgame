/*
 * Graphic.h
 *
 *  Created on: 2012-01-25
 *      Author: Emile
 *
 *      Handles windowing and basic graphic functions
 */
#pragma once
#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <sstream>
#include <stack>
#include <GL/gl.h>
#include "SDL/SDL.h"

#include "Singleton.h"
#include "GraphicType.h"
#include "Rectangle.h"

namespace TileEngine {
///
/// A class to contain all graphic subsystems
///
class Graphic: public Singleton<Graphic> {
	friend class Singleton<Graphic> ;
	//friend class cTextureManager;

public:

	/// Intializes all a window for creation
	bool Initialize(int width = 640, int height = 480, int bpp = 32,
			std::string windowTitle = "");
	/// kills all graphic subsystems
	void Shutdown();

	/// Clears the screen with a grey color
	void ClearScreen();
	/// Clear the buffers (send all the data to the graphic device)
	void FlushBuffers();
	/// Flips backbuffer to the screen
	void FlipBuffers();

	/// Creates a window for drawing
	bool MakeWindow();

	void SetTransparentColor(int, int, int);

	SDL_Surface * LoadImage(std::string);

	/// Resizes the window
	bool ResizeWindow(int width, int height);
	/// Toggles if the window is fullscreen or not
	void ToggleFullScreen();

	/// Use when toggling fullscreen
	void Reload();

	void ToggleBlendMode();

	void DrawLight(float x, float y, float rad, float red, float green,
			float blue, float alpha, bool isStatic);

	/// Draws an empty Rectangle
	void DrawRectangle(float x, float y, float width, float height, float red =
			0, float green = 0, float blue = 0, float alpha = 1,
			float thickness = 1, bool isStatic = false);

	void DrawRectangle(SectionRect* rect, Color3f* color, float alpha = 1,
			float thickness = 1, bool isStatic = false);

	/// Draws an filled rectangle
	void DrawFilledRectangle(float x, float y, float width, float height,
			float red = 0, float green = 0, float blue = 0, float alpha = 1,
			bool isStatic = false);

	void DrawFilledRectangle(SectionRect* rect, Color3f* color, float alpha = 1,
			bool isStatic = false);

	/// Draws a line
	void DrawLine(float x, float y, float x2, float y2, float red = 0,
			float green = 0, float blue = 0, float alpha = 1, float thickness =
					1, bool isStatic = false);

	void SetCaption(std::string caption);

	void EnableClipping();

	void DisableClipping();

	/// Pushes a clipping area on the stack for drawing
	//void PushClippingArea(Rectangle);

	/// Pops a clipping area off the stack
	//void PopClippingArea();

	/// returns the current texture in memory
	GLuint GetCurrentTexture() const {
		return mCurrentTexture;
	}

	/// Set the current texture in memory
	void SetCurrentTexture(GLuint texture) {
		mCurrentTexture = texture;
	}

	/// Returns the width of the drawing area
	int GetWidth() const {
		return mWidthCurrent;
	}

	/// Returns the height of the drawing area
	int GetHeight() const {
		return mHeightCurrent;
	}

	bool IsFullScreen() const {
		return mIsFullscreen;
	}

	/**
	 * NumberToString
	 *  cast any Number base type to string...
	 */
	template<typename T>
	std::string NumberToString(T number) {
		std::stringstream ss; //create a stringstream
		ss << number; //add number to the stream
		return ss.str(); //return a string with the contents of the stream
	}

protected:
	/// intializes opengl for 2d drawing
	void InitGl();
	void ResetDraw();
	void InitialiseDraw(float x, float y, float scale, bool isStatic);

	bool mIsLoaded; /**< Tells if the graphics core was successfully loaded	*/
	int mWidthScreen; /**< Stores the width of the drawing area		*/
	int mHeightScreen; /**< Stores the height of the drawing area		*/
	int mWidthCurrent, mHeightCurrent; // current screen size
	int mBpp; /**< Stores the bits per pixel of the screen		*/
	std::string mWindowTitle; /**< Stores the title of the window			*/
	bool mIsFullscreen; /**< Tells if the window id fullscreen or not		*/
	bool mIsBlendingOverLightmap;

	SDL_Surface* mSurface; /**< Stores the drawing surface				*/
	Uint32 mSdlFlags; /**< Stores the drawing surface's capabilities		*/

	GLuint mCurrentTexture; /**< contains the current texture that is in graphics memory	*/
	GLuint mLastTexture;

	SDL_Color _transColor;

	//std::stack<Rectangle> mClippingArea;

	/// Default Constructor
	Graphic();
	/// Default Destructor
	~Graphic();
};

} // fin du namespace

#endif // GRAPHIC_H_
