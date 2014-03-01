#pragma once
#include "ofMain.h"
#include "Matrix3f.h"

/*
 * move along a path to change the position of a coordspace
 *
 */
class RotateAni{    
public:

	float startAngle; 
	float scalefactor;

	RotateAni()
	{
		scalefactor = 1;
		startAngle = 0;
	}

	void init(float startAngle, float  scalefactor)
	{
		this->scalefactor = scalefactor;
		this->startAngle = startAngle;
	}

	float getAngle(float t)
	{
		return startAngle + t*scalefactor;
	}

};
