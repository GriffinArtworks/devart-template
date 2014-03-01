
#include "GLState.h"

 void GLState::setOrthographicView(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w, 0.0, h);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLState::printAvailExtensions()
{
	const GLubyte *extensions = glGetString(GL_EXTENSIONS);
	printf ( "[GLState::printAvailExtensions] %s\n", extensions);
	
}

void GLState::printAnyError()
{
	GLenum errCode;
	const GLubyte *errString;
	if ((errCode = glGetError()) != GL_NO_ERROR) 
	{
	    errString = gluErrorString(errCode);
		fprintf (stderr, "[GLState::printAnyerror] OpenGL Error: %s\n", errString);
	}
}
    
void GLState::saveView()
{
	glPushAttrib(GL_VIEWPORT_BIT);
	saveGLMatrices();
}

void GLState::restoreView()
{
	restoreGLMatrices();
    glPopAttrib();
}
    
void GLState::saveGLState()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
    saveGLMatrices();
}      
   
void GLState::restoreGLState()
{
	restoreGLMatrices();
    glPopAttrib();
}
    
void GLState::saveGLMatrices()
{
	glMatrixMode(GL_PROJECTION);
    glPushMatrix();    	
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
}

 void GLState::restoreGLMatrices()
{
	glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();    
}

 ofMatrix4x4 GLState::getModelViewMatrix()
 {
	 float matvalues[16];
	 glGetFloatv(GL_MODELVIEW_MATRIX, matvalues);
	 
	 ofMatrix4x4 mat;
	 mat.set(&matvalues[0]);
	 return mat;
 }


 ofMatrix4x4 GLState::getProjectionMatrix()
 {
	 float matvalues[16];
	 glGetFloatv(GL_PROJECTION_MATRIX, matvalues);

	 ofMatrix4x4 mat;
	 mat.set(&matvalues[0]);
	 return mat;
 }


 void GLState::printVersionNumbers()
{
	//glVersion = glGetString(GL_VERSION);
    //glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION_ARB); 
}
    
 void GLState::printMaxColorAttachments()
{
	int glMaxColorAttach;
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &glMaxColorAttach);  
	printf("[GLState printMaxColorAttachments] max color attacments: %i", glMaxColorAttach);
 }
