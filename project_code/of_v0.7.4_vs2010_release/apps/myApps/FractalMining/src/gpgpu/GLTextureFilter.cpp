#include "GLTextureFilter.h"

GLTextureFilter::GLTextureFilter()
{
	shader = 0;
	grid = 0;
	blend  =false;
}

void GLTextureFilter::initFilter(GLSLShader *shader, GLTextureGrid *texturegrid)
{	    
	this->shader = shader;
	this->grid = texturegrid;
}

/*Applies the shader program on textures srcTex, writing the output to the textures destTex.
 */
void GLTextureFilter::apply(GLTexture **srcTex, int nsrc, GLFrameBufferObject *destfbo, GLTexture **destTex, int ndest,bool handleFboBind = true)
{
	int srcWidth = srcTex[0]->width;
	int srcHeight = srcTex[0]->height;
    int destWidth = destTex[0]->width;
    int destHeight = destTex[0]->height;
	setGLConf(destWidth, destHeight); // setup projectionmat/viewport

//	printf("[GLTextureFilter::apply] \n");
//	printf("[GLTextureFilter::apply] destfboid %i \n",destfbo->getFramebufferID());
	// bind fbo, input and output textures
	shader->start(srcTex, nsrc, destfbo, destTex , ndest, handleFboBind);
	grid->render();
	shader->end();
    
	restoreGLConf(); // restore state
}
  
/// use for previously setup buffer (eg screen buffer)
void GLTextureFilter::applyToCurrentBuffer(GLTexture **srcTex, int nsrc)
{
	shader->startDrawToCurrentBuffer(srcTex, nsrc);     
	grid->render();
	shader->end();
}

///////////////////////




void GLTextureFilter::noBlend()
{
	blend = false;
}

void GLTextureFilter::setBlendMode(int MODE)
{
	blend = true;
    blendMode = MODE;
}    
      
void GLTextureFilter::setGLConf(int w, int h)
{
	blend0 = glIsEnabled(GL_BLEND);
    glGetIntegerv(GL_POLYGON_MODE, &polyMode);
		
    if (blend) 
	{
		glEnable(GL_BLEND);
//        if (blendMode == BLEND) glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        else if (blendMode == ADD) glBlendFunc(GL_SRC_ALPHA, GL_ONE);
 //       else if (blendMode == MULTIPLY) glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);/
//		else if (blendMode == SUBTRACT) glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
//            how to implement all these other blending modes:
//            else if (blendMode == LIGHTEST)
//            else if (blendMode == DIFFERENCE)
//            else if (blendMode == EXCLUSION)
//            else if (blendMode == SCREEN)
//            else if (blendMode == OVERLAY)
//            else if (blendMode == HARD_LIGHT)
//            else if (blendMode == SOFT_LIGHT)
//            else if (blendMode == DODGE)
//            else if (blendMode == BURN)

    }
    else glDisable(GL_BLEND);

    glPolygonMode(GL_FRONT, GL_FILL);
	GLState::saveView();
	GLState::setOrthographicView(w, h);
}


void GLTextureFilter::restoreGLConf()
{
	GLState::restoreView();
	if (blend0) glEnable(GL_BLEND);
	else glDisable(GL_BLEND);
	glPolygonMode(GL_FRONT, polyMode);
}


  
/////


