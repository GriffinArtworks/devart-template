#include "GLSLShaderUniform.h"

GLSLShaderUniform::GLSLShaderUniform()
{
	//shader = 0;
    name = "";
	type = 0;
	glID = -1;		
}


void GLSLShaderUniform::init(char *name, ShaderParamType type) 
{        
    this->name = name;
    this->type = type;
    allocateValueArray();
}


void GLSLShaderUniform::setParameter()
{
	if(glID == -1) return;
	if (type == SHADER_PARAM_TYPE_INT)		glUniform1iARB(glID, valueInt);
    else if (type == SHADER_PARAM_TYPE_FLOAT)glUniform1fARB(glID, valueFloat);
    else if (type == SHADER_PARAM_TYPE_VEC2) glUniform2fvARB(glID, 1, valueArray);
    else if (type == SHADER_PARAM_TYPE_VEC3) glUniform3fvARB(glID, 1, valueArray);
    else if (type == SHADER_PARAM_TYPE_VEC4) glUniform4fvARB(glID, 1, valueArray);
    else if (type == SHADER_PARAM_TYPE_MAT2) glUniformMatrix2fvARB(glID, 1, false, valueArray);
    else if (type == SHADER_PARAM_TYPE_MAT3) glUniformMatrix3fvARB(glID, 1, false, valueArray);
    else if (type == SHADER_PARAM_TYPE_MAT4) glUniformMatrix4fvARB(glID, 1, false, valueArray);
}

void GLSLShaderUniform::setShader(ofShader *shader)
{
//	this->shader = shader;
	glID = shader->getUniformLocation(name);        

}

void GLSLShaderUniform::genID() 
{
}

//Sets the parameter value when the type is int.
void GLSLShaderUniform::setValue(int value) 
{
	if (type == SHADER_PARAM_TYPE_INT) valueInt = value;
}

//Sets the parameter value when the type is float.
void GLSLShaderUniform::setValue(float value)
{
	if (type == SHADER_PARAM_TYPE_FLOAT) valueFloat = value;
}
    
// * Sets the parameter value for any type
void GLSLShaderUniform::setValues(float *values, int n)
{
	memcpy(&valueArray[0], values, valueArraySize*4);
}

// only for mat/vec array types
void GLSLShaderUniform::setValue(int ix, float value)
{
	valueArray[ix] = value;
}

// only for mat array types
void GLSLShaderUniform::setValue(int i, int j, float value)
{
	if ((i < 2) && (j < 2) && (type == SHADER_PARAM_TYPE_MAT2)) valueArray[2 * i + j] = value;
    else if ((i < 3) && (j < 3) && (type == SHADER_PARAM_TYPE_MAT3)) valueArray[3 * i + j] = value;
    else if ((i < 4) && (j < 4) && (type == SHADER_PARAM_TYPE_MAT4)) valueArray[4 * i + j] = value;
}

void GLSLShaderUniform::setValue(ofMatrix4x4 &mat)
{
	memcpy(&valueArray[0], mat.getPtr(), 16);
}


void GLSLShaderUniform::allocateValueArray()
{
	if (type == SHADER_PARAM_TYPE_VEC2) valueArraySize = 2;
    else if (type == SHADER_PARAM_TYPE_VEC3) valueArraySize = 3;
    else if (type == SHADER_PARAM_TYPE_VEC4) valueArraySize = 4;
    else if (type == SHADER_PARAM_TYPE_MAT2) valueArraySize = 4;
    else if (type == SHADER_PARAM_TYPE_MAT3) valueArraySize = 9;
    else if (type == SHADER_PARAM_TYPE_MAT4) valueArraySize = 16;
	else valueArraySize = 1;
}

   
