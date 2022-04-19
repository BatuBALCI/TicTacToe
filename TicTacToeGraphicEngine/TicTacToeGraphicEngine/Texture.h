#pragma once

#include <glew.h>
#include <stb_image.h>
class __declspec(dllexport) Texture
{
public:
	Texture();
	Texture(const char* fileLoc);
	void LoadTexture();
	void UseTexture();
	void ClearTexture();
	~Texture();
private:
	// This id is going to be used in texture units to be reached by samplers.
	GLuint textureID;
	// width and height of the texture image
	int width, height, bitDepth;
	// char array to hold file location.
	const char* fileLocation;
};

