
#ifndef __MATRIX4F
#define __MATRIX4F

#include "ofMain.h"
#include "vecStructs.h"

class Matrix4f
{
public:
    float m00; //element 0 of row 0.
    float m01; //element 1 of row 0.
    float m02; //element 2 of row 0.
	float m03; //element 3 of row 0.
	
	float m10; //element 0 of row 1.
    float m11; //element 1 of row 1.
    float m12; //element 2 of row 1.
	float m13; //element 3 of row 1.
	
	float m20; //element 0 of row 2.
    float m21; //element 1 of row 2.
    float m22; //element 2 of row 2.
	float m23; //element 3 of row 2.
	
	float m30; //element 0 of row 3.
    float m31; //element 1 of row 3.
    float m32; //element 2 of row 3.
	float m33; //element 3 of row 3.

	Matrix4f();
	void print();
	void transformPoint(Vec3 *p); 
	void transformPoint(Vec3 *p, Vec3 *resp) ;
	void transformVector(Vec3 *v, Vec3 *resv) ;
	void setIdentity();
	void transpose();
	void transpose(Matrix4f &m1);
	void invert(Matrix4f &m1);
	void invert();
	float determinant();
	void setTranslation(float x,float y,float z);
	void rotX(float angle);
	void rotY(float angle); 
	void rotZ(float angle);  
	void mulTransposeRight(Matrix4f &m1, Matrix4f &m2); 
	void mul(Matrix4f *m1); 
	void mul(float scalar);
	void mul(Matrix4f *m1, Matrix4f *m2);
	void applyScale(float sx, float sy, float sz) ;
	void set(float m00, float m01, float m02, float m03, 
		  float m10, float m11, float m12, float m13,
		  float m20, float m21, float m22, float m23,
		  float m30, float m31, float m32, float m33); 
	void set(Matrix4f &m1); 
	
};

#endif