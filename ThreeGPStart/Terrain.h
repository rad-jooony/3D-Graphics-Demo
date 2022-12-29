#pragma once
#include "ExternalLibraryHeaders.h"
#include "Renderer.h"
#include "ImageLoader.h"
class Terrain
{

public:
	bool noiseOn = true;
	std::vector<glm::vec3> vertsMovedUp;
	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> colours;
	std::vector<glm::vec2> texCoords;
	std::vector<GLuint> elements;

	glm::vec3 minValues{ -10,-10,-10 };
	glm::vec3 maxValues{ 10,10,10 };

	Model makeTerrain(int X, int Z);

};

