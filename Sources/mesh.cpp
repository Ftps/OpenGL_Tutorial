#include "mesh.hpp"
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	drawCount = numVertices;

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> text;
	positions.reserve(numVertices);
	text.reserve(numVertices);

	for(auto i = 0; i < numVertices; ++i){
		positions.push_back(vertices[i].getPos());
		text.push_back(vertices[i].getTex());
	}

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(text[0]), &text[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, drawCount);
	glBindVertexArray(0);
}
