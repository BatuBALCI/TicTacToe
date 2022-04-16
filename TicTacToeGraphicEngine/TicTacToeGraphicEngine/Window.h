#pragma once
#include <stdio.h>
#include <glew.h>

#include <glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int Initialize();

	GLint GetBufferWidth() { return bufferWidth; }
	GLint GetBufferHeight() { return bufferHeight; }

	bool GetShouldClose(){ return glfwWindowShouldClose(mainWindow); }

	bool* GetKeys() { return keys; }

	GLfloat GetXChange();
	GLfloat GetYChange();


	void swapBuffers() {        
		// it swaps the non visible buffer with visible ones
		glfwSwapBuffers(mainWindow);
	}

	~Window();
private:
	// Window dimensions
	GLint WIDTH = 1080, HEIGHT = 1080;

	GLFWwindow* mainWindow;

	// Get buffer size information
	GLint bufferWidth, bufferHeight;

	// It holds the push info about all of the button combinations on the keyboard
	bool keys[1024];

	// last x poisition of the mouse curser
	GLfloat lastX;
	// last ypoisition of the mouse curser
	GLfloat lastY;
	// poisiton change of the curse in x direction
	GLfloat xChange;
	// poisiton change of the curse in y direction
	GLfloat yChange;
	// check if the first movement of the curser.
	bool mouseFirstMoved;

	// this function creats the callback functions.
	void createCallbacks();

	// this function handles the pressed and released keys.
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	// this function handles the current curser position of the mouse.
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);

};

