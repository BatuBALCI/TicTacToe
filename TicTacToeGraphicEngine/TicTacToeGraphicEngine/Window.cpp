#include "Window.h"

Window::Window()
{
	WIDTH = 800;
	HEIGHT = 600;

    for (size_t i = 0; i < 1024; i++) 
    {
        keys[i] = 0;
    }

    xChange = 0.0f;
    yChange = 0.0f;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	WIDTH = windowWidth;
	HEIGHT = windowHeight;

    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
    xChange = 0.0f;
    yChange = 0.0f;
}

int Window::Initialize() {
    // Initializze glfw
    if (!glfwInit())
    {
        printf("GLFW init is failed");
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    // OpenGl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // This profile determines how opengl treats the code. For examploe Core Profile doesn't allow you to have backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // open main window, 1 Width, 2- Height, 3- title, 4-Windowed mode, 5- Shared
    mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "TicTacToe", NULL, NULL);
    if (!mainWindow)
    {
        printf("GLFWwindow creation failed");
        glfwTerminate();
        return 1;
    }

    // Get buffer size information
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    // This function states which window is the current used window which is created.
    glfwMakeContextCurrent(mainWindow);

    // Handle key and mouse inputs
    createCallbacks();
    // Call this function to make curser invisible on the open window by 
    // passing GLFW_CURSOR_DISABLED parameters.
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        printf("Glew init failed");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // Enable depth test.
    glEnable(GL_DEPTH_TEST);

    // Set up viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    // This functions sets the window user pointer to the class.
    // The first input is the current window, the second input is the user class of the window
    glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks() 
{
    // It sets the key callbacks from given mainwindow to respective fields.
    glfwSetKeyCallback(mainWindow, handleKeys);
    // It sets the mouse callbacks from given mainwindow to respective fields.
    glfwSetCursorPosCallback(mainWindow, handleMouse);
    // It sets the mouse botton callbacks from given mainwindow to respective fields.
    glfwSetMouseButtonCallback(mainWindow, handleMouseBottons);
}

GLfloat Window::GetXChange() 
{
    GLfloat theChange = xChange;
    xChange = 0.0f;
    return theChange;
}

GLfloat Window::GetYChange() 
{
    GLfloat theChange = yChange;
    yChange = 0.0f;
    return theChange;
}

GLfloat* Window::GetMouseLocation()
{
    return clickedPosition;
}

GLuint Window::GetClickedStatus()
{
    return clickedStatus;
}

GLuint Window::GetClickedButton()
{
    return clickedButton;
}

GLFWwindow* Window::GetMainWindow()
{
    return mainWindow;
}


// this order of input is important for glfwSEtKeyCallBack function to handle pressed key.
void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {

    // get functions gets the window user pointer. By this pointer we can accsess the window
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    // check if the pushed key is the escape.
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        // if the escape button is pressed close the window
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // Check if the pressed key is valid and if the valid key is pressed find key inside of the array and make the cell as true. 
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            theWindow->keys[key] = true;
        else if (action == GLFW_RELEASE)
            theWindow->keys[key] = false;
    }
};

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos) 
{ 
    // get functions gets the window user pointer. By this pointer we can accsess the window
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(theWindow->mouseFirstMoved)
    {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = true;
    }

    theWindow->xChange = xPos - theWindow->lastX;
    // to avoid inverted controls substruct current location from the last.
    theWindow->yChange = theWindow->lastY - yPos;

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
}

void Window::handleMouseBottons(GLFWwindow* window, int button, int action, int mods)
{
    // get functions gets the window user pointer. By this pointer we can accsess the window
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if ((button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) || (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS))
    {   
        theWindow->clickedPosition[0] = theWindow->lastX;
        theWindow->clickedPosition[1] = theWindow->lastY;
        theWindow->clickedStatus = action;
        theWindow->clickedButton = button;
    }
    if ((button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) || (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE))
    {
        theWindow->clickedStatus = action;
    }
}

Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
