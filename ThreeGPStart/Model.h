#pragma once
#include "ExternalLibraryHeaders.h"

struct Model
{
	GLuint m_VAO{ 0 };

	GLuint m_numElements{ 0 };

	GLuint m_tex{ 0 };

	glm::vec3 m_translation;

	glm::vec3 m_rotation;
};

