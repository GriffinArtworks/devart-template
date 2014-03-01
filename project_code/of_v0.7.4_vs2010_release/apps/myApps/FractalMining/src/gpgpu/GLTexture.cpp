#include "GLTexture.h"
#include "ofUtils.h"		// for nextPow2()

GLTexture::GLTexture()
{      
	tex[0] = 0;
}

void GLTexture::initFromOFTexture(ofTexture &texture)
{
	tex[0] = texture.getTextureData().textureID;
	type = texture.texData.glType;
	texTarget = texture.texData.textureTarget;			//texTarget  GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_RECTANGLE_ARB, 
	texInternalFormat = texture.texData.glTypeInternal;  //GL_RGBA, GL_RGBA16F_ARB, GL_RGBA32F_ARB;
	minFilter = GL_LINEAR;		//GL_NEAREST, GL_LINEAR
	magFilter = GL_LINEAR;		//GL_NEAREST, GL_LINEAR
	width = texture.getWidth();
	height = texture.getHeight();

}

void GLTexture::init(int width, int height)
{	GLTextureParameters params;	init(width, height, params);
}

void GLTexture::init(int width, int height, GLTextureParameters &params)
{
	setTextureParams(params);
    initTexture(width, height);
}

void GLTexture::bind()
{
	glBindTexture(texTarget, tex[0]);
}

void GLTexture::initTexture(int w, int h)
{
	if (tex[0] != 0)
	{
		releaseTexture();
	}
        
    glGenTextures(1, &tex[0]);
	glEnable(texTarget);
    glBindTexture(texTarget, tex[0]);
    glTexParameteri(texTarget, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(texTarget, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(texTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(texTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	if (texTarget == GL_TEXTURE_1D) glTexImage1D(texTarget, 0, texInternalFormat, w, 0, GL_RGBA, type, NULL);
    else glTexImage2D(texTarget, 0, texInternalFormat, w, h, 0, GL_RGBA, type, NULL);
    
	glDisable(texTarget);
    glBindTexture(texTarget, 0);
	

	/*
    if (texTarget == GL_TEXTURE_RECTANGLE_ARB)
    {
		this->maxCoordS = w;
        this->maxCoordT = h;
	}
    else
    {
		this->maxCoordS = 1.0f;
        this->maxCoordT = 1.0f; 
	}*/

	width = w;
	height = h;

	printf("[GLtexture.init] %i, %i\n", width,height);
	GLState::printAnyError();
}
    
void GLTexture::releaseTexture()
{
	glDeleteTextures(1, &tex[0]);  
	tex[0] = 0;
}
    
void GLTexture::setTextureParams(GLTextureParameters &params)
{
	type = params.type;
	texTarget = params.target;			//texTarget  GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_RECTANGLE_ARB, 
	texInternalFormat = params.format;  //GL_RGBA, GL_RGBA16F_ARB, GL_RGBA32F_ARB;
	minFilter = params.minFilter;		//GL_NEAREST, GL_LINEAR
	magFilter = params.magFilter;		//GL_NEAREST, GL_LINEAR
}   

GLuint GLTexture::getTextureID()
{
	return tex[0];
}

GLuint GLTexture::getTextureTarget()
{
	return texTarget;
}   

float GLTexture::getMaxTextureCoordS()
{
	return (float)width;
}

float GLTexture::getMaxTextureCoordT()
{
	return (float)height;
}
	

///////////////////
/// draw

void GLTexture::render()
{
	render(0, 0, (float)width, (float)height);
}


void GLTexture::render(float x, float y, float w, float h)
{
	render(x, y, w, h, 0, 0, 1, 1);
}
    
void GLTexture::render(float x, float y, float w, float h, float sx, float ty, float sw, float th)
{
	glEnable(texTarget);
    glBindTexture(texTarget, tex[0]);

	float fw, fh;
    fw = (float)width;
	fh = (float)height;
	glBegin(GL_QUADS);
    bind();
	glTexCoord2f(fw * sx, fh * ty);
	glVertex2f(x, y);
    glTexCoord2f(fw * sw, fh * ty);
	glVertex2f(x + w, y);
    glTexCoord2f(fw * sw, fh * th);
	glVertex2f(x + w, y + h );
    glTexCoord2f(fw * sx, fh * th);
	glVertex2f(x, y + h);
	glEnd();

	glBindTexture(texTarget, 0);
	glDisable(texTarget);
}   


//////////////////////////


  
    
/**
  * Copies floatArray into the texture, assuming that the array has 4 components.
  * @param floatArray float[]
  * @param format int
  */
void GLTexture::putBuffer(float *floatArray)
{
	putBuffer(floatArray, texInternalFormat);
}

/**
  * Copies floatArray into the texture, using the specified format.
  * @param floatArray float[]
  * @param format int
  */
void GLTexture::putBuffer(float* floatArray, int format)
{
	if (tex[0] == 0)
    {
		initTexture((int)width, (int)height);
	}
	int glFormat = GL_RGBA; //format;  //GL_LUMINANCE, GL_RGB, GL_RGBA;
	glEnable(texTarget);
    glBindTexture(texTarget, tex[0]);
    if (texTarget == GL_TEXTURE_1D)
		glTexSubImage1D(texTarget, 0, 0, width, glFormat, GL_FLOAT, floatArray);
	else
		glTexSubImage2D(texTarget, 0, 0, 0, width, height, glFormat, type, floatArray);

	glBindTexture(texTarget, 0);
	glDisable(texTarget);
	
}

void GLTexture::getBuffer(float *floatArray)
{
	getBuffer(floatArray, texInternalFormat);
}
   
/**
  * Copies the texture into floatArray.
  * @param floatArray float[]
  * @param format int
  */
void GLTexture::getBuffer(float *floatArray, int format)
{
	int mult;
    int glFormat;
    if (format == GL_LUMINANCE) 
    { 
		mult = 1;
	}
    else if (format == GL_RGB) 
    {
		mult = 3;
	}
    else // GL_RGBA, GL_RGBA16F_ARB, GL_RGBA32F_ARB;
    { 
		
		glFormat = GL_RGBA;
		mult = 4;
	}
	
	int size = mult * width * height;
	glEnable(texTarget);
	glBindTexture(texTarget, tex[0]);
    glGetTexImage(texTarget, 0, glFormat, type, floatArray);
    glBindTexture(texTarget, 0);
}


