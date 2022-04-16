#include "Texture.h"

Texture::Texture()
{
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = "";
}

Texture::Texture(const char* fileLoc)
{
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = fileLoc;
}

void Texture::LoadTexture()
{
	// unsigned char array is mostly use for storing image data.
	// stbi_load data takes 5 inputs. The first one is the location of the file to be loaded.
	// second, third and fourth ones are the references of the width, height and bitDepth parameters
	// ,respectively. Those three parameters are going to be updatep in stbi_load() file.
	unsigned char *texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);

	if (!texData)
	{
		printf("Failed to find : %s\n", fileLocation);
		return;
	}
	// First input is the number of the created textures, the second one is the id of the created textures.
	// glGenTextures method generates a texture and returns the id of that texture.
	glGenTextures(1, &textureID);
	// glBindTexture method binds the texture.
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Wraping the texture.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Filter the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// add image to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	// Generate mipmap for rendereing texture at different distance.
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind the texture.
	glBindTexture(GL_TEXTURE_2D, 0);

	// free the memory from the image.
	stbi_image_free(texData);
}

void Texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::ClearTexture() 
{
	// delete the dexture.
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = "";
}

Texture::~Texture()
{
	ClearTexture();
}