#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMovementSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	movementSpeed = startMovementSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime;
	
	// Ýf checks below checks the pressed key values and according to these value control the movement.
	if (keys[GLFW_KEY_W]) 
	{
		position += front * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		position += right * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		position -= right * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange) 
{
	xChange = xChange * turnSpeed;
	yChange = yChange * turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	update();
}

glm::mat4 Camera::CalculateViewMatrix() 
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition() 
{
	return position;
}

void Camera::update() 
{
	// Calculate front direction of the camera
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	// normalize the front vector
	front = glm::normalize(front);

	// cross product front with the world up vector to find right.
	right = glm::normalize(glm::cross(front, worldUp));
	// cross product right with the front vector to find up.
	up = glm::normalize(glm::cross(right, front));


}

Camera::~Camera()
{
}