#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "Matrix4f.h"
#include "ofFbo.h"
#include "GPUFractal.h"
#include "GLTexture.h"
#include "ofxHttpUtils.h"

class testApp : public ofBaseApp{

	public:
		GLTexture glcolourmaptex;
		ofImage colourmaptex;
		GPUFractal gpufractal;
		
		bool showPathLines;
		int counter;
		bool regenerate;
		bool restart;
		int continueDelay;

		ofxHttpUtils httpUtils;

		testApp();
		void setup();
		void update();
		void draw();
		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void newResponse(ofxHttpResponse & response);
};

#endif
