#pragma once
#include "ofMain.h"
#include "Matrix3f.h"

/*
 * move along a path to change the position of a coordspace
 *
 */
class ScaleAni{    
public:
	ofVec2f endScale;
	ofVec2f startScale; 
	float tscale;

	ScaleAni()
	{
		startScale = ofVec2f(1,1);
		tscale = 1;
	}

	void init(ofVec2f startScale, ofVec2f endScale, float tscale)
	{
		this->startScale = startScale;
		this->endScale = endScale;
		this->tscale =tscale;
	}

	ofVec2f getScale(float t)
	{
		return startScale.getInterpolated(endScale, max(0.0f, min(1.f,t*tscale)) );
	}

};
