//
//  InterpolatedPath.h
//  emptyExample
//
//  Created by David on 05/01/2014.
//
//

#pragma once

#include "PPath.h"

/*
 * Interpolated path between into paths.
 */
class InterpolatedPath: public PPath
{
public:
	typedef ofPtr<InterpolatedPath> Ptr;
	
	PPath::Ptr path0;
	PPath::Ptr path1;
	float pathr;
	float pathr1;
	
	
	InterpolatedPath()
	{
		pathr1 = 0;
		pathr = 0;
	}
	
	InterpolatedPath(PPath::Ptr path0, PPath::Ptr path1, float r):PPath()
	{
		this->path0 = path0;
		this->path1 = path1;
		this->pathr = r;
		this->pathr1 = r;
		
	}
	
	virtual ofVec2f getPoint(float rr)
	{
		float r = getSegmentR(rr);
		ofVec2f p0 = path0->getPoint(r);
		ofVec2f p1 = path1->getPoint(r);
		return p0.interpolated(p1, pathr + (pathr1 - pathr)*rr );
	}
	
	virtual PPath::Ptr clone()
	{
		PPath::Ptr cloned = Create(path0->clone(),path1->clone(),pathr);
		cloned->setFrom(this);
		return cloned;
	}
	
	static InterpolatedPath::Ptr Create(PPath::Ptr path0, PPath::Ptr path1, float r)
	{
		return InterpolatedPath::Ptr(new InterpolatedPath(path0,path1,r));
	}
};