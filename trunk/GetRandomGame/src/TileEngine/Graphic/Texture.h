/*
 * Texture.h
 *
 *  Created on: 2012-01-23
 *      Author: Emile
 *
 *      IMPORTANT: image width and height MUST be
 *                 a power of 2. (64x256, 64x64, 128x256, etc)
 *
 *      Load an image into an SDL_Surface, then make
 *      an OpenGL texture out of it. Provides a Draw function.
 *
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "Global.h"
#include "GraphicType.h"
#include "Ressource.h"
#include <vector>

namespace TileEngine {

class Texture : public Ressource{
	friend class TextureManager;
public:
	/// Default Constructor
	Texture();
	/// Constructor that loads a texture
	Texture(std::string filename);
	/// Default Destructor
	virtual ~Texture();

	/// Returns the texture width
	GLfloat GetWidth() const {
		return mWidth;
	}
	/// Returns the texture height
	GLfloat GetHeight() const {
		return mHeight;
	}

	// return the OpenGL id for that texture
	GLfloat GetId() const {
		return mTexture;
	}

	/// Loads a texture
	virtual void Load(std::string filename);

	/// Reloads the texture
	//virtual void reload();

	/// Deletes the texture
	void Kill();


	/// Returns the pixel data
	std::vector<std::vector<bool> >* GetPixels();

	/// Draws the whole texture
	void Draw(GLfloat x, GLfloat y, GLfloat scale = 1, GLfloat rotation = 0,
			GLfloat red = 1, GLfloat green = 1, GLfloat blue = 1,
			GLfloat alpha = 1);

	/// Draws a section of the texture
	void DrawSection(GLfloat x, GLfloat y, SectionRect* box,
			GLfloat scale = 1, GLfloat rotation = 0, GLfloat red = 1,
			GLfloat green = 1, GLfloat blue = 1, GLfloat alpha = 1);

protected:
	/// Internal function to setup drawing
	void InitializeDraw(GLfloat scale, GLfloat rotation, GLfloat x, GLfloat y,
			SectionRect* rect);

	/// Internal function for loading a texture from a surface
	void MakeTexture(SDL_Surface* surface);

	GLuint mTexture; /**< Holds the texture data */
	SDL_Surface * mSurface;
	std::vector<std::vector<bool> > mPixelOn; /**< Holds the pixel data, if a pixel is not transparent it is on */
	GLfloat mWidth; /**< Stores the width of the texture */
	GLfloat mHeight; /**< Stores the height of the texture	*/
};

} /* namespace TileEngine */
#endif /* TEXTURE_H_ */
