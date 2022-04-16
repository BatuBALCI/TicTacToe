#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"
#include "Utility.h"
#include "Material.h"


// Window dimensions
const GLint WIDTH = 1080, HEIGHT = 1080;


std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Camera camera;

Texture brickTexture;
Texture soilTexture;

Material material;

AmbientLight mainLight;
DiffuseLight diffuseLight;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Those variables are going to use to transform the primitive incrementally;
bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.6f;
float triIncrement = 0.0003f;

// Those variables are going to use to rotate the primitive incrementally;
float curAngle = 0.0f;

// convert angles to radian
const float toRadians = 3.14159265f / 180.0f;

// Vertex Shader
static const char* vShader = "../Shaders/shader.vert";

// Fragmet Shader
static const char* fShader = "../Shaders/shader.frag";

// File location of the vertex coordinates
static const char* vertices = "../Inputs/vertex.inp";

// File location of the indices
static const char* indices = "../Inputs/index.inp";

void CreateObject() 
{
    Mesh* obj = new Mesh();

    auto vertexVector = Mesh::ReadFloatsFromFile(vertices);
    auto indexVector = Mesh::ReadFloatsFromFile(indices);

    obj->CreateMesh(vertexVector, indexVector, GL_TRIANGLES);

    meshList.push_back(obj);
    meshList.push_back(obj);
}

void CreateShader() {
    Shader* shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(shader1);
}

int main(void)
{
    Window window = Window(WIDTH, HEIGHT);
    window.Initialize();

    GLint bufferWidth = window.GetBufferWidth();
    GLint bufferHeight = window.GetBufferHeight();

    // call functions to draw triangle.
    CreateObject();
    CreateShader();

    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.2f);

    brickTexture = Texture((char*)("../Textures/thing.png"));
    brickTexture.LoadTexture();

    material = Material(1.0f, 100);

    mainLight = AmbientLight(1.0f, 1.0f, 1.0f, 0.4f);
    diffuseLight = DiffuseLight(1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 1.0f);

    GLuint uniformProjection = 0;
    GLuint uniformModel = 0;
    GLuint uniformView = 0;
    GLuint uniformAmbientIntensityLocation = 0;
    GLuint uniformAmbientColourLocation = 0;
    GLuint uniformDiffuseIntensityLocation = 0;
    GLuint uniformDiffuseColourLocation = 0;
    GLuint uniformDirectionLocation = 0;
    GLuint uniformShininessLocation = 0;
    GLuint uniformSpecularIntensityLocation = 0;
    GLuint uniformEyeLocationLocation = 0;


    // loop until the window close
    while (!window.GetShouldClose())
    {
        // get the time that is passed until now;
        GLfloat now = glfwGetTime();
        // find the passed time for the loop;
        deltaTime = now - lastTime;
        lastTime = now;
        
        // Get and handle user input events
        glfwPollEvents();

        // get keys from window and pass it into keyControl method to control the camera.
        camera.keyControl(window.GetKeys(), deltaTime);
        // get xChange and yChange values from window and pass it into mouseControl method to control the camera.
        camera.mouseControl(window.GetXChange(), window.GetYChange());

        if (direction)
        {
            triOffset += triIncrement;
        }
        else 
        {
            triOffset -= triIncrement;
        }

        if (abs(triOffset) >= triMaxOffset) 
        {
            direction = !direction;
        }

        curAngle += 0.05f;

        if (curAngle>=360)
        {
            curAngle -= 360;
        }

        // Set every pixel in the frame buffer to the current clear color.
        // alpha means visibility
        glClearColor(0.2f, 0.0f, 0.0f, 0.3f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // This function opens the shader inside the program and until it closes program uses attached shader
        shaderList.at(0)->UseShader();

        uniformModel = shaderList.at(0)->GetModelLocation();
        uniformProjection = shaderList.at(0)->GetProjectionLocation();
        uniformView = shaderList.at(0)->GetViewLocation();
        uniformAmbientIntensityLocation = shaderList.at(0)->GetAmbientIntensityLocation();
        uniformAmbientColourLocation = shaderList.at(0)->GetAmbientColourLocation();
        uniformDiffuseColourLocation = shaderList.at(0)->GetDiffuseColourLocation();
        uniformDiffuseIntensityLocation = shaderList.at(0)->GetDiffuseIntensityLocation();
        uniformDirectionLocation = shaderList.at(0)->GetDirectionLocation();
        uniformShininessLocation = shaderList.at(0)->GetShininessLocation();
        uniformSpecularIntensityLocation = shaderList.at(0)->GetSpecularIntensityLocation();
        uniformEyeLocationLocation = shaderList.at(0)->GetEyePositionLocation();

        glUniform3f(uniformEyeLocationLocation, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

        // 4x4 matrix with zeros;
        glm::mat4 model, projection;
        //First apply translation than apply rotation glm automatically combine this two movement.
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
        model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        projection = glm::perspective(30.0f, (GLfloat)bufferWidth/(GLfloat)bufferHeight, 0.1f, 100.0f);
        //Since we have pointer of a matrix we didn't directly pass model object we pass the pointer of it.
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
        glUniformMatrix4fv(uniformModel,1,GL_FALSE,glm::value_ptr(model));
        // all created object before renderMesh function will use this texture.
        brickTexture.UseTexture();
        // use lights for the objects that are going to be rendered.
        mainLight.UseLight(uniformAmbientIntensityLocation, uniformAmbientColourLocation);
        diffuseLight.UseLight(uniformDiffuseIntensityLocation, uniformDiffuseColourLocation, uniformDirectionLocation);
        //material.UseMaterial(uniformSpecularIntensityLocation, uniformShininessLocation);
        // call renderMesh function to draw the element on the screen.
        meshList.at(0)->RenderMesh();
        
        glUseProgram(0);

        window.swapBuffers();
    }

    return 0;
}

