//
//  QCurvePath.h
//  emptyExample
//
//  Created by David on 04/01/2014.
//
//
#pragma once

#include "PPath.h"

/*
 * a quadratic bezier curve (p1 is the control point)
 */
class QCurvePath: public PPath
{
public:
	typedef ofPtr<QCurvePath> Ptr;
	
	ofVec2f p0;
	ofVec2f p1;
	ofVec2f p2;
	
	QCurvePath(const ofVec2f &p0,const ofVec2f &p1,const ofVec2f &p2):PPath()
	{
		this->p0 = p0;
		this->p1 = p1;
		this->p2 = p2;
	}
	
	virtual ofVec2f getPoint(float rr)
	{
		float r = getSegmentR(rr);
		
		ofVec2f p;
		float f2 = (1-r)*(1-r);
		float f1 = 2*(1-r)*r;
		p.x = f2*p0.x + f1*p1.x + r*r*p2.x;
		p.y = f2*p0.y + f1*p1.y + r*r*p2.y;
		return p;

	}
	
	virtual PPath::Ptr clone()
	{
		PPath::Ptr cloned = Create(p0,p1,p2);
		cloned->setFrom(this);
		return cloned;
	}
	
	static QCurvePath::Ptr Create(const ofVec2f &p0, const ofVec2f &p1, const ofVec2f &p2)
	{
		return QCurvePath::Ptr(new QCurvePath(p0,p1,p2));
	}

	static QCurvePath CreatePoint(ofVec2f p)
	{
		return QCurvePath(p,p,p);
	}

	static QCurvePath CreateLine(ofVec2f p0,ofVec2f p1)
	{
		return QCurvePath(p0,p0.interpolated(p1,0.5),p1);
	}

	static QCurvePath CreateCurve(const ofVec2f &p0, const ofVec2f &p1, const ofVec2f &p2)
	{
		return QCurvePath(p0,p1,p2);
	}
};
