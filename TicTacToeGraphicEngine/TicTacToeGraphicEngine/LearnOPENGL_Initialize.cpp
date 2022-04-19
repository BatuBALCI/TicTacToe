#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <glew.h>
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

#include "Game.h"
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

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// convert angles to radian
const float toRadians = 3.14159265f / 180.0f;

// Vertex Shader
static const char* vShader = "../Shaders/shader.vert";

// Fragmet Shader
static const char* fShader = "../Shaders/shader.frag";

// File location of the vertex coordinates
static const char* stripVertices = "../Inputs/strip.inp";

// File location of the indices
static const char* stripIndices = "../Inputs/stripIndices.inp";

// File location of the vertex coordinates
static const char* xVertices = "../Inputs/objectX.inp";

// File location of the indices
static const char* xIndices = "../Inputs/objectXindices.inp";
// File location of the vertex coordinates
static const char* oVertices = "../Inputs/objectO.inp";

// File location of the indices
static const char* oIndices = "../Inputs/objectOindices.inp";

void CreateShader() {
    Shader* shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(shader1);
}

void RestartGame(Game& game, std::vector<std::pair<float, float>>& offsetPairO, std::vector<std::pair<float, float>>& offsetPairX)
{
    game.~Game();
    game = Game();
    if (offsetPairX.size() > 0)
        offsetPairX.clear();
    if (offsetPairO.size() > 0)
        offsetPairO.clear();
}

int main(void)
{
    Window window = Window(WIDTH, HEIGHT);
    window.Initialize();

    GLint bufferWidth = window.GetBufferWidth();
    GLint bufferHeight = window.GetBufferHeight();

    // call functions to draw triangle.
    //CreateObject();
    Utility::createStrip(stripVertices, stripIndices, meshList);
    Utility::createXO(oVertices, oIndices, meshList);
    Utility::createXO(xVertices, xIndices, meshList);
    CreateShader();

    GLuint uniformModel = 0;

    Game newGame = Game::Game();

    float PosX = 0.0;
    float PosY = 0.0;

    std::vector<std::pair<float, float>> offsetPairX;
    std::vector<std::pair<float, float>> offsetPairO;

    unsigned short xPos;
    unsigned short yPos;

    // A lambda function to update the x and y positions according to the mouse clicks.
    auto UpdatePositions = [&](GLuint type)
    {
        if (window.GetMouseLocation()[0] != PosX || window.GetMouseLocation()[1] != PosY)
        {
            PosX = window.GetMouseLocation()[0];
            PosY = window.GetMouseLocation()[1];
            if (type == 1) {
                Utility::FindOffset(offsetPairX, PosX, PosY, bufferWidth, bufferHeight, xPos, yPos);
                if (!newGame.IsUpdatable(xPos, yPos)) {
                    offsetPairX.pop_back();
                    return;
                }
            }
            else if (type == 2) {
                Utility::FindOffset(offsetPairO, PosX, PosY, bufferWidth, bufferHeight, xPos, yPos);
                if (!newGame.IsUpdatable(xPos, yPos)) {
                    offsetPairO.pop_back();
                    return;
                }
            }
            newGame.updateGame(xPos, yPos, type);
        }
    };

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
        
        if (window.GetKeys()[GLFW_KEY_R] == true) 
            RestartGame(newGame, offsetPairO, offsetPairX);

        // According to the mouse clicks update the game table and the draw offset.
        if (window.GetClickedStatus() == 1)
            UpdatePositions(window.GetClickedButton() + 1);

        // Set every pixel in the frame buffer to the current clear color.
        // alpha means visibility
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // This function opens the shader inside the program and until it closes program uses attached shader
        shaderList.at(0)->UseShader();

        uniformModel = shaderList.at(0)->GetModelLocation();

        Utility::createGrid(meshList, uniformModel);
        for (int i = 0; i < offsetPairX.size(); i++)
        {
            Utility::drawX(meshList, uniformModel, offsetPairX.at(i).first, offsetPairX.at(i).second);
        }

        for (int i = 0; i < offsetPairO.size(); i++)
        {
            Utility::drawO(meshList, uniformModel, offsetPairO.at(i).first, offsetPairO.at(i).second);
        }
        

        glUseProgram(0);
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (newGame.IsWinner() || (offsetPairX.size() + offsetPairO.size()) == 9) {
            ImGui::Begin("TicTacToe");

            ImGui::SetNextWindowContentSize({ 280,600 });

            if(newGame.IsWinner() == true)
                ImGui::Text("You Won");
            else
                RestartGame(newGame, offsetPairO, offsetPairX);

            ImGui::SetWindowPos({ 400,400 });
            ImGui::SetWindowSize({ 280,280 });

            if (ImGui::RadioButton("Restart", true))
                RestartGame(newGame, offsetPairO, offsetPairX);

            if (ImGui::RadioButton("Exit", true))
                glfwSetWindowShouldClose(window.GetMainWindow(), GL_TRUE);

            ImGui::End();
        }

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.swapBuffers();
    }
    return 0;
}

