#pragma once
#include <stdio.h>
#include <glew.h>

#include <glfw3.h>

class __declspec(dllexport) Window
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
	GLfloat* GetMouseLocation();
	GLuint GetClickedStatus();
	GLuint GetClickedButton();
	GLFWwindow* GetMainWindow();

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
	// the position of the mouse when the mouse bottom is clicked.
	GLfloat clickedPosition[2];
	// click status of the mouse button.
	GLuint clickedStatus;
	// which mouse button is clicked.
	GLuint clickedButton;
	// check if the first movement of the curser.
	bool mouseFirstMoved;

	// this function creats the callback functions.
	void createCallbacks();

	// this function handles the pressed and released keys.
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	// this function handles the current curser position of the mouse.
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
	// this function handles the pressed mouse bottoms.
	static void handleMouseBottons(GLFWwindow* window, int button, int action, int mods);
};

