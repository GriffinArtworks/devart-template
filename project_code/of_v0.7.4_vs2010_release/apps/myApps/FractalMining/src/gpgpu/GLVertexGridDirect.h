#ifndef __GL_TEX_GRID_DIRECT
#define __GL_TEX_GRID_DIRECT

#include "vecStructs.h"
#include "ofMain.h"
#include "GLTextureGrid.h"
#include "GLTexturedPoint.h"

#define MAX_LAYERS 10

class GLVertexGridDirect : public GLTextureGrid
{
public:
	int srcW; // source width
	int srcH; // source height
	int destW; // dest width
	int destH; // dest height
	int resX;  // x resolution
	int resY;  // y resolution
	float gridDX[MAX_LAYERS];
    float gridDY[MAX_LAYERS];
	float gridw[MAX_LAYERS]; 
    float gridh[MAX_LAYERS];
	
	int numLayers;

	GLVertexGridDirect();
	void init(int sW, int sH, int dW, int dH, int resX = 2, int resY = 2);	
	void render();

	//
	void getPoint(int layeri, int i, int j, Vec2 &tp);
	void setTexCoord(int i,int j);
	void initGrid();
};

#endif