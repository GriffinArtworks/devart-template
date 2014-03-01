#include "GPUBezierShapes.h"
#define SIZEOF_FLOAT 4
#define MAX_VERTS 1000

GPUBezierShapes::GPUBezierShapes()
{
	built = false;
	numTextures = 1;
	mode = GL_PATCHES;
	dirty = true;
}

void GPUBezierShapes::init()
{
	vertCoordsBuffer.allocateSpace(MAX_VERTS);
	glGenBuffersARB(1, &vertCoordsVBO[0]);  
}


void GPUBezierShapes::render(int numInstances)
{
	int nVerts = vertCoordsBuffer.n/3;

	// upload data if dirty
	if(dirty)
	{
		dirty = false;
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertCoordsVBO[0]);  // Bind the buffer.
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertCoordsBuffer.n  * SIZEOF_FLOAT, vertCoordsBuffer.farray, GL_STATIC_DRAW_ARB); // Load the data
	}


	// Enable VBO Pointers
	glEnableClientState(GL_VERTEX_ARRAY);        // Enable Vertex Arrays
//	glEnableClientState(GL_TEXTURE_COORD_ARRAY); // Enable Texture Coord Arrays 
	/**
	for (int n = 0; n < numTextures; n++)
	{
		glClientActiveTexture(GL_TEXTURE0 + n);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, texCoordsVBO[n]);
		glTexCoordPointer(2, GL_FLOAT, 0, 0); // Set The TexCoord Pointer To The TexCoord Buffer
	}*/

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertCoordsVBO[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0); // Set The Vertex Pointer To The Vertex Buffer

	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // draw wire

	glPatchParameteri(GL_PATCH_VERTICES, 6);
	glDrawArraysInstanced(mode, 0, nVerts, numInstances);
	// Disable Vertex Arrays
	glDisableClientState(GL_VERTEX_ARRAY);  
	// Disable Texture Coord Arrays
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); 

	glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
}	


void GPUBezierShapes::clear()
{
	dirty = true;
	vertCoordsBuffer.reset();

}

void GPUBezierShapes::addCurveLine( const QCurvePath &curve )
{
	addFilledShape(curve,curve);
}

void GPUBezierShapes::addFilledShape( const QCurvePath &curve0, const QCurvePath &curve1 )
{
	dirty = true;
	vertCoordsBuffer.add(curve0.p0.x,curve0.p0.y,0);
	vertCoordsBuffer.add(curve0.p1.x,curve0.p1.y,0);
	vertCoordsBuffer.add(curve0.p2.x,curve0.p2.y,0);

	vertCoordsBuffer.add(curve1.p0.x,curve1.p0.y,0);
	vertCoordsBuffer.add(curve1.p1.x,curve1.p1.y,0);
	vertCoordsBuffer.add(curve1.p2.x,curve1.p2.y,0);

}

void GPUBezierShapes::addOval(ofVec2f center, float radiusx, float radiusy)
{
	dirty = true;
	
	int n = 8;
	for(int i =0 ;i <8;++i)
	{
		GLTexturedPoint p;
		float r0 = (float)i/(float)n;
		float r1 = (float)(i+1)/(float)n;
		float r2 = (float)(i+2)/(float)n;

		ofVec2f p0 =center + ofVec2f(sin(r0*M_TWO_PI)*radiusx,cos(r0*M_TWO_PI)*radiusy);
		ofVec2f p1 =center + ofVec2f(sin(r1*M_TWO_PI)*radiusx,cos(r1*M_TWO_PI)*radiusy);
		ofVec2f p2 =center + ofVec2f(sin(r2*M_TWO_PI)*radiusx,cos(r2*M_TWO_PI)*radiusy);
		addFilledShape(QCurvePath::CreatePoint(center), QCurvePath(p0.getInterpolated(p1,0.5),p1,p1.getInterpolated(p2,0.5)));
	}
}

void GPUBezierShapes::addRect(ofVec2f center, float w, float h)
{
	float x = w*0.5;
	float y = h*0.5;
	addFilledShape(QCurvePath::CreateLine(center + ofVec2f(-x,-y), center + ofVec2f(-x,y)), 
				   QCurvePath::CreateLine(center + ofVec2f(+x,-y), center + ofVec2f(+x,y)));

}

void GPUBezierShapes::addPetal(ofVec2f center, float w, float h)
{
	float x = w*0.5;
	float y = h*0.5;
	addFilledShape(QCurvePath::CreateCurve(center+ ofVec2f(-w*0.5,0),center + ofVec2f(0,h*0.5), center + ofVec2f(w*0.5,0) ), 
		QCurvePath::CreateCurve(center+ ofVec2f(-w*0.5,0),center + ofVec2f(0,-h*0.5), center + ofVec2f(w*0.5,0) ) );
}


void GPUBezierShapes::addTriangle(ofVec2f tip, float w, float h)
{
	float x = w*0.5;
	float y = h*0.5;
	addFilledShape(QCurvePath::CreatePoint(tip), 
		QCurvePath::CreateLine(tip + ofVec2f(-w*0.5,+h), tip + ofVec2f(+w*0.5,h)));
}

void GPUBezierShapes::addTeardrop(ofVec2f tip, float w, float h, float curveh)
{
	float x = w*0.5;
	float y = h*0.5;
	addFilledShape(QCurvePath::CreatePoint(tip), 
		QCurvePath::CreateCurve(tip + ofVec2f(-w*0.5,+h),tip + ofVec2f(0,+h+curveh), tip + ofVec2f(+w*0.5,h)));
}

void GPUBezierShapes::addCurvedTriangle(ofVec2f tip, float w, float h, float curveoffset)
{
	float x = w*0.5;
	float y = h*0.5;
	addFilledShape(	QCurvePath::CreateCurve(tip+ofVec2f(curveoffset,0),tip.getInterpolated(ofVec2f(-w*0.5,+h),0.5), ofVec2f(-w*0.5,+h) ), 
		QCurvePath::CreateCurve(tip+ofVec2f(curveoffset,0),tip.getInterpolated(ofVec2f(+w*0.5,+h),0.5), ofVec2f(+w*0.5,+h) ) 
		);
}
