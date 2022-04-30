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
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

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


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.GetMainWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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


        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        ImGui::Render();

        // get keys from window and pass it into keyControl method to control the camera.
        camera.keyControl(window.GetKeys(), deltaTime);
        // get xChange and yChange values from window and pass it into mouseControl method to control the camera.
        camera.mouseControl(window.GetXChange(), window.GetYChange());

        // Set every pixel in the frame buffer to the current clear color.
        // alpha means visibility
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
        // First apply translation than apply rotation glm automatically combine this two movement.
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
        model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        projection = glm::perspective(30.0f, (GLfloat)bufferWidth/(GLfloat)bufferHeight, 0.1f, 100.0f);
        // Since we have pointer of a matrix we didn't directly pass model object we pass the pointer of it.
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
        glUniformMatrix4fv(uniformModel,1,GL_FALSE,glm::value_ptr(model));
        // all created object before renderMesh function will use this texture.
        brickTexture.UseTexture();
        // use lights for the objects that are going to be rendered.
        mainLight.UseLight(uniformAmbientIntensityLocation, uniformAmbientColourLocation);
        diffuseLight.UseLight(uniformDiffuseIntensityLocation, uniformDiffuseColourLocation, uniformDirectionLocation);
        // material.UseMaterial(uniformSpecularIntensityLocation, uniformShininessLocation);
        // call renderMesh function to draw the element on the screen.
        meshList.at(0)->RenderMesh();
        
        glUseProgram(0);

        window.swapBuffers();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}

