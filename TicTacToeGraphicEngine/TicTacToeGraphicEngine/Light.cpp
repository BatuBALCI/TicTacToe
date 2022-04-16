#include "Light.h"

AmbientLight::AmbientLight()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	intensity = 1.0f;
}

AmbientLight::AmbientLight(GLfloat red, GLfloat redgreen, GLfloat blue, GLfloat intensity)
{
	this->colour = glm::vec3(red, redgreen, blue);
	this->intensity = intensity;
}

void AmbientLight::UseLight(GLfloat intensityLocation, GLfloat colourLocation)
{
	//Bind the location of the ambient intensity to the colours that we have 
	glUniform3f(colourLocation, colour.x, colour.y, colour.z);
	glUniform1f(intensityLocation, intensity);
}

AmbientLight::~AmbientLight()
{
}

DiffuseLight::DiffuseLight()
{
	this->colour = glm::vec3(1.0f, 1.0f, 1.0f);
	this->direction = glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f));
	this->intensity = 0.0f;
}

DiffuseLight::DiffuseLight(GLfloat red, GLfloat redgreen, GLfloat blue,
	GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat intensity)
{
	this->colour = glm::vec3(red, redgreen, blue);
	this->direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
	this->intensity = intensity;
}

void DiffuseLight::UseLight(GLfloat intensityLocation, GLfloat colourLocation, GLfloat directionLocation)
{
	//Bind the location of the ambient intensity to the colours that we have 
	glUniform3f(colourLocation, colour.x, colour.y, colour.z);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(intensityLocation, intensity);

}

DiffuseLight::~DiffuseLight()
{
}