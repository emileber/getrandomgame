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
	GLfloat getWidth();
	/// Returns the texture height
	GLfloat getHeight();

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
	void drawSection(GLfloat x, GLfloat y, SectionStruct* box, GLfloat scale = 1,
			GLfloat rotation = 0, GLfloat red = 1, GLfloat green = 1,
			GLfloat blue = 1, GLfloat alpha = 1);

protected:
	/// Internal function to setup drawing
	void initializeDraw(GLfloat scale, GLfloat rotation, GLfloat x, GLfloat y,
			SectionStruct* rect);

	/// Internal function for loading a texture from a surface
	void makeTexture(SDL_Surface* surface, bool LoadCollision);
	void cleanup(); // delete the texture before loading it.

	GLuint m_Texture; /**< Holds the texture data */
	std::vector<std::vector<bool> > m_PixelOn; /**< Holds the pixel data, if a pixel is not transparent it is on */
	std::string m_Filename; /**< Holds the filename of the texture */
	GLfloat m_Width; /**< Stores the width of the texture */
	GLfloat m_Height; /**< Stores the height of the texture	*/
};

/*
 *
 */
class TextureManager: public Singleton<TextureManager> {
	friend class Singleton<TextureManager> ;
public:
	TextureManager();
	virtual ~TextureManager();

	Texture * loadTextureFromFile(std::string filename);

	//void removeTexture(uint textureId);

	//void drawTexture(uint textureId, GLfloat x, GLfloat y, GLfloat scale = 1,
	//            GLfloat rotation = 0, GLfloat red = 1, GLfloat green = 1, GLfloat blue = 1);

	/// Reloads all textures
	void ReloadTextures();
	/// Deletes all textures
	void DeleteTextures();

	/// Registers a texture for management
	void RegisterTexture(Texture* Texture);
	/// Removes a texture from management
	void UnRegisterTexture(Texture* Texture);

protected:

	std::vector< Texture* > m_Textures; /**< Holds all textures that are managed	*/
	//std::map< uint, TextureSection* > m_TextureSections;
};

} /* namespace TileEngine */
#endif /* TEXTUREMANAGER_H_ */
