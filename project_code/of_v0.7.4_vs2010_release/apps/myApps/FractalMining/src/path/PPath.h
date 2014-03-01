//
//  Path.h
//  emptyExample
//
//  Created by David on 04/01/2014.
//
//
#pragma once
#include "ofMain.h"

/*
 * base path class, from which Line, Point and Curves extend.
 */
class PPath
{
public:
	typedef ofPtr<PPath> Ptr;
	
	float startr; // path segment start range, default is 0.0
	float endr;   // path segment end range, default is 1.0
	
	PPath()
	{
		// default segment this the whole path
		startr = 0;
		endr = 1;
	}

	
	/*
	 * return an interpolated point on the path,  r = [0,1]
	 * override this in subclass
	 */
	virtual ofVec2f getPoint(float r)
	{
		return ofVec2f(0,0);
	}
	
	/*
	 * draw the path as a line, mainly for debuging
	 */
	virtual void draw(float thickness )
	{
	}
	
	/*
	 * return a new cloned copy
	 */
	virtual PPath::Ptr clone()
	{
		PPath::Ptr cloned = Create();
		cloned->setFrom(this);
		return cloned;
	}
	
	/*
	 * helper for the clone method
	 */
	virtual void setFrom(PPath *path)
	{
		this->startr = path->startr;
		this->endr = path->endr;
	}
	
	/*
	 * helper method for getting the Ratio value within the segment (startr to endr).
	 */
	float getSegmentR(float r)
	{
		return startr + (endr-startr)*r;
	}
	
	void setSegmentRange(float startr, float endr)
	{
		this->startr = startr;
		this->endr = endr;
		
	}
	
	static PPath::Ptr Create()
	{
		return PPath::Ptr(new PPath());
	}
	
	////////////////////////////////////
	// helper methods
	
	static ofVec2f Interpolated(PPath *path0, PPath *path1, float rx, float ry)
	{
		return path0->getPoint(rx).getInterpolated(path1->getPoint(rx), ry);
	}
	
	static ofVec2f Interpolated(PPath *path0, PPath *path1, ofVec2f normalisedPoint)
	{
		return path0->getPoint(normalisedPoint.x).getInterpolated(path1->getPoint(normalisedPoint.x), normalisedPoint.y);
	}
	
	static ofRectangle GetBound(PPath *path0, PPath *path1)
	{
		ofVec2f p = path0->getPoint(0);
		float sx, endx;
		float sy, endy;
		sx = p.x;
		sy = p.y;
		endx = p.x;
		endy = p.y;
		int n = 9;
		for (int i=0; i<n; i++)
		{
			float r = (float)i/(float ) (n-1);
			p = path0->getPoint(r);
			if( p.x < sx)			sx = p.x;
			else if( p.x > endx)	endx = p.x;
			if( p.y < sy)			sy = p.y;
			else if( p.y > endy)	endy = p.y;
		}
		for (int i=0; i<n; i++)
		{
			float r = (float)i/(float ) (n-1);
			p = path1->getPoint(r);
			if( p.x < sx)			sx = p.x;
			else if( p.x > endx)	endx = p.x;
			if( p.y < sy)			sy = p.y;
			else if( p.y > endy)	endy = p.y;
		}
		
		ofRectangle bound;
		
		bound.x = sx;
		bound.y = sy;
		bound.width = endx - sx;
		bound.height = endy - sy;
		return bound;
	}
	
	
	////
	//helper method for drawing path line from a set of points
	// 
	void drawPath(vector<ofVec2f> &points, float thickness)
	{
		vector<ofVec2f> vs;
		ofSetLineWidth(0);
		ofBeginShape();
		float size = thickness;
		ofVec2f p0,p1;
		ofVec2f v,p;
		for(int i=0;i < points.size() ;++i)
		{
			if(i == points.size() - 1)
			{
				p0 = points[i-1];
				p1 = points[i];
			}
			else{
				p0 = points[i];
				p1 = points[i+1];
			}
			v = p1 -p0;
			v = v.getPerpendicular().normalized();
			vs.push_back(v);
			
			p = points[i] + v*size*0.5;
			ofVertex(p.x,p.y);
		}
		
		for(int i=points.size() - 1;i >=0  ;--i)
		{
			p = points[i] - vs[i]*size*0.5;
			ofVertex(p.x,p.y);
		}
		ofEndShape(true);
	}
};

