//
//  PointPath.h
//  emptyExample
//
//  Created by David on 04/01/2014.
//
//
#pragma once

#include "PPath.h"

/*
 * a single Point
 */
class PointPath: public PPath
{
public:
	typedef ofPtr<PointPath> Ptr;
	
	ofVec2f p;
	
	PointPath(const ofVec2f &p):PPath()
	{
		this->p = p;
	}
	
	virtual ofVec2f getPoint(float r)
	{
		return p;
	}

	virtual PPath::Ptr clone()
	{
		PPath::Ptr cloned = Create(p);
		cloned->setFrom(this);
		return cloned;
	}
	
	static PointPath::Ptr Create(const ofVec2f &p)
	{
		return PointPath::Ptr(new PointPath(p));
	}
};