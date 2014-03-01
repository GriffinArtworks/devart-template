#include "GPUFractal.h"


void GPUFractal::init()
{
	canvasw = 1680*2;
	canvash = 1050;

	nSubmats = 4;
	depthStart = 4;
	depthEnd = 13;
	nInstancesInUpdate = 10000;

	colourmaptex.loadImage("data/colourmap.png");
	glcolourmap.initFromOFTexture(colourmaptex.getTextureReference());

	//printf("[ GPUFractal::init] total nsubspaces %i \n",(int) pow((float)nSubmats, (depthEnd-depthStart) ));
	basescale = 1.0f;
	basepos.x =0;basepos.y = 0;
	scalef0 = 1.0f;
	scalef1 = 1.0f;
	scalef2 = 1.0f;
	scalef3 = 1.0f;
	extratime = 0.0f;
	easedextratime = 0.0f;
	pathtime = 0;
	rotatetime = 0;
	scaletime = 0;
	
	regenerateTransformAni();

	fbo.allocate(canvasw,canvash, GL_RGBA, 16);
	
	// populate with seome default shapes
	float z = 0;float s = 10;
	shapes.init();
	//shapes.addRect(ofVec2f(0,0), 200,50);
	shapes.addCurveLine(QCurvePath(ofVec2f(-5*s, (z+30)*s), ofVec2f(10*s, (z+50)*s), ofVec2f(15*s,z*s)));
	//shapes.addCurveLine(QCurve(ofVec2f(-5*s, z*s), ofVec2f(20*s, (z+5)*s), ofVec2f(5*s,(z+10)*s)));
	shapes.addOval(ofVec2f(0,0), 50,50);
	shapes.addCurveLine(QCurvePath::CreateLine(ofVec2f(-25,0), ofVec2f(25,0)));



	texsize.init("texsize", SHADER_PARAM_TYPE_FLOAT);
	shader.addUniform(&texsize);
	uniformFractalDepth.init("fractalDepth", SHADER_PARAM_TYPE_FLOAT);
	shader.addUniform(&uniformFractalDepth);
	uniformNPointsInDepth.init("nPointsInDepth", SHADER_PARAM_TYPE_FLOAT);
	shader.addUniform(&uniformNPointsInDepth);
	shader.initShader("shaders/particleRenderer.vert", "shaders/particleRenderer.frag", "shaders/particleRenderer.tc", "shaders/particleRenderer.te", 4);


}

void GPUFractal::regenerateTransformAni()
{
	

	paths[0].setTransform(ofRandom(100.0,50.0), M_TWO_PI*ofRandom(0,2), M_TWO_PI*ofRandom(0,2), ofVec2f(0,0), M_TWO_PI*ofRandom(0.5,2));
	paths[1].setTransform(ofRandom(200.0,50.0), M_TWO_PI*ofRandom(0,2), M_TWO_PI*ofRandom(0,2), ofVec2f(0,0), M_TWO_PI*ofRandom(0.5,2));
	paths[2].setTransform(ofRandom(100.0,50.0), M_TWO_PI*ofRandom(0,2), M_TWO_PI*ofRandom(0,2), ofVec2f(0,0), M_TWO_PI*ofRandom(0.5,3));
	paths[3].setTransform(ofRandom(100.0,50.0), M_TWO_PI*ofRandom(0,2), M_TWO_PI*ofRandom(0,2), ofVec2f(0,0), M_TWO_PI*ofRandom(0.5,3));
	
	paths[0].createPath(ofVec2f(-100, 10),ofVec2f(0, 10), ofVec2f(100, 10));
	paths[1].createPath(ofVec2f(-100, 10),ofVec2f(0, 10), ofVec2f(100, 10));
	paths[2].createPath(ofVec2f(-100, 10),ofVec2f(0, 10), ofVec2f(100, 10));
	paths[3].createPath(ofVec2f(-100, 10),ofVec2f(0, 10), ofVec2f(100, 10));

	scales[0].init(ofVec2f(ofRandom(0.1,0.7),ofRandom(0.5,1)), ofVec2f(1,1), 0.5);
	scales[1].init (ofVec2f(ofRandom(0.1,0.7),ofRandom(0.5,1)), ofVec2f(1,1), 0.5);
	scales[2].init(ofVec2f(ofRandom(0.1,0.7),ofRandom(0.5,1)), ofVec2f(1,1), 0.5);
	scales[3].init(ofVec2f(ofRandom(0.1,0.8),ofRandom(0.5,1)), ofVec2f(1,1), 0.5);

	rotations[0].init(M_TWO_PI*ofRandom(0,2), ofRandom(0.3,2));
	rotations[1].init(M_TWO_PI*ofRandom(0,2), ofRandom(0.3,2));
	rotations[2].init(M_TWO_PI*ofRandom(0,2), ofRandom(0.3,2));
	rotations[3].init(M_TWO_PI*ofRandom(0,2), ofRandom(0.3,2));

	for(int i =0;i < nSubmats;++i)
	{
		pathtimeExtraSpeed[i] =ofRandom(-0.001,0.001);
		rotatetimeExtraSpeed[i] =ofRandom(-0.01,0.01);

	}
}

