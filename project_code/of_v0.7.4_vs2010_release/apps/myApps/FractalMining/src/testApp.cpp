#include "testApp.h"
#include "stdio.h"
#include "GLState.h"
//--------------------------------------------------------------
testApp::testApp(){
	ofSetWindowPosition(0,0);
	ofSetWindowShape(1680*2,1050);
	ofSetFrameRate(30);
}

//--------------------------------------------------------------
void testApp::setup()
{
	counter = 0;
	gpufractal.init();
	colourmaptex.loadImage("data/colourmap.png");
	glcolourmaptex.initFromOFTexture(colourmaptex.getTextureReference());

	showPathLines = false;
	gpufractal.startDraw();
	restart = true;
	regenerate = true;
}

//--------------------------------------------------------------
void testApp::update()
{
	
}


//--------------------------------------------------------------
void testApp::draw()
{
	if(restart)
	{
		restart = false;
		gpufractal.startDraw();
		continueDelay = 0;
	}
	if(regenerate)
	{
		regenerate = false;
		gpufractal.regenerateTransformAni();
	}

	// draw the first frame, then wait a bit to continue drawing
	if(continueDelay ==0 || continueDelay > 5)
	{
		
		// update the fractal attributes
		gpufractal.scalef3 = 0.7f;	
		gpufractal.tf0.x =0;
		gpufractal.tf0.y =gpufractal.tf0.x;
	//	gpufractal.extratime = bands[0]*0.1;


		gpufractal.compute();
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.0,0.0,0.0,1);
		ofPushView();
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glTranslatef(ofGetWidth()*0.5,ofGetHeight()*0.5,0);
		glEnable(GL_DEPTH_TEST);
		//gpufractal.render();
		gpufractal.updateDraw();
	
		glDisable(GL_DEPTH_TEST);

		ofPopView();
		counter++;
	//	fbo.end();

		ofSetColor(255,255,255,255);
		// show framerate in titlebar
		string str = ofToString(ofGetFrameRate(), 2)+"fps"; ofSetWindowTitle(str); 
	
		//glClearColor(0.0,0.0,1.0,1);
		//glClear(GL_COLOR_BUFFER_BIT);
	}
	continueDelay++;

	gpufractal.fbo.draw(0,0);


//	ofLine(ofPoint(100,100),ofPoint(200,300));
	
	if(showPathLines)
	{
		ofPushView();
		ofTranslate(ofPoint(gpufractal.fbo.getWidth()*0.5,gpufractal.fbo.getHeight()*0.5));
		ofSetLineWidth(5);

		for(int i =0;i < gpufractal.nSubmats;++i)
		{
			gpufractal.paths[i].drawPath();
			Matrix3f m = gpufractal.submats[i];
			m.drawAxisLines();
		}


		ofPopView();
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	switch(key)
	{
		case OF_KEY_F5:
			ofSetFullscreen(true);
			break;
		case OF_KEY_UP:
			gpufractal.basescale += 0.1;
			break;
	
		case OF_KEY_DOWN:
			gpufractal.basescale -= 0.1;
			gpufractal.basescale = max(0.1f,gpufractal.basescale);
			break;
		case 'c':
			break;
		case OF_KEY_LEFT:
			gpufractal.basepos.x -= gpufractal.basescale*100.0;
			break;
		case OF_KEY_RIGHT:
			gpufractal.basepos.x += gpufractal.basescale*100.0;
			break;
		case 'w':
			gpufractal.basepos.y-= gpufractal.basescale*100.0;
			break;
		case 's':
			gpufractal.basepos.y += gpufractal.basescale*100.0;
			break;
		case 'n':
			gpufractal.pathtime  += 0.01;
			break;
		case 'm':
			gpufractal.pathtime  -= 0.01;
			break;
		case 'j':
			gpufractal.rotatetime  += 0.04;
			break;
		case 'k':
			gpufractal.rotatetime  -= 0.04;
			break;
		case 'i':
			gpufractal.scaletime  += 0.1;
			break;
		case 'o':
			gpufractal.scaletime  -= 0.1;
			break;
		case 'q':
			showPathLines = showPathLines == false;
			break;
		case 'r':
			regenerate = true;
			break;
	}
	restart = true;
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
	
}
