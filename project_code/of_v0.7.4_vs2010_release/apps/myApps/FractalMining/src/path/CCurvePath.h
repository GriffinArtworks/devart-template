//
//  CCurvePath.h
//  emptyExample
//
//  Created by David on 04/01/2014.
//
//
#pragma once

#include "PPath.h"

/*
 * a cubic bezier curve (p1,p2 are the control points)
 */
class CCurvePath: public PPath
{
public:
	typedef ofPtr<CCurvePath> Ptr;
	
	ofVec2f p0;
	ofVec2f p1;
	ofVec2f p2;
	ofVec2f p3;
	
	CCurvePath(const ofVec2f &p0,const ofVec2f &p1,const ofVec2f &p2,const ofVec2f &p3):PPath()
	{
		this->p0 = p0;
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
	}
	
	virtual ofVec2f getPoint(float rr)
	{
		float r = getSegmentR(rr);
		
		ofVec2f p;
		float s = 1- r;
		p.x = s*s*s*p0.x + 3*s*s*r*p1.x + 3*s*r*r*p2.x + r*r*r*p3.x;
		p.y = s*s*s*p0.y + 3*s*s*r*p1.y + 3*s*r*r*p2.y + r*r*r*p3.y;
		return p;
	}

	virtual PPath::Ptr clone()
	{
		PPath::Ptr cloned = Create(p0,p1,p2,p3);
		cloned->setFrom(this);
		return cloned;
	}
	
	static CCurvePath::Ptr Create(const ofVec2f &p0, const ofVec2f &p1, const ofVec2f &p2, const ofVec2f &p3)
	{
		return CCurvePath::Ptr(new CCurvePath(p0,p1,p2,p3));
	}


};
