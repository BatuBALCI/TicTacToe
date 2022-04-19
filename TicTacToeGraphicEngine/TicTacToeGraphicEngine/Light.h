#pragma once

#include <glm/glm.hpp>
#include <glew.h>
// Base class of the all light types.
class __declspec(dllexport) Light
{
protected:
	// this is the colour of the light, for example if the light doesn't have red colour inside
	// then the red object won't appear.
	glm::vec3 colour;
	// Intensity of the light.
	GLfloat intensity;
};

class AmbientLight : Light
{
public:
	AmbientLight();

	AmbientLight(GLfloat red, GLfloat redgreen, GLfloat blue, GLfloat intensity);

	void UseLight(GLfloat intensityLocation, GLfloat ColourLocation);

	~AmbientLight();
};

class DiffuseLight : Light
{
public:
	DiffuseLight();

	DiffuseLight(GLfloat red, GLfloat redgreen, GLfloat blue,
		GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat intensity);

	void UseLight(GLfloat intensityLocation, GLfloat colourLocation, GLfloat directionLocation);

	~DiffuseLight();
private:
	// Direction of the light
	glm::vec3 direction;
};

