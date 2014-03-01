#include "Matrix3f.h"
#include "ofMain.h"

// port from Matrix3f.java
Matrix3f::Matrix3f()
{
	setIdentity();
}

void Matrix3f::print() 
{
	//printf("%.3f %.3f %.3f %.3f \n", m00,m01,m02,m03 );
	//printf("%.3f %.3f %.3f %.3f \n", m10,m11,m12,m13 );
	//printf("%.3f %.3f %.3f %.3f \n", m20,m21,m22,m23 );

}


ofVec2f Matrix3f::transform(ofVec2f p) 
{
	ofVec2f q;
	q.x = m00*p.x + m01*p.y + m02;
	q.y = m10*p.x + m11*p.y + m12;
	return q;
}

void Matrix3f::applyScale(float sx, float sy) 
{
	m00 *= sx; //m03 *= sx;
	m11 *= sy; //m13 *= sy;
}


void Matrix3f::setIdentity() 
{
	m00 = 1.0; m01 = 0.0; m02 = 0.0;
	m10 = 0.0; m11 = 1.0; m12 = 0.0;
	m20 = 0.0; m21 = 0.0; m22 = 1.0;

}

void Matrix3f::transpose() {
	float tmp = m01;
	m01 = m10;
	m10 = tmp;

	tmp = m02;
	m02 = m20;
	m20 = tmp;

	tmp = m12;
	m12 = m21;
	m21 = tmp;
}

void Matrix3f::transpose(Matrix3f &m1) 
{
	// alias-safe
	set(m1);
	transpose();
}

void Matrix3f::set(Matrix3f &m1) 
{
	m00 = m1.m00; m01 = m1.m01; m02 = m1.m02; 
	m10 = m1.m10; m11 = m1.m11; m12 = m1.m12;
	m20 = m1.m20; m21 = m1.m21; m22 = m1.m22; 
}

void Matrix3f::mul(float scalar) 
{
	m00 *= scalar; m01 *= scalar;  m02 *= scalar; 
	m10 *= scalar; m11 *= scalar;  m12 *= scalar; 
	m20 *= scalar; m21 *= scalar;  m22 *= scalar; 

}


void Matrix3f::setTranslation(float x,float y) 
{
	m02 = x;
	m12 = y; 
}

void Matrix3f::mulTranslate(float x, float y)
{
	Matrix3f mat;
	mat.setTranslation(x,y);

	Matrix3f res;
	res.mul(this, &mat);
	*this = res;
}

void Matrix3f::mulRotate(float angle)
{
	Matrix3f mat;
	mat.rotZ(angle);

	Matrix3f res;
	res.mul(this, &mat);
	*this = res;
}

void Matrix3f::mulScale(float sx, float sy)
{
	Matrix3f mat;
	mat.applyScale(sx,sy);

	Matrix3f res;
	res.mul(this, &mat);
	*this = res;
}


void Matrix3f::rotZ(float angle)  
{
	float c = cosf(angle);
	float s = sinf(angle);
	m00 = c;   m01 = -s;  m02 = 0.0; 
	m10 = s;   m11 = c;   m12 = 0.0; 
	m20 = 0.0; m21 = 0.0; m22 = 1.0;
}


void Matrix3f::mulTransposeRight(Matrix3f &m1, Matrix3f &m2) 
{
	// alias-safe way.
	set(
		m1.m00*m2.m00 + m1.m01*m2.m01 + m1.m02*m2.m02,
		m1.m00*m2.m10 + m1.m01*m2.m11 + m1.m02*m2.m12,
		m1.m00*m2.m20 + m1.m01*m2.m21 + m1.m02*m2.m22,
		
		m1.m10*m2.m00 + m1.m11*m2.m01 + m1.m12*m2.m02,
		m1.m10*m2.m10 + m1.m11*m2.m11 + m1.m12*m2.m12,
		m1.m10*m2.m20 + m1.m11*m2.m21 + m1.m12*m2.m22,
		
		m1.m20*m2.m00 + m1.m21*m2.m01 + m1.m22*m2.m02,
		m1.m20*m2.m10 + m1.m21*m2.m11 + m1.m22*m2.m12,
		m1.m20*m2.m20 + m1.m21*m2.m21 + m1.m22*m2.m22 
		
);
}

void Matrix3f::mul(Matrix3f *m1) 
{
	mul(this, m1);
}


void Matrix3f::mul(Matrix3f *m1, Matrix3f *m2) 
{
	// alias-safe way
	set(
		m1->m00*m2->m00 + m1->m01*m2->m10 + m1->m02*m2->m20,
		m1->m00*m2->m01 + m1->m01*m2->m11 + m1->m02*m2->m21,
		m1->m00*m2->m02 + m1->m01*m2->m12 + m1->m02*m2->m22,
	
		m1->m10*m2->m00 + m1->m11*m2->m10 + m1->m12*m2->m20,
		m1->m10*m2->m01 + m1->m11*m2->m11 + m1->m12*m2->m21,
		m1->m10*m2->m02 + m1->m11*m2->m12 + m1->m12*m2->m22,
		
		m1->m20*m2->m00 + m1->m21*m2->m10 + m1->m22*m2->m20,
		m1->m20*m2->m01 + m1->m21*m2->m11 + m1->m22*m2->m21,
		m1->m20*m2->m02 + m1->m21*m2->m12 + m1->m22*m2->m22
	
		);
}

void Matrix3f::set(float m00, float m01, float m02,
	float m10, float m11, float m12,
	float m20, float m21, float m22
	) 
{
	this->m00 = m00; this->m01 = m01; this->m02 = m02;
	this->m10 = m10; this->m11 = m11; this->m12 = m12; 
	this->m20 = m20; this->m21 = m21; this->m22 = m22; 
	
}

void Matrix3f::drawAxisLines()
{
	ofSetLineWidth(3);
	ofVec2f p0 = transform(ofVec2f(0,0));
	ofVec2f p1 = transform(ofVec2f(1,0));
	ofVec2f p2 = transform(ofVec2f(0,1));

	ofVec2f v;
	v = p1 - p0;
	v = v * 30.0;
	ofSetColor(255,0,0);
	ofLine(p0,p0 + v);

	v = p2 - p0;
	v = v* 30.0;
	ofSetColor(0,255,0);
	ofLine(p0,p0 + v);

	ofSetColor(255,255,255);


}

