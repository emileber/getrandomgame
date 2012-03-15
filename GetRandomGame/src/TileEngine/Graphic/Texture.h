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

class Texture: public Ressource {
	friend class TextureManager;
public:
	/// Default Constructor
	Texture();
	/// Constructor that loads a texture
	Texture(std::string filename);
	/// Default Destructor
	virtual ~Texture();

	void Init();

	/// Returns the texture width
	float GetWidth() const {
		return mWidth;
	}
	/// Returns the texture height
	float GetHeight() const {
		return mHeight;
	}

	// return the OpenGL id for that texture
	float GetId() const {
		return mTexture;
	}

	// Set if it moves with the camera or not
	void SetStatic(bool isBound) {
		mIsStatic = isBound;
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
	void Draw(float x, float y, float scale = 1, float rotation = 0, float red =
			1, float green = 1, float blue = 1, float alpha = 1);

	/// Draws a section of the texture
	void DrawSection(float x, float y, const SectionRect* box, float scale = 1,
			float rotation = 0, float red = 1, float green = 1, float blue = 1,
			float alpha = 1);

	void DrawSection4Color(float x, float y, const SectionRect* box,
			Color3f * bottomLeftColor, Color3f * bottomRightColor,
			Color3f * topRightColor, Color3f * topLeftColor, float scale = 1,
			float rotation = 0, float alpha = 1);

protected:
	/// Internal function to setup drawing
	void InitializeDraw(float scale, float rotation, float x, float y,
			const SectionRect* rect);

	/// Internal function for loading a texture from a surface
	void MakeTexture(SDL_Surface* surface);

	GLuint mTexture; /**< Holds the texture data */
	SDL_Surface * mSurface;
	std::vector<std::vector<bool> > mPixelOn; /**< Holds the pixel data, if a pixel is not transparent it is on */
	float mWidth; /**< Stores the width of the texture */
	float mHeight; /**< Stores the height of the texture	*/
	bool mIsStatic; // if it moves with the camera
};

} /* namespace TileEngine */
#endif /* TEXTURE_H_ */
