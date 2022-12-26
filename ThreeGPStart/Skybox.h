#pragma once

#include "ExternalLibraryHeaders.h"
#include "Renderer.h"
#include "ImageLoader.h"
class Skybox
{
public:

	Model skyBox;

	std::vector<glm::vec3> skyboxVertices =
	{
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),

		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),

		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0),

		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),

		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f, 1.0f, -1.0f),

		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f)
	};

	std::vector<GLuint> skyboxElements =
	{
		// right
		1,2,6,
		6,5,1,
		// left
		0,4,7,
		7,3,0,
		// top
		4,5,6,
		6,7,4,
		// bottom
		0,3,2,
		2,1,0,
		// back
		0,1,5,
		5,4,0,
		// front
		3,7,6,
		6,2,3
	};

	std::vector<std::string> skyboxFaces
	{
		"1.jpg",
		"2.jpg",
		"3.jpg",
		"4.jpg",
		"5.jpg",
		"6.jpg"
	};

	std::vector<std::string> skyboxFacesPaths
	{
		"Data\\Models\\Sky\\Mountains\\2.jpg",//right
		"Data\\Models\\Sky\\Mountains\\4.jpg",//left
		"Data\\Models\\Sky\\Mountains\\6.jpg",//top /
		"Data\\Models\\Sky\\Mountains\\5.jpg",//bot /
		"Data\\Models\\Sky\\Mountains\\3.jpg",//front /
		"Data\\Models\\Sky\\Mountains\\1.jpg"//back
	};

	Model MakeSkybox();
	
};

