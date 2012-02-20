/*
 * Texture.h
 *
 *  Created on: 2012-01-23
 *      Author: Emile
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
	GLfloat getWidth() const {
		return _Width;
	}
	/// Returns the texture height
	GLfloat getHeight() const {
		return _Height;
	}

	// return the OpenGL id for that texture
	GLfloat getId() const {
		return _Texture;
	}

	/// Loads a texture
	virtual void load(std::string filename);

	/// Reloads the texture
	//virtual void reload();

	/// Deletes the texture
	void kill();


	/// Returns the pixel data
	std::vector<std::vector<bool> >* getPixels();

	/// Draws the whole texture
	void draw(GLfloat x, GLfloat y, GLfloat scale = 1, GLfloat rotation = 0,
			GLfloat red = 1, GLfloat green = 1, GLfloat blue = 1,
			GLfloat alpha = 1);

	/// Draws a section of the texture
	void drawSection(GLfloat x, GLfloat y, SectionRect* box,
			GLfloat scale = 1, GLfloat rotation = 0, GLfloat red = 1,
			GLfloat green = 1, GLfloat blue = 1, GLfloat alpha = 1);

protected:
	/// Internal function to setup drawing
	void initializeDraw(GLfloat scale, GLfloat rotation, GLfloat x, GLfloat y,
			SectionRect* rect);

	/// Internal function for loading a texture from a surface
	void makeTexture(SDL_Surface* surface);

	GLuint _Texture; /**< Holds the texture data */
	SDL_Surface * _Surface;
	std::vector<std::vector<bool> > _PixelOn; /**< Holds the pixel data, if a pixel is not transparent it is on */
	GLfloat _Width; /**< Stores the width of the texture */
	GLfloat _Height; /**< Stores the height of the texture	*/
};

} /* namespace TileEngine */
#endif /* TEXTURE_H_ */
