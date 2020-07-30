#include "texture.hpp"
#include "stb_image.hpp"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
	unsigned char* imgData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if(imgData == NULL){
		std::cerr << "Texture loading failed for texture " << fileName << std::endl;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// texture boundaries
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// texture filling

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

	stbi_image_free(imgData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture);
}
