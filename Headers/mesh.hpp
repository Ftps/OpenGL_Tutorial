#ifndef MESH_HPP
#define MESH_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& textCoord)
	{
		this->pos = pos;
		this->textCoord = textCoord;
	}
	inline glm::vec3 getPos() { return pos; }
	inline glm::vec2 getTex() { return textCoord; }
private:
	glm::vec3 pos;
	glm::vec2 textCoord;
};

class Mesh{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	~Mesh();
	void Draw();
private:
	enum{
		POSITION_VB,
		TEXCOORD_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffer[NUM_BUFFERS];
	unsigned int drawCount;
};

#endif
