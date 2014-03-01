//
//  PiecewisePath.h
//  pattern
//
//  Created by David on 30/01/2014.
//
//

#pragma once

#include "PPath.h"
#include "QCurvePath.h"
#include "LinePath.h"
#include "PointPath.h"


/*
 * Piecewise path is made up of a number of subpaths.
 */
class PiecewisePath: public PPath
{
public:
	typedef ofPtr<PiecewisePath> Ptr;
	
	typedef enum ClosedType
	{
		ClosedType_CLOSED = 0,
		ClosedType_OPEN = 1
	}ClosedType;
	
	typedef enum SmoothType
	{
		SmoothType_LINEAR = 0,
		SmoothType_SMOOTH = 1
		
	}SmoothType;
	
	
	vector<PPath::Ptr> paths;
	
	PiecewisePath()
	{
	}
	
	void addQCurve(const ofVec2f &p0,const ofVec2f &p1,const ofVec2f &p2)
	{
		paths.push_back(QCurvePath::Create(p0,p1,p2));
	}
	
	void addLine(const ofVec2f &p0,const ofVec2f &p1)
	{
		paths.push_back(LinePath::Create(p0,p1));
	}
	
	void addSubpath(PPath::Ptr path)
	{
		paths.push_back(path);
	}
	
	virtual ofVec2f getPoint(float rr)
	{
		if(paths.size() == 0) return ofVec2f(0,0);
		float r = getSegmentR(rr);
		
		
		// assume all lines equally weighted
		int pathi = r*paths.size();
		pathi = min(pathi,(int) paths.size() - 1);
		pathi = max(pathi, 0);
		
		
		float r2 = r*(float) (paths.size()) - (float)pathi;
	
		
		PPath::Ptr path = paths[pathi];
		return path->getPoint(r2);
		
	}
	
	///////
	// creates a path of a point set using quadratic curve segments
	void createSmoothPathFromPoints(vector<ofVec2f> &points, bool closed = false)
	{
		paths.clear();
		PPath::Ptr path;
		if(points.size() == 1)
		{
			// just make a point
			path = PointPath::Create(points[0]);
			addSubpath(path);
		}
		else if(points.size() == 2)
		{
			// create a line path
			this->addLine(points[0], points[1]);
			if(closed)
			{
				this->addLine(points[1], points[0]);
			}
		}
		else if(closed)
		{
			// closed path, so make peicewise quadratic curves if more than 2 points
			if(points.size() >= 3)
			{
				int n = points.size();
				ofVec2f p0,p1,p2;
				
				// add the first link
				p0 = points[n-1];
				p1 = points[0];
				p2 = points[1];
				p0 = p0.interpolated(p1, 0.5);
				p2 = p2.interpolated(p1, 0.5);
				this->addQCurve(p0, p1, p2);
				
				// add the middle segments
				for(int i = 0 ; i < n-2;++i)
				{
					p0 = points[i];
					p1 = points[i+1];
					p2 = points[i+2];
					
					p0 = p0.interpolated(p1, 0.5);
					p2 = p2.interpolated(p1, 0.5);
					this->addQCurve(p0, p1, p2);
				}
				
				// add the last link to join up to the start
				p0 = points[n-2];
				p1 = points[n-1];
				p2 = points[0];
				p0 = p0.interpolated(p1, 0.5);
				p2 = p2.interpolated(p1, 0.5);
				this->addQCurve(p0, p1, p2);
				
			}
		}
		else{
			if(points.size() >= 2)
			{
				// piecewise quad
				int n = points.size();
				ofVec2f p0,p1,p2;
				for(int i = 0 ; i < n-2;++i)
				{
					p0 = points[i+0];
					p1 = points[i+1];
					p2 = points[i+2];
					
					if(i > 0) p0 = p0.interpolated(p1, 0.5);
					if(i < n-3) p2 = p2.interpolated(p1, 0.5);
					this->addQCurve(p0, p1, p2);
				}
				
			}
		}
	}

	
	virtual PPath::Ptr clone()
	{
		PiecewisePath::Ptr cloned = Create();
		cloned->paths = this->paths;
		cloned->setFrom(this);
		return cloned;
	}
	
	static PiecewisePath::Ptr Create()
	{
		return PiecewisePath::Ptr(new PiecewisePath());
	}
	
	static PiecewisePath::Ptr CreateFromPoints(vector<ofVec2f>points, ClosedType closed /*, SmoothType smooth*/)
	{
		PiecewisePath::Ptr path =  PiecewisePath::Ptr(new PiecewisePath());
		
		//if(smooth == SmoothType_SMOOTH)
			path->createSmoothPathFromPoints(points, closed == ClosedType_CLOSED);
		//else
		//	path->createSharpPathFromPoints(points, closed == ClosedType_CLOSED);
		//path->setColourMode(colourmode);
		
		return path;
	}
};