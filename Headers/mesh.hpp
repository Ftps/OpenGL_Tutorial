#ifndef MESH_HPP
#define MESH_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "obj_loader.hpp"

class Vertex{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& textCoord, const glm::vec3& normal = glm::vec3(0,0,0))
	{
		this->normal = normal;
		this->pos = pos;
		this->textCoord = textCoord;
	}
	inline glm::vec3 getPos() { return pos; }
	inline glm::vec2 getTex() { return textCoord; }
	inline glm::vec3 getNor() { return normal; }
private:
	glm::vec3 pos;
	glm::vec2 textCoord;
	glm::vec3 normal;
};

class Mesh{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numInd);
	Mesh(const std::string& fileName);
	~Mesh();
	void Draw();
private:
	enum{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffer[NUM_BUFFERS];
	unsigned int drawCount;

	void initMesh(const IndexedModel& model);
};

#endif
