#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <glew.h>

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColourLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDiffuseColourLocation();
	GLuint GetDirectionLocation();	
	GLuint GetShininessLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetEyePositionLocation();

	void UseShader();
	void ClearShader();

	~Shader();
private:
	// These variables will be id of the uniform variable and these variables will be defined in shader code. The feature of these variables
	// are that they can be used by every vertex or every other thing because they doen't change during the process of the shader.
	GLuint uniformModel, uniformProjection, uniformView, uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDiffuseColour, uniformDirection, uniformShininess, uniformSpecularIntensity, uniformEyePosition;


	GLuint shaderID;
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

};

