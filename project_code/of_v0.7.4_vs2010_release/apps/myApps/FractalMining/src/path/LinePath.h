//
//  LinePath.h
//  emptyExample
//
//  Created by David on 04/01/2014.
//
//
#pragma once

#include "PPath.h"

/*
 * Line Path
 */
class LinePath: public PPath
{
public:
	typedef ofPtr<LinePath> Ptr;
	
	ofVec2f p0;
	ofVec2f p1;
	
	LinePath(const ofVec2f &p0, const ofVec2f &p1):PPath()
	{
		this->p0 = p0;
		this->p1 = p1;
	}
	
	virtual ofVec2f getPoint(float r)
	{
		return p0.interpolated(p1,getSegmentR(r));
	}
	
	virtual PPath::Ptr clone()
	{
		PPath::Ptr cloned = Create(p0,p1);
		cloned->setFrom(this);
		return cloned;
	}
	
	static LinePath::Ptr Create(const ofVec2f &p0, const ofVec2f &p1)
	{
		return LinePath::Ptr(new LinePath(p0,p1));
	}
};



