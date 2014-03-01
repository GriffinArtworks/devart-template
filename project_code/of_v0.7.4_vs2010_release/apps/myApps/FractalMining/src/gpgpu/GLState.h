#ifndef __GL_STATE
#define __GL_STATE

#include "ofMain.h"

class GLState
{
	public:
	static void setOrthographicView(int w, int h);
	static void saveView();
	static void printAnyError();
	static void printAvailExtensions();
	static void restoreView();
	static void saveGLState();
	static void restoreGLState();
	static void saveGLMatrices();
	static void restoreGLMatrices();
	static void printVersionNumbers();
	static void printMaxColorAttachments();
	static ofMatrix4x4 getModelViewMatrix();
	static ofMatrix4x4 getProjectionMatrix();
};

#endif