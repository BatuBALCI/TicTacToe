#pragma once
#include <glm/glm.hpp>

class Utility
{
public:
	static void calcAvarageNormals(unsigned int* indices, unsigned int indiceCount, float* vertices, unsigned int verticesCount, unsigned int vLength, unsigned int normalOffset);
};

