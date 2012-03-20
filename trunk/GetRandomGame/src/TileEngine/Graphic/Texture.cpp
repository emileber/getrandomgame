/*
 * Texture.cpp
 *
 *  Created on: 2012-01-23
 *      Author: Emile
 */

#include "Texture.h"
#include "Graphic.h"
#include "Camera.h"
#include "GraphicType.h"
#include "SdlInterface.h"

using namespace std;

namespace TileEngine {
//
// Default contructor
//
Texture::Texture() {
	Init();
}

//
// Constructor that loads a file
/// @param Filename a std::string
Texture::Texture(std::string Filename) {
	Init();
	Load(Filename);
}

//
// Default destructor
//
Texture::~Texture() {
	Kill();
}

void Texture::Init() {
	mWidth = 0;
	mHeight = 0;
	mTexture = 0;
	mSurface = NULL;
	mFilename = "";
	mIsStatic = false;
	mIsLoaded = false;
}

//
// Loads the texture to memory
/// @param filename a std::string
///
void Texture::Load(std::string filename) {
	//cout << "load " << filename << endl;
	//load the image from a file via sdl_img
	//SDL_Surface* surface = IMG_Load(filename.c_str());

	SDL_Surface* surface = NULL;

	surface = SdlInterface::getInstance()->LoadImage(filename);

	if (surface == NULL) {
		cout << "Failed to load the image: " << filename << ", Error: "
				<< SDL_GetError() << endl;
		mIsLoaded = false;
		return;
	}

	mFilename = filename; // Ressource filename

	//mSurface = surface;
	mSurface = SDL_DisplayFormatAlpha(surface);

	MakeTexture(mSurface);
	mIsLoaded = true; // Ressource loaded
}

//
// Internal function for loading a texture from a surface
/// @param Surface a SDL_Surface pointer
///
void Texture::MakeTexture(SDL_Surface *surface) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_PixelFormat *fmt = surface->format;
	//setup all the information
	mWidth = (float) ((surface->w));
	mHeight = (float) ((surface->h));
	//setup the pixel data (used for collisions)
//	if (LoadCollision) {
//		SDL_LockSurface(Surface);
//		Uint32 *sur_pixels = (Uint32*) (Surface->pixels);
//		Uint32 pixel;
//		SDL_UnlockSurface(Surface);
//		SDL_PixelFormat *format = Surface->format;
//		Uint32 temp;
//		Uint8 alpha;
//		std::vector<bool> pixTemp;
//		for (int x = 0; x < (int) (_Width); x++) {
//			pixTemp.push_back(false);
//		}
//		for (int y = 0; y < (int) (_Height); y++) {
//			_PixelOn.push_back(pixTemp);
//		}
//		pixel = *(sur_pixels++);
//		for (int y = 0; y < (int) (_Height); y++) {
//			for (int x = 0; x < (int) (_Width); x++) {
//				temp = pixel & format->Amask;
//				temp = temp >> fmt->Ashift;
//				temp = temp << fmt->Aloss;
//				alpha = (Uint8) (temp);
//				if (alpha >= 200) {
//					_PixelOn[y][x] = true;
//				}
//				pixel = *(sur_pixels++);
//			}
//
//		}
//
//		//flip rows so it's represented right in memory
//		vector<vector<bool> > colTmp;
//		for (int y = _Height - 1; y >= 0; y--) {
//			colTmp.push_back(_PixelOn[y]);
//		}
//		_PixelOn.clear();
//		_PixelOn = colTmp;
//	}

	//if there is alpha
	if (fmt->Amask) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, mWidth, mHeight, GL_BGRA,
				GL_UNSIGNED_BYTE, surface->pixels);
	} else // no alpha
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, mWidth, mHeight, GL_RGB,
				GL_UNSIGNED_BYTE, surface->pixels);
	}
	//TextureManager::getInstance()->registerTexture(this);

	mIsLoaded = true; // Ressource loaded

}

//
// Deletes the texture
//
void Texture::Kill() {
	if (mIsLoaded) {
		glDeleteTextures(1, &mTexture);
		SDL_FreeSurface(mSurface);
	}
}

//
// Reloads the texture
//
//void Texture::reload() {
//	//only reload if it's a real file
//	if (_filename != "") {
//		load(_filename);
//	}
//}

//
// Moves the camera, binds the texture if nessiary and does scaling/rotation
/// @param Scale a GLfloat
/// @param Rotation a GLfloat
/// @param X a GLfloat
/// @param Y a GLfloat
///
void Texture::InitializeDraw(float scale, float rotation, float x, float y,
		const SectionRect *rect) const {
	Graphic *graphics = Graphic::getInstance();
	//check if the right texture is bound
	if (graphics->GetCurrentTexture() != mTexture) {
		//bind texture
		glBindTexture(GL_TEXTURE_2D, mTexture);

		//set graphics varible
		graphics->SetCurrentTexture(mTexture);
	}
	//scale the points if needed
	glLoadIdentity();

	if (!mIsStatic) {
		x = Camera::getInstance()->GetX() + x;
		y = Camera::getInstance()->GetY() + y;
	}
	glTranslatef(x, y, 0.0f);

//	if (rotation != 0) {
//		GLfloat x, y;
//		x = ((rect->right - rect->left) / 2) * m_Width;
//		y = ((rect->top - rect->bottom) / 2) * m_Height;
//		glTranslatef(x, y, 0.0f);
//		glRotatef(rotation, 0.0f, 0.0f, 1.0f);
//		glTranslatef(-x, -y, 0.0f);
//	}
	glScaled(scale, scale, 0);
}

