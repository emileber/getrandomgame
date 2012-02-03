/**
 *  File: cGraphics.h
 *  Project: Kore-Engine
 *
 *  Description: This file contains handles all the graphic subsystems and
 *		basic window management.
 *
 *  Created by Sean Chapel on 1/21/06.
 *  Copyright 2006 Seoushi Games. All rights reserved.
 *
 */

#include "Global.h"
#include "GraphicType.h"

#ifndef GRAPHIC
#define GRAPHIC

namespace TileEngine
{
	///
	/// A class to contain all graphic subsystems
	///
	class Graphic: public Singleton<Graphic>
	{
		friend class Singleton<Graphic>;
		//friend class cTextureManager;

		public:
			/// Default Constructor
			Graphic();
			/// Default Destructor
			~Graphic();

			/// Intializes all a window for creation
			bool initialize(int Width = 640, int Height = 480, int Bpp = 32, std::string WindowTitle = "");
			/// kills all graphic subsystems
			void shutdown();

			/// Clears the screen with a grey color
			void clearScreen();
			/// Flips backbuffer to the screen
			void flipBuffers();

			/// Creates a window for drawing
			bool makeWindow();

			/// Resizes the window
			void resizeWindow(int width, int height);
			/// Toggles if the window is fullscreen or not
			void toggleFullScreen();

			/// Returns the width of the drawing area
			int getWidth();

			/// Returns the height of the drawing area
			int getHeight();

            /// Draws an empty Rectangle
			void drawRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0, GLfloat alpha = 1);

			/// Draws an filled rectangle
			void drawFilledRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0, GLfloat alpha = 1);

			/// Draws a line
			void drawLine(GLfloat x, GLfloat y, GLfloat x2, GLfloat y2, GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0, GLfloat alpha = 1);

			/// returns the current texture in memory
			GLuint getCurrentTexture();

			/// Set the current texture in memory
			void setCurrentTexture(GLuint texture);

			void setCaption(std::string caption);

			/// Pushes a clipping area on the stack for drawing
			void pushClippingArea(sRect);

			/// Pops a clipping area off the stack
			void popClippingArea();

		protected:
			/// intializes opengl for 2d drawing
			void initGl();

			bool m_Loaded;			/**< Tells if the graphics core was successfully loaded	*/
			int m_Width;			/**< Stores the width of the drawing area		*/
			int m_Height;			/**< Stores the height of the drawing area		*/
			int m_Bpp;			/**< Stores the bits per pixel of the screen		*/
			std::string m_WindowTitle;	/**< Stores the title of the window			*/
			bool m_FullScreen;		/**< Tells if the window id fullscreen or not		*/

			SDL_Surface* m_Surface;		/**< Stores the drawing surface				*/
			Uint32 m_SdlFlags;		/**< Stores the drawing surface's capabilities		*/

			GLuint m_CurrentTexture; 	/**< contains the current texture that is in graphics memory	*/

			std::stack< sRect > m_ClippingArea;
	};
}

#endif
