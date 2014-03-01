#ifndef __GL_TEXTURE_SET_
#define __GL_TEXTURE_SET_

#include "GLTexture.h"
#include "GLTexturePtrArray.h"

class GLTextureSet
{
public:
	GLTexture texArray[10];
	int ntexs;
	GLTexturePtrArray pointerarray;
	int width;
	int height;

	void init(int n, int width, int height, GLTextureParameters &params)
	{
		this->width = width;
		this->height = height;
		this->ntexs = n;
		for(int i=0;i<n;i++)
		{
			texArray[i].init(width,height, params);
			pointerarray.addTexture(&texArray[i]);
		}
	}

	GLTexture *getTexture(int i)
	{
		return &texArray[i];
	}

	// for filter.apply
	GLTexture **getTexturePtrArray()  
	{
		return pointerarray.getPointerToArray();
	}
};

#endif