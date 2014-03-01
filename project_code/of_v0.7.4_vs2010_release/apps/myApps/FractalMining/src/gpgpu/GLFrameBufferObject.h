#ifndef __GL_FRAME_BUFFER_OBJECT
#define __GL_FRAME_BUFFER_OBJECT

#include "ofMain.h"
#include "GLTexture.h"

class GLFrameBufferObject 
{
public:
	GLFrameBufferObject(bool screenFBO);
	GLFrameBufferObject();
	void init();
	int getFramebufferID();
	void checkFBO();
    void setDrawBuffer(GLTexture *tex);
    void setDrawBuffers(GLTexture **drawTextures, int n);
	void setDrawBuffer(int target, int texid);
    void setDrawBuffers(int *texTargets, int *texIDs, int n);
    void bind();
   
  
    GLuint fbo[10];
	int numDrawBuffersInUse;
	GLuint colorDrawBuffers[10];
    GLuint textureIDs[10];
    GLuint textureTargets[10]; 
};

#endif
