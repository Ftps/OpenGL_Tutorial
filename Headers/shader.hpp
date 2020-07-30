#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <GL/glew.h>
#include "transform.hpp"
#include "camera.hpp"

class Shader{
public:
	Shader(const std::string& fileName);
	~Shader();
	void Bind();
	void Update(const Transform& transform, const Camera& camera);
private:
	static const unsigned int NUM_SHADERS = 2;
	enum{
		TRANSFORM_U,

		NUM_TRANSFORM
	};

	GLuint program;
	GLuint shaders[NUM_SHADERS];
	GLuint uniform[NUM_TRANSFORM];
};

#endif
