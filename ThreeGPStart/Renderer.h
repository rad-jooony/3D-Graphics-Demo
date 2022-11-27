#pragma once

#include "ExternalLibraryHeaders.h"

#include "Helper.h"
#include "Mesh.h"
#include "Camera.h"


struct Model
{
	GLuint m_VAO{ 0 };

	GLuint m_numElements{ 0 };

	GLuint m_tex{ 0 };

	glm::vec3 m_translation;

	glm::vec3 m_rotation;
};

class Renderer
{
private:
	// Program object - to host shaders
	GLuint m_program{ 0 };

	std::vector<Model> modelVector;

	bool m_wireframe{ false };
	bool m_cullFace{ true };	
public:
	Renderer();
	~Renderer();

	// Draw GUI
	void DefineGUI();

	// Create the program. This is the compiled shaders.
	bool CreateProgram();

	// Create and / or load geometry, this is like 'level load'
	bool InitialiseGeometry();

	// Render the scene
	void Render(const Helpers::Camera& camera, float deltaTime);
};

