

#ifndef __GL_TEXTURED_POINT
#define __GL_TEXTURED_POINT

#include "ofMain.h"
#define GL_TEXTURE_POINT_MAX_POINTS 10
class GLTexturedPoint
{
public:
	float x, y, z, dx, dy, dz;
    float s[GL_TEXTURE_POINT_MAX_POINTS];
	float t[GL_TEXTURE_POINT_MAX_POINTS];
	int ntex;

	GLTexturedPoint()
	{
		x = y = z = 0.0f;
		dx = dy = dz = 0.0f;
		ntex = 1;
		setTexCoords(0,0,0);
	};

	void copyFrom(GLTexturedPoint *p)
	{
		x = p->x; y = p->y; z = p->z;
		dx = p->dx; dy = p->dy; dz = p->dz;
		ntex = p->ntex;
		for(int i=0;i<ntex;i++)
		{
			s[i] = p->s[i];
			t[i] = p->t[i];
		}
	};

	void setDeltaVertex(float dx, float dy, float dz)
    {
		this->dx = dx;
		this->dy = dy;
		this->dz = dz;
	};

	// use pixel grid for textureIX
	void setTexCoordsAsGridMode(int ix)
    {
        if (ix < ntex)
        {
			this->s[ix] = -1;
            this->t[ix] = -1;
        }
    };

	void setTexCoords(int ix, float s, float t)
    {
        if (ix < ntex)
        {
			this->s[ix] = s;
            this->t[ix] = t;
        }
    };
    
	
};

#endif