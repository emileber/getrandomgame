/*
 * TextureManager.h
 *
 *  Created on: 2012-01-30
 *      Author: Emile
 */

#ifndef TEXTURES
#define TEXTURES

#include "Global.h"
#include "GraphicType.h"

namespace TileEngine {

class Texture {
	friend class TextureManager;
public:
	/// Default Constructor
	Texture();
	/// Constructor that loads a texture
	Texture(std::string filename);
	/// Default Destructor
	~Texture();

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

	bool isLoaded() const{
		return _isLoaded;
	}

	/// Loads a texture
	void load(std::string filename, bool LoadCollision = false);

	/// Loads file from a zip file
	void loadFromZip(std::string filename);

	/// Deletes the texture
	void deleteTexture();
	/// Reloads the texture
	void reload();

	/// Returns the pixel data
	std::vector<std::vector<bool> >* getPixels();

	/// Draws the whole texture
	void draw(GLfloat x, GLfloat y, GLfloat scale = 1, GLfloat rotation = 0,
			GLfloat red = 1, GLfloat green = 1, GLfloat blue = 1,
			GLfloat alpha = 1);

	/// Draws a section of the texture
	void drawSection(GLfloat x, GLfloat y, SectionStruct* box,
			GLfloat scale = 1, GLfloat rotation = 0, GLfloat red = 1,
			GLfloat green = 1, GLfloat blue = 1, GLfloat alpha = 1);

protected:
	/// Internal function to setup drawing
	void initializeDraw(GLfloat scale, GLfloat rotation, GLfloat x, GLfloat y,
			SectionStruct* rect);

	/// Internal function for loading a texture from a surface
	void makeTexture(SDL_Surface* surface, bool LoadCollision);
	void cleanup(); // delete the texture before loading it.

	GLuint _Texture; /**< Holds the texture data */
	SDL_Surface * _Surface;
	std::vector<std::vector<bool> > _PixelOn; /**< Holds the pixel data, if a pixel is not transparent it is on */
	std::string _Filename; /**< Holds the filename of the texture */
	GLfloat _Width; /**< Stores the width of the texture */
	GLfloat _Height; /**< Stores the height of the texture	*/
	bool _isLoaded;
};

/*
 *
 */
class TextureManager: public Singleton<TextureManager> {
	friend class Singleton<TextureManager> ;
public:
	TextureManager();
	virtual ~TextureManager();

	bool loadTextureFromFile(std::string filename);

	//void removeTexture(uint textureId);

	void drawTexture(std::string textureId, GLfloat x, GLfloat y, SectionStruct * rect = NULL, GLfloat scale = 1,
	            GLfloat rotation = 0, GLfloat red = 1, GLfloat green = 1, GLfloat blue = 1);

	/// Reloads all textures
	void reloadTextures();
	/// Deletes all textures
	void deleteTextures();

	/// Registers a texture for management
	void registerTexture(Texture* Texture);
	/// Removes a texture from management
	void unRegisterTexture(Texture* Texture);

protected:

	std::vector<Texture*> m_Textures; /**< Holds all textures that are managed	*/
	//std::map< std::string, TextureSection* > m_TextureSections;
};

} /* namespace TileEngine */
#endif /* TEXTUREMANAGER_H_ */
