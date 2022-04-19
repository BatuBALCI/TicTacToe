#pragma once
#include <glew.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Utility.h"

class __declspec(dllexport) Mesh
{
public:
	Mesh();
	~Mesh();

	void CreateMesh(std::vector<float> vertices, std::vector<float> indices, int type);
	void RenderMesh();
	void ClearMesh();
	static std::vector<float> ReadFloatsFromFile(const char* fileLocation);

	float* verts;
	unsigned int* inds;

private:
	GLuint VAO, VBO, IBO, dimension;
	GLsizei indexCount;
	GLsizei vertexCount;
	int type;
};

