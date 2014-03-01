#ifndef __GL_TEXTURE_
#define __GL_TEXTURE_

#include "ofConstants.h"
#include "ofGraphics.h"
#include "ofTexture.h"
#include "GLState.h"

class GLTextureParameters
{
public:
	GLuint target;		//GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_RECTANGLE_ARB, 
	GLuint format;		//GL_RGBA, GL_RGBA16F_ARB, GL_RGBA32F_ARB;
	GLuint type;		//GL_FLOAT, GL_UNSIGNEDINT;
	GLuint minFilter;	//GL_NEAREST, GL_LINEAR
	GLuint magFilter;	//GL_NEAREST, GL_LINEAR
	
	GLTextureParameters()
	{
		type= GL_UNSIGNED_BYTE;
		target = GL_TEXTURE_RECTANGLE_ARB;
		format = GL_RGBA;
		minFilter = GL_LINEAR;
		magFilter = GL_LINEAR;
	};

	void setupForGPGPU(bool use32bitFloatingPoint=false)
	{
		target = GL_TEXTURE_RECTANGLE_ARB;
		type= GL_FLOAT;
		format = (use32bitFloatingPoint) ? GL_RGBA32F_ARB: GL_RGBA16F_ARB;
		//format = GL_RGBA32F_ARB;

		//format = GL_RGBA;
		minFilter = GL_NEAREST;
		magFilter = GL_NEAREST;
	};
};


class GLTexture 
{
public:
	GLuint tex[1]; 
	GLuint texTarget;	
	GLuint texInternalFormat;
    GLuint minFilter;	
    GLuint magFilter;
	GLuint type;
    int width;
    int height;
	

	GLTexture();
	void initFromOFTexture(ofTexture &texture);
	void init(int width, int height);
	void init(int width, int height, GLTextureParameters &params);
	void bind();
	void initTexture(int w, int h);
	void setTextureParams(GLTextureParameters &params);
	void releaseTexture();   
	
	GLuint getTextureID();
	GLuint getTextureTarget();
	float getMaxTextureCoordS();
	float getMaxTextureCoordT();

	///////////////////////////
	
	void render();
	void render(float x, float y, float w, float h);
	void render(float x, float y, float w, float h, float sx, float ty, float sw, float th);

	//////////////////////////

	void putBuffer(float *floatArray);
	void getBuffer(float *floatArray);
	void putBuffer(float* floatArray, int format);
	void getBuffer(float *floatArray, int format);   
};

#endif


