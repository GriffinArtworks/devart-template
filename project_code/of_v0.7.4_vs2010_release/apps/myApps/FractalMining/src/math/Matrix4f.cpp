#include "Matrix4f.h"
#include "ofMain.h"

// port from matrix4f.java
Matrix4f::Matrix4f()
{
	setIdentity();
}

void Matrix4f::print() 
{
	printf("%.3f %.3f %.3f %.3f \n", m00,m01,m02,m03 );
	printf("%.3f %.3f %.3f %.3f \n", m10,m11,m12,m13 );
	printf("%.3f %.3f %.3f %.3f \n", m20,m21,m22,m23 );
	
}

void Matrix4f::applyScale(float sx, float sy, float sz) 
{
	m00 *= sx; //m03 *= sx;
	m11 *= sy; //m13 *= sy;
	m22 *= sz;// m23 *= sz;
}


void Matrix4f::setIdentity() 
{
	m00 = 1.0; m01 = 0.0; m02 = 0.0; m03 = 0.0;
	m10 = 0.0; m11 = 1.0; m12 = 0.0; m13 = 0.0;
	m20 = 0.0; m21 = 0.0; m22 = 1.0; m23 = 0.0;
	m30 = 0.0; m31 = 0.0; m32 = 0.0; m33 = 1.0;
}

void Matrix4f::transformPoint(Vec3 *p) 
{
	transformPoint(p,p);
}

void Matrix4f::transformVector(Vec3 *v, Vec3 *resv) 
{
	float x,y,z;
	x = m00*v->x + m01*v->y + m02*v->z;
	y = m10*v->x + m11*v->y + m12*v->z;
	z = m20*v->x + m21*v->y + m22*v->z;
	resv->x = x;
	resv->y = y;
	resv->z = z;
}

void Matrix4f::transformPoint(Vec3 *p, Vec3 *resp) 
{
	float x,y,z;
	x = m00*p->x + m01*p->y + m02*p->z + m03;
	y = m10*p->x + m11*p->y + m12*p->z + m13;
	z = m20*p->x + m21*p->y + m22*p->z + m23;
	resp->x = x;
	resp->y = y;
	resp->z = z;
//	printf("p = %f,%f,%f  res %f,%f,%f \n", p->x, p->y, p->z,resp->x, resp->y, resp->z);
}

void Matrix4f::transpose() {
	float tmp = m01;
	m01 = m10;
	m10 = tmp;

	tmp = m02;
	m02 = m20;
	m20 = tmp;

	tmp = m03;
	m03 = m30;
	m30 = tmp;

	tmp = m12;
	m12 = m21;
	m21 = tmp;

	tmp = m13;
	m13 = m31;
	m31 = tmp;

	tmp = m23;
	m23 = m32;
	m32 = tmp;
}

 void Matrix4f::transpose(Matrix4f &m1) 
 {
	// alias-safe
	set(m1);
	transpose();
 }

void Matrix4f::set(Matrix4f &m1) 
{
	m00 = m1.m00; m01 = m1.m01; m02 = m1.m02; m03 = m1.m03;
	m10 = m1.m10; m11 = m1.m11; m12 = m1.m12; m13 = m1.m13;
	m20 = m1.m20; m21 = m1.m21; m22 = m1.m22; m23 = m1.m23;
	m30 = m1.m30; m31 = m1.m31; m32 = m1.m32; m33 = m1.m33;
}

void Matrix4f::invert(Matrix4f &m1)  
{
	set(m1);
	invert();
}

