
#ifndef __FLOAT_BUFFER
#define __FLOAT_BUFFER

#include "ofMain.h"
#define DEFAULT_RESERVE_AMOUNT 100

class FloatBuffer{
public:

	float *farray;
	int n;
	int reservedSize;

	FloatBuffer()
	{
		farray = 0;
		n = 0;
		reserve(DEFAULT_RESERVE_AMOUNT);
	};

	void allocateSpace(int n)
	{
		reserve(n);
	};

	void add(float x)
	{
		if(n >= reservedSize) reserve(reservedSize * 1.1);      // if we hit limit, increase reserve by 10%
		farray[n++]      = x;
	};

	void add(float x, float y) 
	{
		if(n >= reservedSize) reserve(reservedSize * 1.1);      // if we hit limit, increase reserve by 10%
		farray[n++]      = x;
		farray[n++]      = y;
	};

	void add(float x, float y, float z) 
	{
		if( n >= reservedSize) reserve(reservedSize * 1.1);      // if we hit limit, increase reserve by 10%
		farray[n++]      = x;
		farray[n++]      = y;
		farray[n++]      = z;
	};

	
	inline void reserve(int reservedSize) 
	{
		//printf("ofxMSAShape3D::reserve( %i )\n", reservedSize);
		this->reservedSize = reservedSize;
		farray	= (float*)realloc(farray, reservedSize * sizeof(float));
		reset();
	}
	
	inline void reset() 
	{
		n = 0;
	}
};

# endif