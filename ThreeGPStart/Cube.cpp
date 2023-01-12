#include "Cube.h"

Model Cube::makeCube()
{
	Model cube;

	cube.m_translation = translation;

	GLuint positionsVBO;
	glGenBuffers(1, &positionsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertecies.size(), vertecies.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint coloursVBO;
	glGenBuffers(1, &coloursVBO);
	glBindBuffer(GL_ARRAY_BUFFER, coloursVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colours.size(), colours.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint elemEBO;
	glGenBuffers(1, &elemEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * elements.size(), elements.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	cube.m_numElements = elements.size();

	glGenVertexArrays(1, &cube.m_VAO);
	glBindVertexArray(cube.m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0, // attribute
		3, // num of componants
		GL_FLOAT, // type
		GL_FALSE, // ignore this
		0, // stride
		(void*)0 // array buffer offset 
	);

	glBindBuffer(GL_ARRAY_BUFFER, coloursVBO);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1, // attribute
		3, // num of componants
		GL_FLOAT, // type
		GL_FALSE, // ignore this
		0, // stride
		(void*)0 // array buffer offset 
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemEBO);

	glBindVertexArray(0);

	return cube;
}