void Matrix4f::invert() 
{
	float s = determinant();
	if (s == 0.0)
	    return;
	s = 1/s;
	// alias-safe way.
	// less *,+,- calculation than expanded expression.
	set(
	    m11*(m22*m33 - m23*m32) + m12*(m23*m31 - m21*m33) + m13*(m21*m32 - m22*m31),
	    m21*(m02*m33 - m03*m32) + m22*(m03*m31 - m01*m33) + m23*(m01*m32 - m02*m31),
	    m31*(m02*m13 - m03*m12) + m32*(m03*m11 - m01*m13) + m33*(m01*m12 - m02*m11),
	    m01*(m13*m22 - m12*m23) + m02*(m11*m23 - m13*m21) + m03*(m12*m21 - m11*m22),

	    m12*(m20*m33 - m23*m30) + m13*(m22*m30 - m20*m32) + m10*(m23*m32 - m22*m33),
	    m22*(m00*m33 - m03*m30) + m23*(m02*m30 - m00*m32) + m20*(m03*m32 - m02*m33),
	    m32*(m00*m13 - m03*m10) + m33*(m02*m10 - m00*m12) + m30*(m03*m12 - m02*m13),
	    m02*(m13*m20 - m10*m23) + m03*(m10*m22 - m12*m20) + m00*(m12*m23 - m13*m22),

	    m13*(m20*m31 - m21*m30) + m10*(m21*m33 - m23*m31) + m11*(m23*m30 - m20*m33),
	    m23*(m00*m31 - m01*m30) + m20*(m01*m33 - m03*m31) + m21*(m03*m30 - m00*m33),
	    m33*(m00*m11 - m01*m10) + m30*(m01*m13 - m03*m11) + m31*(m03*m10 - m00*m13),
	    m03*(m11*m20 - m10*m21) + m00*(m13*m21 - m11*m23) + m01*(m10*m23 - m13*m20),

	    m10*(m22*m31 - m21*m32) + m11*(m20*m32 - m22*m30) + m12*(m21*m30 - m20*m31),
	    m20*(m02*m31 - m01*m32) + m21*(m00*m32 - m02*m30) + m22*(m01*m30 - m00*m31),
	    m30*(m02*m11 - m01*m12) + m31*(m00*m12 - m02*m10) + m32*(m01*m10 - m00*m11),
	    m00*(m11*m22 - m12*m21) + m01*(m12*m20 - m10*m22) + m02*(m10*m21 - m11*m20)
	    );

	mul(s);
}

float Matrix4f::determinant()  
{
	// less *,+,- calculation than expanded expression.
	return
	    (m00*m11 - m01*m10)*(m22*m33 - m23*m32)
	   -(m00*m12 - m02*m10)*(m21*m33 - m23*m31)
	   +(m00*m13 - m03*m10)*(m21*m32 - m22*m31)
	   +(m01*m12 - m02*m11)*(m20*m33 - m23*m30)
	   -(m01*m13 - m03*m11)*(m20*m32 - m22*m30)
	   +(m02*m13 - m03*m12)*(m20*m31 - m21*m30);

}

void Matrix4f::mul(float scalar) 
{
	m00 *= scalar; m01 *= scalar;  m02 *= scalar; m03 *= scalar;
	m10 *= scalar; m11 *= scalar;  m12 *= scalar; m13 *= scalar;
	m20 *= scalar; m21 *= scalar;  m22 *= scalar; m23 *= scalar;
	m30 *= scalar; m31 *= scalar;  m32 *= scalar; m33 *= scalar;
}


void Matrix4f::setTranslation(float x,float y,float z) 
{
	m03 = x;
    m13 = y;  
	m23 = z;
}

void Matrix4f::rotX(float angle)  
{
	float c = cosf(angle);
	float s = sinf(angle);
	m00 = 1.0; m01 = 0.0; m02 = 0.0; m03 = 0.0;
	m10 = 0.0; m11 = c;   m12 = -s;  m13 = 0.0;
	m20 = 0.0; m21 = s;   m22 = c;   m23 = 0.0;
	m30 = 0.0; m31 = 0.0; m32 = 0.0; m33 = 1.0; 
}

void Matrix4f::rotY(float angle)  
{
	float c = cosf(angle);
	float s = sinf(angle);
	m00 = c;   m01 = 0.0; m02 = s;   m03 = 0.0;
	m10 = 0.0; m11 = 1.0; m12 = 0.0; m13 = 0.0;
	m20 = -s;  m21 = 0.0; m22 = c;   m23 = 0.0;
	m30 = 0.0; m31 = 0.0; m32 = 0.0; m33 = 1.0; 
}

void Matrix4f::rotZ(float angle)  
{
	float c = cosf(angle);
	float s = sinf(angle);
	m00 = c;   m01 = -s;  m02 = 0.0; m03 = 0.0;
	m10 = s;   m11 = c;   m12 = 0.0; m13 = 0.0;
	m20 = 0.0; m21 = 0.0; m22 = 1.0; m23 = 0.0;
	m30 = 0.0; m31 = 0.0; m32 = 0.0; m33 = 1.0; 
}


