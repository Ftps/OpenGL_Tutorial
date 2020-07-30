#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <GL/glew.h>

class Texture{
public:
	Texture(const std::string& fileName);
	~Texture();

	void Bind(unsigned int unit);
private:
	GLuint texture;
};

#endif
