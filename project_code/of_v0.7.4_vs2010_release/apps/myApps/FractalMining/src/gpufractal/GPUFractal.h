#ifndef __GPU_FRACTAL
#define __GPU_FRACTAL

#include "GLTexturedPoint.h"
#include "GPUBezierShapes.h"
#include "ofMain.h"
#include "GLSLShader.h"
#include "GLTexture.h"
#include "ofImage.h"
#include "GLState.h"
#include "GLTextureSet.h"
#include "GLVertexGridDirect.h"
#include "GLTextureFilter.h"
#include "GLTexturePtrArray.h"
#include "GLSLShaderUniform.h"
#include "Matrix4f.h"
#include "Matrix3f.h"
#include "GPUBezierShapes.h"
#include "PathAni.h"
#include "RotateAni.h"
#include "ScaleAni.h"

class GPUFractal
{
public:
	//
	int canvasw;
	int canvash;
	int depthStart;	// start depth to render
	int depthEnd;	// end depth to render
	int nInstancesInUpdate;

	float scalef0;
	float scalef1;
	float scalef2;
	float scalef3;
	Vec2 basepos;

	Vec3 tf0;
	Vec3 tf1;
	Vec3 tf2;
	Vec3 tf3;
	float extratime;
	float easedextratime;
	int nMatTextureRows;

	int nSubmats;
	Matrix3f rootmat;
	Matrix3f submats[11];
	PathAni paths[11];
	ScaleAni scales[11];
	RotateAni rotations[11];
	
	float pathtime;
	float rotatetime;
	float scaletime;
	float rotatetimeExtraSpeed[11] ;
	float pathtimeExtraSpeed[11];

	float rotatetimeExtra[11] ;
	float pathtimeExtra[11] ;

	ofFbo fbo;
	
	ofImage colourmaptex;
	GLTexture glcolourmap;

	// shapes
	GPUBezierShapes shapes;
	GLSLShader shader;
	GLSLShaderUniform uniformFractalDepth;
	GLSLShaderUniform uniformNPointsInDepth;
	GLSLShaderUniform texsize;

	///drawing
	int currentDepth;
	int currentInstanceix;

	
	float basescale;

	
	void init();
	void startDraw();
	void updateDraw();
	void compute();
	void renderUpdateDraw();
	void updateDrawInstances(int startix, int nInstancesToDraw);
	void regenerateTransformAni();
private:

	
};

#endif