#ifndef __GL_TEXTURE_PTR_ARRAY_
#define __GL_TEXTURE_PTR_ARRAY_

#include "GLTexture.h"

class GLTexturePtrArray
{
public:
	GLTexture *texArray[100];
	int ntex;
	
	GLTexturePtrArray()
	{
		ntex = 0;
	}
	
	void addTexture(GLTexture *texture)
	{
		texArray[ntex] = texture;
		ntex++;
	}

	GLTexture **getPointerToArray()
	{
		return &(texArray[0]);
	}

};

#endif