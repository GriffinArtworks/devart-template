#include "GLVertexGridDirect.h"


GLVertexGridDirect::GLVertexGridDirect()
{
	
}
    
void GLVertexGridDirect::init(int sW, int sH, int dW, int dH, int resX, int resY)
{
	srcW = sW;
	srcH = sH;
	destW = dW;
	destH = dH;
	this->resX = resX;
	this->resY = resY;
	initGrid();
}

void GLVertexGridDirect::render()
{
	Vec2 p0, p1;

    for (int j = 0; j < resY - 1; j++)
    {
		glBegin(GL_QUAD_STRIP);
        for (int i = 0; i < resX; i++)
        {
			getPoint(0, i, j, p0);
            getPoint(0, i, j + 1, p1);

			setTexCoord(i, j);
			glVertex2f(p0.x*destW, p0.y*destH);

			setTexCoord(i, j + 1);
			glVertex2f(p1.x*destW, p1.y*destH);
		}
		glEnd();
	}
}

void GLVertexGridDirect::getPoint(int layeri, int i, int j, Vec2 &tp)
{
    tp.x = i * gridDX[layeri];
    tp.y = j * gridDY[layeri];
}

void GLVertexGridDirect::setTexCoord(int i, int j)
{
	Vec2 p;
	for (int k = 0; k < numLayers; k++)
    {
		getPoint(k, i, j, p);
        glMultiTexCoord2f(GL_TEXTURE0 + k, p.x*gridw[k], p.y*gridh[k]);
	}
}

 // Creates a 1x1 grid (just 2 points on each direction).
void GLVertexGridDirect::initGrid()
{
	numLayers = 2;
    gridDX[0] = 1.0f / (resX - 1); // i.e.: 1.0
    gridDY[0] = 1.0f / (resY - 1); // i.e.: 1.0
	gridDX[1] = 1.0f / (resX - 1); // i.e.: 1.0
    gridDY[1] = 1.0f / (resY - 1); // i.e.: 1.0
	gridw[0] = srcW; 
	gridh[0] = srcH;
	gridw[1] = destW;
	gridh[1] = destH;
}
