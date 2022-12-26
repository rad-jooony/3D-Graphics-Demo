#pragma once

#include "ExternalLibraryHeaders.h"
#include "Renderer.h"
#include "ImageLoader.h"

class AquaPig
{
private:


public:

	std::vector<std::string> AquaPigObjects = {
		"Data\\Models\\AquaPig\\hull.obj",
		"Data\\Models\\AquaPig\\gun_base.obj",
		"Data\\Models\\AquaPig\\gun.obj",
		"Data\\Models\\AquaPig\\wing_left.obj",
		"Data\\Models\\AquaPig\\wing_right.obj",
		"Data\\Models\\AquaPig\\propeller.obj",
	};
	std::vector<glm::vec3> AquaPigTranslation = {
		glm::vec3(0, 0, 0),			//hull
		glm::vec3(0, 0.569, -1.866),		//gun_base
		glm::vec3(0, 1.506 + 0.569, 0.644 - 1.866),	//gun --- manually applied after gunbase
		glm::vec3(2.231, 0.272, -2.663),	//wing_left
		glm::vec3(-2.231, 0.272, -2.663),	//wing_right
		glm::vec3(0, 1.295, -3.616), 		//propeller
	};
	std::vector<glm::vec3> AquaPigRotation = {
		glm::vec3(0, 0, 0),	//hull
		glm::vec3(0, 0 ,0),	//gun_base
		glm::vec3(0, 0, 0),	//gun --- manually applied after gunbase
		glm::vec3(0, 0, 0),	//wing_left
		glm::vec3(0, 0, 0),	//wing_right
		glm::vec3(1.5708, 0, 0), //propeller //angle is Radian conversion
	};
	Model makeAquaPig(int iteration);
};

