/*
 * Graphic.h
 *
 *  Created on: 2012-01-25
 *      Author: Emile
 *
 *      Handles windowing and basic graphic functions
 */

#ifndef GRAPHIC
#define GRAPHIC

#include "Global.h"
#include "GraphicType.h"
#include <stack>
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
	/// Flips backbuffer to the screen
	void FlipBuffers();

	/// Creates a window for drawing
	bool MakeWindow();

	/// Resizes the window
	bool ResizeWindow(int width, int height);
	/// Toggles if the window is fullscreen or not
	void ToggleFullScreen();

	/// Use when toggling fullscreen
	void Reload();

	/// Returns the width of the drawing area
	int GetWidth();

	/// Returns the height of the drawing area
	int GetHeight();

	/// Draws an empty Rectangle
	void DrawRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height,
			GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0,
			GLfloat alpha = 1, GLfloat thickness = 1, bool isStatic = false);

	void DrawRectangle(SectionRect* rect, Color3f* color, GLfloat alpha = 1, GLfloat thickness = 1, bool isStatic = false);

	/// Draws an filled rectangle
	void DrawFilledRectangle(GLfloat x, GLfloat y, GLfloat width,
			GLfloat height, GLfloat red = 0, GLfloat green = 0,
			GLfloat blue = 0, GLfloat alpha = 1, bool isStatic = false);

	void DrawFilledRectangle(SectionRect* rect, Color3f* color, GLfloat alpha = 1, bool isStatic = false);



	/// Draws a line
	void DrawLine(GLfloat x, GLfloat y, GLfloat x2, GLfloat y2, GLfloat red = 0,
			GLfloat green = 0, GLfloat blue = 0, GLfloat alpha = 1,
			GLfloat thickness = 1, bool isStatic = false);

	/// returns the current texture in memory
	GLuint GetCurrentTexture();

	/// Set the current texture in memory
	void SetCurrentTexture(GLuint texture);

	void ResetDraw();

	void SetCaption(std::string caption);

	void EnableClipping();

	void DisableClipping();

	/// Pushes a clipping area on the stack for drawing
	void PushClippingArea(Rectangle);

	/// Pops a clipping area off the stack
	void PopClippingArea();

	bool isFullScreen() const {
		return mIsFullscreen;
	}

protected:
	/// intializes opengl for 2d drawing
	void InitGl();
	void InitialiseDraw(GLfloat x, GLfloat y, GLfloat scale, bool isStatic);

	bool mIsLoaded; /**< Tells if the graphics core was successfully loaded	*/
	int mWidthScreen; /**< Stores the width of the drawing area		*/
	int mHeightScreen; /**< Stores the height of the drawing area		*/
	int mWidthCurrent, mHeightCurrent; // current screen size
	int mBpp; /**< Stores the bits per pixel of the screen		*/
	std::string mWindowTitle; /**< Stores the title of the window			*/
	bool mIsFullscreen; /**< Tells if the window id fullscreen or not		*/

	SDL_Surface* mSurface; /**< Stores the drawing surface				*/
	Uint32 mSdlFlags; /**< Stores the drawing surface's capabilities		*/

	GLuint mCurrentTexture; /**< contains the current texture that is in graphics memory	*/
	GLuint mLastTexture;

	std::stack<Rectangle> mClippingArea;

	/// Default Constructor
	Graphic();
	/// Default Destructor
	~Graphic();
};
}

#endif
