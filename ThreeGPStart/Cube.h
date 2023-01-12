#pragma once

#include "ExternalLibraryHeaders.h"
#include "Renderer.h"
#include "ImageLoader.h"

class Cube
{
	public:
	std::vector<glm::vec3> vertecies = {

		//front triangle 1
		glm::vec3(-1.0,1.0,1.0), //0
		glm::vec3(-1.0,-1.0,1.0), //1
		glm::vec3(1.0,-1.0,1.0), //2

		//front triangle 2
		glm::vec3(1.0, -1.0, 1.0), //3
		glm::vec3(1.0,1.0,1.0), //4
		glm::vec3(-1.0,1.0,1.0), //5

		//right triangle 1
		glm::vec3(1.0,1.0,1.0), //6
		glm::vec3(1.0,-1.0,1.0), //7
		glm::vec3(1.0,-1.0,-1.0), //8

		//right triangle 2
		glm::vec3(1.0,-1.0,-1.0), //9
		glm::vec3(1.0,1.0,-1.0), //10
		glm::vec3(1.0,1.0,1.0), //11

		//back triangle 1 
		glm::vec3(1.0,1.0,-1.0), //12
		glm::vec3(1.0,-1.0,-1.0), //13
		glm::vec3(-1.0,-1.0,-1.0), //14

		//back triangle 2 
		glm::vec3(-1.0,-1.0,-1.0), //15
		glm::vec3(-1.0,1.0,-1.0), //16
		glm::vec3(1.0,1.0,-1.0), //17

		//left triangle 1
		glm::vec3(-1.0,-1.0,-1.0), //18
		glm::vec3(-1.0,-1.0,1.0), //19
		glm::vec3(-1.0,1.0,1.0), //20

		//left triangle 2
		glm::vec3(-1.0,1.0,1.0), //21
		glm::vec3(-1.0,1.0,-1.0), //22
		glm::vec3(-1.0,-1.0,-1.0), //23

		//top triangle 1
		glm::vec3(-1.0,1.0,-1.0), //24
		glm::vec3(-1.0,1.0,1.0), //25
		glm::vec3(1.0,1.0,1.0), //26

		//top triangle 2
		glm::vec3(1.0,1.0,1.0), //27
		glm::vec3(1.0,1.0,-1.0), //28
		glm::vec3(-1.0,1.0,-1.0), //29

		//bottom triangle 1
		glm::vec3(1.0,-1.0,-1.0), //30
		glm::vec3(1.0,-1.0,1.0), //31
		glm::vec3(-1.0,-1.0,1.0), //32

		//bottom triangle 2
		glm::vec3(-1.0,-1.0,1.0), //33
		glm::vec3(-1.0,-1.0,-1.0), //34
		glm::vec3(1.0,-1.0,-1.0), //35
	};

	std::vector<glm::vec3> colours = {
		glm::vec3(1.0,0.0,0.0), //0
		glm::vec3(1.0,0.0,0.0), //1
		glm::vec3(1.0,0.0,0.0), //2
		glm::vec3(1.0,0.0,0.0), //3
		glm::vec3(1.0,0.0,0.0), //4
		glm::vec3(1.0,0.0,0.0), //5

		glm::vec3(0.0,1.0,0.0), //6
		glm::vec3(0.0,1.0,0.0), //7
		glm::vec3(0.0,1.0,0.0), //8
		glm::vec3(0.0,1.0,0.0), //9
		glm::vec3(0.0,1.0,0.0), //10
		glm::vec3(0.0,1.0,0.0), //11

		glm::vec3(0.0,0.0,1.0), //12
		glm::vec3(0.0,0.0,1.0), //13
		glm::vec3(0.0,0.0,1.0), //14
		glm::vec3(0.0,0.0,1.0), //15
		glm::vec3(0.0,0.0,1.0), //16
		glm::vec3(0.0,0.0,1.0), //17

		glm::vec3(1.0,1.0,0.0), //18
		glm::vec3(1.0,1.0,0.0), //19
		glm::vec3(1.0,1.0,0.0), //20
		glm::vec3(1.0,1.0,0.0), //21
		glm::vec3(1.0,1.0,0.0), //22
		glm::vec3(1.0,1.0,0.0), //23

		glm::vec3(1.0,0.0,1.0), //24
		glm::vec3(1.0,0.0,1.0), //25
		glm::vec3(1.0,0.0,1.0), //26
		glm::vec3(1.0,0.0,1.0), //27
		glm::vec3(1.0,0.0,1.0), //28
		glm::vec3(1.0,0.0,1.0), //29

		glm::vec3(0.0,1.0,1.0), //30
		glm::vec3(0.0,1.0,1.0), //31
		glm::vec3(0.0,1.0,1.0), //32
		glm::vec3(0.0,1.0,1.0), //33
		glm::vec3(0.0,1.0,1.0), //34
		glm::vec3(0.0,1.0,1.0), //35
	};

	std::vector<GLuint> elements{
		0, 1, 2,
		3, 4, 5,
		//front

		6, 7, 8,
		9, 10, 11,
		//r side

		12, 13, 14,
		15, 16, 17,
		//back

		18, 19, 20,
		21, 22, 23,
		//l side

		24, 25, 26,
		27, 28, 29,
		//top

		30, 31, 32,
		33, 34, 35,
		//bottom
	};

	std::vector<glm::vec3> rotation = {
		glm::vec3(1, 1, 0)
	};

	glm::vec3 translation{ 0,0,0 };

	Model makeCube();

};

