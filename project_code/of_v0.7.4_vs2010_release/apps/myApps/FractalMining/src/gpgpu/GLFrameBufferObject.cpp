#include "GLFrameBufferObject.h"

GLFrameBufferObject::GLFrameBufferObject(bool screenFBO)
{
	if (screenFBO) fbo[0] = 0;
	else glGenFramebuffersEXT(1, &fbo[0]);	
}
		
GLFrameBufferObject::GLFrameBufferObject()
{
	
}

void GLFrameBufferObject::init()
{
	numDrawBuffersInUse = 0;
	glGenFramebuffersEXT(1, &fbo[0]);
	printf("[GLFrameBufferObject::init] id %i\n", fbo[0]);
}

int GLFrameBufferObject::getFramebufferID()
{
	return fbo[0];
}
	
void GLFrameBufferObject::checkFBO()
{
	int stat = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
}

void GLFrameBufferObject::setDrawBuffer(GLTexture *tex)
{
	GLTexture **texptr = &tex;
	setDrawBuffers(texptr, 1);
}
        
void GLFrameBufferObject::setDrawBuffers(GLTexture **drawTextures, int n)
{
	this->numDrawBuffersInUse  = n;
	for (int i = 0; i < numDrawBuffersInUse; i++)
	{
		colorDrawBuffers[i] = GL_COLOR_ATTACHMENT0_EXT + i;        	
        textureTargets[i] = drawTextures[i]->getTextureTarget();
        textureIDs[i] = drawTextures[i]->getTextureID();    	
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, colorDrawBuffers[i], textureTargets[i], textureIDs[i], 0);
	}
	checkFBO();
    glDrawBuffers(numDrawBuffersInUse, &colorDrawBuffers[0]);
	
}

void GLFrameBufferObject::setDrawBuffer(int target, int texid)
{
	setDrawBuffers(&target, &texid, 1);
}    
    
void GLFrameBufferObject::setDrawBuffers(int *texTargets, int *texIDs, int n)
{
	numDrawBuffersInUse = n;    	
	for (int i = 0; i < numDrawBuffersInUse; i++)
    {
		colorDrawBuffers[i] = GL_COLOR_ATTACHMENT0_EXT + i;        	
        textureTargets[i] = texTargets[i];
        textureIDs[i] = texIDs[i];	
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, colorDrawBuffers[i], textureTargets[i], textureIDs[i], 0);
	}

	checkFBO();     
    glDrawBuffers(numDrawBuffersInUse, &colorDrawBuffers[0]);    	
}
    
void GLFrameBufferObject::bind()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo[0]);
}
    