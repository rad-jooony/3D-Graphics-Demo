#pragma once

#include "ExternalLibraryHeaders.h"

#include "Helper.h"
#include "Mesh.h"
#include "Camera.h"


struct Model
{
	GLuint m_VAO{ 0 };

	GLuint m_VAO2{ 0 };

	GLuint m_numElements{ 0 };

	GLuint m_tex{ 0 };

	glm::vec3 m_translation{ 0 };

	glm::vec3 m_rotation{ 0 };
};

class Renderer
{
private:
	// Program object - to host shaders
	GLuint m_program{ 0 };
	GLuint m_programSkybox{ 0 };
	GLuint m_programCube{ 0 };


	Model skyBoxModel;
	std::vector<Model> modelVector;
	Model cubeModel;

	bool m_wireframe{ false };
	bool m_cullFace{ true };	
public:
	Renderer();
	~Renderer();

	// Draw GUI
	void DefineGUI();

	// Create the program. This is the compiled shaders.
	bool CreateProgram();
	bool CreateProgramSkybox();
	bool CreateProgramCube();

	// Create and / or load geometry, this is like 'level load'
	bool InitialiseGeometry();

	// Render the scene
	void Render(const Helpers::Camera& camera, float deltaTime);
};

