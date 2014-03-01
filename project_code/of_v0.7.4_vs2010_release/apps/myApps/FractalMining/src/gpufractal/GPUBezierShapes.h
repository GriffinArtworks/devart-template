//The vertices stored in a static Vertex Buffer Object in GPU memory.
//   these can contain static offsets, eg normalised vert coords for a quad to render particles
//texcoord grids for each texture.  For gpgpu, each vert points to a pixel. 

// modified from codeanticode.glgraphics.GLTextureGridCompiled


#ifndef __GL_VERTEX_TEXTURE_GRID_VBO
#define __GL_VERTEX_TEXTURE_GRID_VBO

#include "GLTextureGrid.h"
#include "FloatBuffer.h"
#include "GLTexturedPoint.h"
#include "ofMain.h"
#include "QCurvePath.h"

#define GL_VERTEX_MAX_TEXTURES 8
#define GL_VERTEX_MAX_POINTS 1000 

/*
 * a shape is made of 6 points (2 quadratic beizer paths) 
 */
class GPUBezierShapes: public GLTextureGrid
{
public:
	bool built;
	int mode;
	int resX, resY; // Number of points in the grid, along each direction.  
	FloatBuffer vertCoordsBuffer;
	FloatBuffer texCoordsBuffer[GL_VERTEX_MAX_TEXTURES];
	GLuint vertCoordsVBO[2];
	GLuint texCoordsVBO[GL_VERTEX_MAX_TEXTURES];
   
	int numTexCoords;
	int numTextures;
	bool dirty;
	
	GPUBezierShapes();
	void init();
	void clear();
	void addCurveLine(const QCurvePath &curve);
	void addFilledShape(const QCurvePath &curve0, const QCurvePath &curve1);
	void render(int numInstances);
	//void addCircle(ofVec2f center, float radius);
	void addOval(ofVec2f center, float radiusx, float radiusy);
	void addRect(ofVec2f center, float w, float h);
	void addPetal(ofVec2f center, float w, float h);
	void addTriangle(ofVec2f tip, float w, float h);
	void addTeardrop(ofVec2f tip, float w, float h, float curveh);
	void addCurvedTriangle(ofVec2f tip, float w, float h, float curveoffset);
};

#endif