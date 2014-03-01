
#pragma once

#include "ofMain.h"
#include "vecStructs.h"

class Matrix3f
{
public:
	float m00; //element 0 of row 0.
	float m10; //element 0 of row 1.
	float m20; //element 0 of row 2.

	float m01; //element 1 of row 0.
	float m11; //element 1 of row 1.
	float m21; //element 1 of row 2.

	float m02; //element 2 of row 0.	
	float m12; //element 2 of row 1.
	float m22; //element 2 of row 2.
	
	
	Matrix3f();
	void print();
	void setIdentity();
	void transpose();
	void transpose(Matrix3f &m1);
	void setTranslation(float x,float y);
	void rotZ(float angle);  
	void mulTransposeRight(Matrix3f &m1, Matrix3f &m2); 
	void mul(Matrix3f *m1); 
	void mul(float scalar);
	void mul(Matrix3f *m1, Matrix3f *m2);
	void applyScale(float sx, float sy) ;

	void mulTranslate(float x, float y);


	void set(float m00, float m01, float m02, 
		float m10, float m11, float m12,
		float m20, float m21, float m22); 
	void set(Matrix3f &m1); 
	ofVec2f transform(ofVec2f p);
	void mulRotate(float angle);


	void drawAxisLines();
	void mulScale(float sx, float sy);
};
