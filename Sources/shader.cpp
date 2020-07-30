#include "shader.hpp"
#include <fstream>
#include <iostream>

static std::string LoadShader(const std::string& fileName);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName)
{
	program = glCreateProgram();	// allocates memory in the GPU for our shader
	shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for(auto i = 0; i < NUM_SHADERS; ++i){
		glAttachShader(program, shaders[i]);
	}

	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "text");
	glBindAttribLocation(program, 2, "normal");

	glLinkProgram(program);
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Program failed to link:\n");

	glValidateProgram(program);
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Program is invalid:\n");

	uniform[TRANSFORM_U] = glGetUniformLocation(program, "transform");
}

Shader::~Shader()
{
	for(auto i = 0; i < NUM_SHADERS; ++i){
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(program);
}

void Shader::Bind()
{
	glUseProgram(program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model = camera.getViewProjection()*transform.getModel();

	glUniformMatrix4fv(uniform[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}


static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLength;

	if(shader == 0){
		std::cerr << "Error: Shader creation failed!" << std::endl;
	}

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLength = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, &shaderSourceStringLength);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed:\n");

	return shader;
}



static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file(fileName);
	std::string output, line;

	if(file.is_open()){
		while(file.good()){
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else{
		std::cerr << "Unable to open Shader file: " << fileName << std::endl;
	}

	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if(isProgram){
		glGetProgramiv(shader, flag, &success);
	}
	else{
		glGetShaderiv(shader, flag, &success);
	}

	if(success == GL_FALSE)
	{
		if(isProgram){
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
