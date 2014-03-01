#ifndef __GLSL_SHADER_
#define __GLSL_SHADER_

#include "ofMain.h"
#include "ofShader.h"
#include "GLSLShaderUniform.h"
#include "GLTexture.h"
#include "GLFrameBufferObject.h"


// wraps ofshader to include custom uniform variables and multiple render targets
class GLSLShader
{
public:
	ofShader shader;
	int nsrctex;
	GLTexture **srcTex;
	GLSLShaderUniform *uniformsArray[100];
	int nUniforms;
	int numInputTex;
    int numOutputTex;
	int srcTexUnitUniform[16];    
    char *srcTexName[16];    


	char *clockDataUniformName;
    char *destColorUniformName;
    char *destTexSizeUniformName;
    int clockDataUniform;
	int destColorUniform;
	int destTexSizeUniform;

	int modelMatrixUniform;
	int projectionMatrixUniform;

	
	GLFrameBufferObject *destFBO;
    
	/////
	
	GLSLShader();
	void initShader(string vertName, string fragName,  string tessControlName, string tessEvalName, int numInputTex) ;
	void initShader(char* shaderName, int numInputTex); 
	void addUniform(GLSLShaderUniform *uniform);

	void start(GLTexture **srcTex, int nsrctex, GLFrameBufferObject *destfbo, GLTexture **destTex, int ndesttex, bool handleFboBind);
	void startDrawToCurrentBuffer(GLTexture **srcTex, int nsrctex);
	void end();
	
	//
	void setOutputTextures(GLFrameBufferObject *destfbo, GLTexture **destTex, int ndesttex);
	void setInputTextures(GLTexture **srcTex, int nsrctex);
	void bindSrcTex(GLTexture **srcTex, int nsrctex);
	void unbindSrcTex(GLTexture **srcTex, int nsrctex);
	void updateUniformVariables();
	void setupShaderUniforms(GLTexture **srcTex, int nsrctex);
	void setShaderActive(bool active);
};

#endif