// being drawing the 
void GPUFractal::startDraw()
{
	for(int i =0;i < nSubmats;++i)
	{
		pathtimeExtra[i]= 0;
		rotatetimeExtra[i] = 0;

	}
	fbo.begin();
	glClearColor(0.0,0.0,0.0,0);
	glClear(GL_DEPTH_BUFFER_BIT);

	float canvascol = 0.0; // 1.0 for white  ,0.0 for black

	glClearColor(canvascol,canvascol,canvascol,1);
	glClear(GL_COLOR_BUFFER_BIT);

	fbo.end();
	currentDepth = depthStart;
	currentInstanceix = 0;

}

void GPUFractal::updateDraw()		
{
	for(int i =0;i < nSubmats;++i)
	{
		pathtimeExtra[i] += pathtimeExtraSpeed[i];
		rotatetimeExtra[i] += rotatetimeExtraSpeed[i];

	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float zoomFactor = 1;
	glOrtho (0, canvasw, canvash, 0, -10, 1000);
	glViewport(0,0, canvasw, canvash);
	glMatrixMode(GL_MODELVIEW);

	fbo.begin();
	renderUpdateDraw();
	fbo.end();


}


void GPUFractal::renderUpdateDraw()
{
	int instancesDrawn = 0;
	
	bool reversedDepth = depthStart > depthEnd;

	
	while(instancesDrawn < nInstancesInUpdate)
	{
		int nInstancesInDepth = pow((float)nSubmats, currentDepth);
		int startix = currentInstanceix;
		int endix = min(nInstancesInDepth, startix + nInstancesInUpdate);
		
		if(reversedDepth)
		{
			if(currentDepth > depthEnd)
			{
				texsize.setValue((float) pow(nInstancesInDepth, 0.5));
				uniformFractalDepth.setValue((float)currentDepth);
				uniformNPointsInDepth.setValue((float) nInstancesInDepth);
				updateDrawInstances(startix, endix - startix);

				instancesDrawn += endix - startix;
				if(endix ==nInstancesInDepth )
				{
					currentInstanceix = 0;
					currentDepth--;
				}
				else{
					currentInstanceix  = endix;
				}
			}
		}
		else{
			if(currentDepth < depthEnd)
			{
				texsize.setValue((float) pow(nInstancesInDepth, 0.5));
				uniformFractalDepth.setValue((float)currentDepth);
				uniformNPointsInDepth.setValue((float) nInstancesInDepth);
				updateDrawInstances(startix, endix - startix);

				instancesDrawn += endix - startix;
				if(endix ==nInstancesInDepth )
				{
					currentInstanceix = 0;
					currentDepth++;
				}
				else{
					currentInstanceix  = endix;
				}
			}
		}

		bool complete = (currentDepth == depthEnd);
		if(complete) break;

	}
}

// do method that does the instanced draw call
void GPUFractal::updateDrawInstances(int startix, int nInstancesToDraw)
{
	GLTexturePtrArray ptrarray;
	ptrarray.addTexture(&glcolourmap);
	shader.startDrawToCurrentBuffer(ptrarray.getPointerToArray(),1);     
	glUniformMatrix3fv(shader.shader.getUniformLocation("Mats"), nSubmats, GL_FALSE,(GLfloat *) &submats[0]);
	glUniformMatrix3fv(shader.shader.getUniformLocation("RootMat"), 1, GL_FALSE,(GLfloat *) &rootmat);
	//glUniform1i(shader.shader.getUniformLocation("maxdepth"), max(depthStart,depthEnd));
	//glUniform1i(shader.shader.getUniformLocation("maxdepth"), max(depthStart,depthEnd));

	shader.shader.setUniform1i("startInstanceID", startix);
	shader.shader.setUniform1i("nSubmats", nSubmats);
	shapes.render(nInstancesToDraw);
	shader.end();
}

void GPUFractal::compute()
{
////test
	if(extratime > easedextratime) easedextratime = extratime;
	easedextratime += (extratime - easedextratime)*0.2f;

	for(int i =0; i< nSubmats;++i)
	{
		submats[i] = paths[i].getCoordspace(pathtime + pathtimeExtra[i] );
		submats[i].mulScale(scales[i].getScale(scaletime).x,scales[i].getScale(scaletime).y);
		submats[i].mulRotate(rotations[i].getAngle(rotatetime + rotatetimeExtra[i]));
	}


	//// update root coordspace
	rootmat.setIdentity();
	rootmat.setTranslation(canvasw*0.5 + basepos.x,canvash*0.5 + basepos.y);
	rootmat.applyScale(basescale,basescale);
}


