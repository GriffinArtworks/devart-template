#ifndef __GLSL_SHADER_UNIFORM
#define __GLSL_SHADER_UNIFORM

#include "ofMain.h"
//#include "ofShader.h"

enum ShaderParamType{
	SHADER_PARAM_TYPE_INT,
	SHADER_PARAM_TYPE_FLOAT,
	SHADER_PARAM_TYPE_VEC2,
	SHADER_PARAM_TYPE_VEC3,
	SHADER_PARAM_TYPE_VEC4,
	SHADER_PARAM_TYPE_MAT2,
	SHADER_PARAM_TYPE_MAT3,
	SHADER_PARAM_TYPE_MAT4
} ;

class GLSLShaderUniform
{
public:
	//ofShader *shader;
    char *name;
    int type;
    int glID;
    
	int valueInt;
    float valueFloat;
    float valueArray[16];
	int valueArraySize;
 
	/////

	GLSLShaderUniform();
	void init(char *name, ShaderParamType type); 
	void setParameter();

	void genID();
	void setShader(ofShader *shader);
	
	void setValue(int value);			//Sets the parameter value when the type is int.
	void setValue(float value);			//Sets the parameter value when the type is float.
	void setValues(float *values, int n); //Sets the parameter value for any type
	void setValue(int ix, float value); // only for mat/vec array types
	void setValue(int i, int j, float value); // only for mat array types
	void setValue(ofMatrix4x4 &mat);

protected:
	void allocateValueArray();
};

#endif