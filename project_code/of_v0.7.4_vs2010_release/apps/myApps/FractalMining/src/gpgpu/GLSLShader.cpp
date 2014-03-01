#include "GLSLShader.h"

GLSLShader::GLSLShader()
{
	this->destFBO = 0;
	srcTex = 0;
	nsrctex = 0;
	nUniforms = 0;
}

void GLSLShader::initShader(string vertName, string fragName, string tessControlName, string tessEvalName, int numInputTex) 
{
	this->numInputTex = numInputTex;
	shader.load(vertName,fragName,tessControlName,tessEvalName);
	shader.begin();
    // Getting uniform parameters.
    for (int i = 0; i < numInputTex; i++)
    {
		char name[100];
		sprintf(&name[0],"src_tex_unit%i",i);
		srcTexUnitUniform[i] = shader.getUniformLocation(name );
	    //srcTexOffsetUniform[i] = shader.getUniformLocation(srcTexOffsetUniformName[i]);
    }

	modelMatrixUniform = shader.getUniformLocation("modelMatrix");
	projectionMatrixUniform = shader.getUniformLocation("projectionMatrix");


	for (int i = 0; i < nUniforms; i++)
    {
		uniformsArray[i]->setShader(&shader);
	}
	shader.end();
}

void GLSLShader::initShader(char* shaderName, int numInputTex) 
{
	this->numInputTex = numInputTex;
	shader.load(shaderName);
	shader.begin();
    // Getting uniform parameters.
    for (int i = 0; i < numInputTex; i++)
    {
		char name[100];
		sprintf(&name[0],"src_tex_unit%i",i);
		srcTexUnitUniform[i] = shader.getUniformLocation(name );
	    //srcTexOffsetUniform[i] = shader.getUniformLocation(srcTexOffsetUniformName[i]);
    }
	/*
	clockDataUniformName = "clock_data";
    destColorUniformName = "dest_color";
    destTexSizeUniformName = "dest_tex_size";
	clockDataUniform = shader.getUniformLocation("clock_data");
    destColorUniform = shader.getUniformLocation("dest_color");
    destTexSizeUniform = shader.getUniformLocation("dest_tex_size");
	*/

	modelMatrixUniform = shader.getUniformLocation("modelMatrix");
	projectionMatrixUniform = shader.getUniformLocation("projectionMatrix");



	for (int i = 0; i < nUniforms; i++)
    {
		uniformsArray[i]->setShader(&shader);
	}
	shader.end();
}



void GLSLShader::start(GLTexture **srcTex, int nsrctex, GLFrameBufferObject *destfbo, GLTexture **destTex, int ndesttex, bool handleFboBind)
{
	//this->handleFboBind = handleFboBind;
	if(handleFboBind)
	{
		this->destFBO = destfbo;
		destFBO->bind();
	}
	//printf("[GLSLShader::start] here 2");
	setOutputTextures(destfbo, destTex, ndesttex);
	startDrawToCurrentBuffer(srcTex, nsrctex);
	
}

void GLSLShader::startDrawToCurrentBuffer(GLTexture **srcTex, int nsrctex)
{
	this->srcTex = srcTex;
	this->nsrctex = nsrctex;
	shader.begin();



	setupShaderUniforms(srcTex, nsrctex);
	bindSrcTex(srcTex, nsrctex);
	setInputTextures(srcTex, nsrctex);
}

void GLSLShader::end()
{
	unbindSrcTex(srcTex, nsrctex);
	shader.end();
	if(destFBO != 0) glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); //unbind fbo
}


///////////////////////


void GLSLShader::setOutputTextures(GLFrameBufferObject *destfbo, GLTexture **destTex, int ndesttex)
{
	destfbo->setDrawBuffers(destTex, ndesttex);
}

void GLSLShader::setInputTextures(GLTexture **srcTex, int nsrctex)
{
	int i;
	for (i = 0; i < nsrctex; i++)
    {
	   glUniform1iARB(srcTexUnitUniform[i], i);
		//   if (-1 < srcTexOffsetUniform[i]) gl.glUniform2fARB(srcTexOffsetUniform[i], 1.0f / srcTex[i].width, 1.0f / srcTex[i].height);
	}
	
	
}

void GLSLShader::bindSrcTex(GLTexture **srcTex, int nsrctex)
{
	glEnable(srcTex[0]->getTextureTarget());
	for (int i = 0; i < nsrctex; i++)
    { 
		///printf("[ GLTextureFilter::bindSrcTex] %i", i);
		glActiveTextureARB(GL_TEXTURE0 + i);
        glBindTexture(srcTex[i]->getTextureTarget(), srcTex[i]->getTextureID());    
    }
}

void GLSLShader::unbindSrcTex(GLTexture **srcTex, int nsrctex)
{
	for (int i = 0; i < nsrctex; i++)
    {
		glActiveTexture(GL_TEXTURE0 + i );
        glBindTexture(srcTex[i]->getTextureTarget(), 0);
	}
    glDisable(srcTex[0]->getTextureTarget());
}


void GLSLShader::updateUniformVariables()
{
	for (int i = 0; i < nUniforms; i++) 
		uniformsArray[i]->setParameter();
}

void GLSLShader::setupShaderUniforms(GLTexture **srcTex, int nsrctex)
{
	updateUniformVariables();
	
	
	glUniformMatrix4fvARB(modelMatrixUniform, 1, false, GLState::getModelViewMatrix().getPtr());
	glUniformMatrix4fvARB(projectionMatrixUniform, 1, false, GLState::getProjectionMatrix().getPtr());

	/*
    if (-1 < clockDataUniform)
    {
		int fcount = parent.frameCount;
        int msecs = parent.millis();          
        gl.glUniform2fARB(clockDataUniform, fcount, msecs);
	}
		
    if (-1 < destColorUniform)
        	gl.glUniform4fARB(destColorUniform, destR, destG, destB, destA);		

	if (-1 < destTexSizeUniform) gl.glUniform2fARB(destTexSizeUniform, w, h);
    */  
}


void GLSLShader::addUniform(GLSLShaderUniform *uniform)
{
	uniformsArray[nUniforms] = uniform;
	nUniforms++;
}



void GLSLShader::setShaderActive(bool active)
{
	if(active)shader.begin();
	else shader.end();
}

