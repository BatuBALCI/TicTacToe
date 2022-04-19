#pragma once
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

class Mesh;

class Utility
{
public:
	static void calcAvarageNormals(unsigned int* indices, unsigned int indiceCount, float* vertices, unsigned int verticesCount, unsigned int vLength, unsigned int normalOffset);
};