void Matrix4f::mulTransposeRight(Matrix4f &m1, Matrix4f &m2) 
{
	// alias-safe way.
	set(
	    m1.m00*m2.m00 + m1.m01*m2.m01 + m1.m02*m2.m02 + m1.m03*m2.m03,
	    m1.m00*m2.m10 + m1.m01*m2.m11 + m1.m02*m2.m12 + m1.m03*m2.m13,
	    m1.m00*m2.m20 + m1.m01*m2.m21 + m1.m02*m2.m22 + m1.m03*m2.m23,
	    m1.m00*m2.m30 + m1.m01*m2.m31 + m1.m02*m2.m32 + m1.m03*m2.m33,

	    m1.m10*m2.m00 + m1.m11*m2.m01 + m1.m12*m2.m02 + m1.m13*m2.m03,
	    m1.m10*m2.m10 + m1.m11*m2.m11 + m1.m12*m2.m12 + m1.m13*m2.m13,
	    m1.m10*m2.m20 + m1.m11*m2.m21 + m1.m12*m2.m22 + m1.m13*m2.m23,
	    m1.m10*m2.m30 + m1.m11*m2.m31 + m1.m12*m2.m32 + m1.m13*m2.m33,

	    m1.m20*m2.m00 + m1.m21*m2.m01 + m1.m22*m2.m02 + m1.m23*m2.m03,
	    m1.m20*m2.m10 + m1.m21*m2.m11 + m1.m22*m2.m12 + m1.m23*m2.m13,
	    m1.m20*m2.m20 + m1.m21*m2.m21 + m1.m22*m2.m22 + m1.m23*m2.m23,
	    m1.m20*m2.m30 + m1.m21*m2.m31 + m1.m22*m2.m32 + m1.m23*m2.m33,
	    
	    m1.m30*m2.m00 + m1.m31*m2.m01 + m1.m32*m2.m02 + m1.m33*m2.m03,
	    m1.m30*m2.m10 + m1.m31*m2.m11 + m1.m32*m2.m12 + m1.m33*m2.m13,
	    m1.m30*m2.m20 + m1.m31*m2.m21 + m1.m32*m2.m22 + m1.m33*m2.m23,
	    m1.m30*m2.m30 + m1.m31*m2.m31 + m1.m32*m2.m32 + m1.m33*m2.m33
	    );
}

void Matrix4f::mul(Matrix4f *m1) 
{
	mul(this, m1);
}

 
void Matrix4f::mul(Matrix4f *m1, Matrix4f *m2) 
{
	// alias-safe way
	set(
	    m1->m00*m2->m00 + m1->m01*m2->m10 + m1->m02*m2->m20 + m1->m03*m2->m30,
	    m1->m00*m2->m01 + m1->m01*m2->m11 + m1->m02*m2->m21 + m1->m03*m2->m31,
	    m1->m00*m2->m02 + m1->m01*m2->m12 + m1->m02*m2->m22 + m1->m03*m2->m32,
	    m1->m00*m2->m03 + m1->m01*m2->m13 + m1->m02*m2->m23 + m1->m03*m2->m33,

	    m1->m10*m2->m00 + m1->m11*m2->m10 + m1->m12*m2->m20 + m1->m13*m2->m30,
	    m1->m10*m2->m01 + m1->m11*m2->m11 + m1->m12*m2->m21 + m1->m13*m2->m31,
	    m1->m10*m2->m02 + m1->m11*m2->m12 + m1->m12*m2->m22 + m1->m13*m2->m32,
	    m1->m10*m2->m03 + m1->m11*m2->m13 + m1->m12*m2->m23 + m1->m13*m2->m33,

	    m1->m20*m2->m00 + m1->m21*m2->m10 + m1->m22*m2->m20 + m1->m23*m2->m30,
	    m1->m20*m2->m01 + m1->m21*m2->m11 + m1->m22*m2->m21 + m1->m23*m2->m31,
	    m1->m20*m2->m02 + m1->m21*m2->m12 + m1->m22*m2->m22 + m1->m23*m2->m32,
	    m1->m20*m2->m03 + m1->m21*m2->m13 + m1->m22*m2->m23 + m1->m23*m2->m33,

	    m1->m30*m2->m00 + m1->m31*m2->m10 + m1->m32*m2->m20 + m1->m33*m2->m30,
	    m1->m30*m2->m01 + m1->m31*m2->m11 + m1->m32*m2->m21 + m1->m33*m2->m31,
	    m1->m30*m2->m02 + m1->m31*m2->m12 + m1->m32*m2->m22 + m1->m33*m2->m32,
	    m1->m30*m2->m03 + m1->m31*m2->m13 + m1->m32*m2->m23 + m1->m33*m2->m33
	);
}

void Matrix4f::set(float m00, float m01, float m02, float m03, 
		  float m10, float m11, float m12, float m13,
		  float m20, float m21, float m22, float m23,
		  float m30, float m31, float m32, float m33) 
{
	this->m00 = m00; this->m01 = m01; this->m02 = m02; this->m03 = m03;
	this->m10 = m10; this->m11 = m11; this->m12 = m12; this->m13 = m13;
	this->m20 = m20; this->m21 = m21; this->m22 = m22; this->m23 = m23;
	this->m30 = m30; this->m31 = m31; this->m32 = m32; this->m33 = m33;
}

