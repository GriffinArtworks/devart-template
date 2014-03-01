#ifndef __GL_FILTER
#define __GL_FILTER

#include "ofMain.h"
#include "GLTexture.h"
#include "GLState.h"
#include "GLSLShader.h"
#include "GLSLShaderUniform.h"
#include "GLFrameBufferObject.h"
#include "GPUBezierShapes.h"
#include "GLTextureGrid.h"

// 
class GLTextureFilter
{
public:
	GLSLShader *shader;
	GLTextureGrid *grid;
	//GLFrameBufferObject *destfbo; // optional

	int polyMode;
	bool blend;
    bool blend0;
    int blendMode;
	 
	GLTextureFilter();
	void initFilter(GLSLShader *shader, GLTextureGrid *texturegrid);	 
	void apply(GLTexture **srcTex, int nsrc, GLFrameBufferObject *destfbo, GLTexture **destTex, int ndest, bool handleFboBind );
	void applyToCurrentBuffer(GLTexture **srcTex, int nsrc);
	//

	void noBlend();
	void setBlendMode(int MODE);
	void setGLConf(int w, int h);
	void restoreGLConf();
	
};

#endif






  
  