//
/// Returns the pixel data
/// @return
///
std::vector<std::vector<bool> > *Texture::GetPixels() {
	return &mPixelOn;
}

//
// Draws the whole texture
/// @param X a GLfloat
/// @param Y a GLfloat
/// @param Scale a GLfloat
/// @param Rotation a GLfloat
/// @param red a GLfloat
/// @param green a GLfloat
/// @param blue a GLfloat
/// @param alpha a GLfloat
///
void Texture::Draw(float x, float y, float scale, float rotation, float red,
		float green, float blue, float alpha) const {
	glPushMatrix();
//	RectStruct rect;
//	rect.bottom = 0.0f;
//	rect.top = 1.0f;
//	rect.right = 1.0f;
//	rect.left = 0.0f;
	InitializeDraw(scale, rotation, x, y, NULL);

	glColor4f(red, green, blue, alpha);

	//draw the quad
	glBegin(GL_QUADS);

	//bottom-left vertex (corner)
	glTexCoord2f(0, 0);
	glVertex2f(0, mHeight);
	//bottom-right vertex (corner)
	glTexCoord2f(1, 0);
	glVertex2f(mWidth, mHeight);
	//top-right vertex (corner)
	glTexCoord2f(1, 1);
	glVertex2f(mWidth, 0);
	//top-left vertex (corner)
	glTexCoord2f(0, 1);
	glVertex2f(0, 0);

	glEnd();

	glPopMatrix();
	//reset the color
	glColor3f(1.0f, 1.0f, 1.0f);
}

//
// Draws a section of a texture
/// @param X a GLfloat
/// @param Y a GLfloat
/// @param Box a sRect pointer
/// @param Scale a GLfloat
/// @param Rotation a GLfloat
/// @param red a GLfloat
/// @param green a GLfloat
/// @param blue a GLfloat
/// @param alpha a GLfloat
///
void Texture::DrawSection(float x, float y, const SectionRect * box,
		float scale, float rotation, float red, float green, float blue,
		float alpha) const {

	if (box == NULL) {
		Draw(x, y, scale, rotation, red, green, blue, alpha);
	}

	glPushMatrix();
	InitializeDraw(scale, rotation, x, y, box);
	//width for drawing
	float box_left = 1.0f * (box->x / mWidth);
	float box_right = 1.0f * ((box->x + box->w) / mWidth);
	float box_top = 1.0f - (1.0f * ((box->y + box->h) / mHeight));
	float box_bottom = 1.0f - (1.0f * (box->y / mHeight));

	glColor4f(red, green, blue, alpha);

	//draw the quad
	glBegin(GL_QUADS);
	//bottom-left vertex (corner)

	glTexCoord2f(box_left, box_bottom);
	glVertex2f(0, 0);
	//bottom-right vertex (corner)
	glTexCoord2f(box_right, box_bottom);
	glVertex2f(box->w, 0);
	//top-right vertex (corner)
	glTexCoord2f(box_right, box_top);
	glVertex2f(box->w, box->h);
	//top-left vertex (corner)
	glTexCoord2f(box_left, box_top);
	glVertex2f(0, box->h);
	glEnd();
	//reset the color
	glColor3f(1.0f, 1.0f, 1.0f);
	glPopMatrix();
}

void Texture::DrawSection4Color(float x, float y, const SectionRect* box,
		const Color3f * bottomLeftColor, const Color3f * bottomRightColor,
		const Color3f * topRightColor, const Color3f * topLeftColor, float scale,
		float rotation, float alpha) const {
	glPushMatrix();
	InitializeDraw(scale, rotation, x, y, box);
	//width for drawing
	float box_left = 1.0f * (box->x / mWidth);
	float box_right = 1.0f * ((box->x + box->w) / mWidth);
	float box_top = 1.0f - (1.0f * ((box->y + box->h) / mHeight));
	float box_bottom = 1.0f - (1.0f * (box->y / mHeight));

	glColor4f(1.0f, 1.0f, 1.0f, alpha);

	//draw the quad
	glBegin(GL_QUADS);
	//bottom-left vertex (corner)
	glColor3f(bottomLeftColor->r, bottomLeftColor->g, bottomLeftColor->b);
	glTexCoord2f(box_left, box_bottom);
	glVertex2f(0, 0);

	//bottom-right vertex (corner)
	glColor3f(bottomRightColor->r, bottomRightColor->g, bottomRightColor->b);
	glTexCoord2f(box_right, box_bottom);
	glVertex2f(box->w, 0);

	//top-right vertex (corner)
	glColor3f(topRightColor->r, topRightColor->g, topRightColor->b);
	glTexCoord2f(box_right, box_top);
	glVertex2f(box->w, box->h);

	//top-left vertex (corner)
	glColor3f(topLeftColor->r, topLeftColor->g, topLeftColor->b);
	glTexCoord2f(box_left, box_top);
	glVertex2f(0, box->h);

	glEnd();

	//reset the color
	glColor3f(1.0f, 1.0f, 1.0f);
	glPopMatrix();

}

} // fin du namespace
