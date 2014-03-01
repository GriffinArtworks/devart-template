#pragma once
#include "ofMain.h"
#include "Matrix3f.h"
#include "path.h"


/*
 * move along a path to change the position of a coordspace
 *
 */
class PathAni{    
public:

	// 
	PPath::Ptr path;
	Matrix3f mat;
	PathAni()
	{

	}

	Matrix3f getCoordspace(float t)
	{
		ofVec2f p = getPoint(t);
		ofVec2f vx = getTangent(t);

		Matrix3f m;
		m.setTranslation(p.x,p.y);
		m.m00 = vx.x;
		m.m01 = vx.y;
		m.m10 = vx.y;
		m.m11 = -vx.x;


		return m;
	}

	/*
	 * 
	 */
	void setTransform(float dist, float r, float localr, ofVec2f localoffset, float localscale)
	{

		mat.setIdentity();
		mat.mulRotate(r);
		mat.mulTranslate(0,dist);
		mat.mulRotate(localr);
		mat.mulTranslate(localoffset.x,localoffset.y);
		mat.applyScale(localscale,localscale);
	}

	void createPath(ofVec2f p0, ofVec2f p1, ofVec2f p2)
	{
		path = QCurvePath::Create(p0,p1,p2);
	}

	ofVec2f getTangent(float t)
	{
		ofVec2f p0 = getPoint(t);
		ofVec2f p1 = getPoint(t+0.01);
		ofVec2f v = p1 - p0;
		return v.getNormalized();
	}

	ofVec2f getPoint(float t)
	{
		ofVec2f p = path->getPoint(t);
		return mat.transform(p);
	}

	virtual void update(float t, Matrix3f *mat)
	{
		ofVec2f p = path->getPoint(t);
		mat->setTranslation(p.x,p.y);

	}

	void drawPath()
	{
		int res = 10;
		for(int i =0 ; i <res;++i)
		{
			float r = (float)i/(float)res;
			float r1 = (float)(i+1)/(float)res;
			ofVec2f p = getPoint(r);
			ofVec2f p1 = getPoint(r1);
			ofLine(p,p1);
		}
	}

};
