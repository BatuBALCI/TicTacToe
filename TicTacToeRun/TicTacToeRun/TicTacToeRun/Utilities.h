#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Game.h>
#include <Player.h>
#include <Mesh.h>
#include <Shader.h>
#include <Window.h>
#include <Camera.h>
#include <Texture.h>
#include <Light.h>
#include <Material.h>

class Mesh;

class Utilities
{
public:
	static void createStrip(static const char* vertices, static const char* indices, std::vector<Mesh*>& meshList);

	static void createGrid(std::vector<Mesh*> meshList, GLuint uniformModel);

	static void createXO(static const char* vertices, static const char* indices, std::vector<Mesh*>& meshList);

	static void drawX(std::vector<Mesh*> meshList, GLuint uniformModel, float xOffset, float yOffset);

	static void drawO(std::vector<Mesh*> meshList, GLuint uniformModel, float xOffset, float yOffset);

	static void GetTypeAndNameForm(Player::Player* playerObj, Window& window, char* name, int* currentItems, const char* items[], const char* formName);
};