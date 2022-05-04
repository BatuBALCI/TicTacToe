#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <comdef.h>

#include <glew.h>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "Utilities.h"

// Window dimensions
const GLint WIDTH = 1080, HEIGHT = 1080;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

// Vertex Shader
const char* vShader = "../../../TicTacToeGraphicEngine/Shaders/shader.vert";

// Fragmet Shader
const char* fShader = "../../../TicTacToeGraphicEngine/Shaders/shader.frag";

// File location of the vertex coordinates
const char* stripVertices = "../../../TicTacToeGraphicEngine/Inputs/strip.inp";

// File location of the indices
const char* stripIndices = "../../../TicTacToeGraphicEngine/Inputs/stripIndices.inp";

// File location of the vertex coordinates
const char* xVertices = "../../../TicTacToeGraphicEngine/Inputs/objectX.inp";

// File location of the indices
const char* xIndices = "../../../TicTacToeGraphicEngine/Inputs/objectXindices.inp";

// File location of the vertex coordinates
const char* oVertices = "../../../TicTacToeGraphicEngine/Inputs/objectO.inp";

// File location of the indices
const char* oIndices = "../../../TicTacToeGraphicEngine/Inputs/objectOindices.inp";

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
    //CreateObject();
    Utilities::createStrip(stripVertices, stripIndices, meshList);
    Utilities::createXO(oVertices, oIndices, meshList);
    Utilities::createXO(xVertices, xIndices, meshList);
    CreateShader();

    GLuint uniformModel = 0;

    // Create game object
    Game newGame = Game::Game();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.GetMainWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Combo Box Items.
    const char* items[2] = { "X", "0" };

    // Current item
    int item = 0;
    int* currentItem = &item;

    // Chars to return from input text function.
    char name1[20] = {0};
    char name2[20] = { 0 };

    // loop until the window close
    while (!window.GetShouldClose())
    {
        // Get and handle user input events
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        // Set every pixel in the frame buffer to the current clear color.
        // alpha means visibility
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Enter name and the click type for the players.
        if (newGame.player1->GetName().getValue() == L"") {
            Utilities::GetTypeAndNameForm(newGame.player1, window, name1, currentItem, items, "Player 1");
            continue;
        }
        else if (newGame.player2->GetName().getValue() == L"")
        {
            Utilities::GetTypeAndNameForm(newGame.player2, window, name2, currentItem, items, "Player 2");
            continue;
        }

        if (window.GetKeys()[GLFW_KEY_R] == true)
            newGame.RestartGame();

        // According to the mouse clicks update the game table and the draw offset.
        if (window.GetClickedStatus() == 1 && !newGame.IsWinner())
            newGame.UpdatePositions(window.GetClickedButton() + 1, bufferWidth, bufferHeight, window.GetMouseLocation()[0], window.GetMouseLocation()[1]);

        // This function opens the shader inside the program and until it closes program uses attached shader
        shaderList.at(0)->UseShader();

        uniformModel = shaderList.at(0)->GetModelLocation();

        Utilities::createGrid(meshList, uniformModel);
        for (int i = 0; i < newGame.GetOffsetPairX().size(); i++)
        {
            Utilities::drawX(meshList, uniformModel, newGame.GetOffsetPairX().at(i).first, newGame.GetOffsetPairX().at(i).second);
        }

        for (int i = 0; i < newGame.GetOffsetPairO().size(); i++)
        {
            Utilities::drawO(meshList, uniformModel, newGame.GetOffsetPairO().at(i).first, newGame.GetOffsetPairO().at(i).second);
        }

        glUseProgram(0);

        ImGui::NewFrame();

        if (newGame.IsWinner() || (newGame.GetOffsetPairX().size() + newGame.GetOffsetPairO().size()) == 9) {
            ImGui::Begin("TicTacToe");

            ImGui::SetNextWindowContentSize({ 280,600 });

            if (newGame.IsWinner() == true) {
                if (window.GetClickedButton() == newGame.player1->GetType().getValue())
                    ImGui::Text(_bstr_t(newGame.player1->GetName().getValue().c_str()) + " Won");
                else if(window.GetClickedButton() == newGame.player2->GetType().getValue())
                    ImGui::Text(_bstr_t(newGame.player2->GetName().getValue().c_str()) + " Won");
            }
            else
                newGame.RestartGame();

            ImGui::SetWindowPos({ (float)bufferWidth/2 -140, (float)bufferHeight/2 -140});
            ImGui::SetWindowSize({ 280,280 });

            if (ImGui::RadioButton("Restart", true))
                newGame.RestartGame();

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

