#include "AquaPig.h"

Model AquaPig::makeAquaPig(int iteration)
{
	Helpers::ModelLoader loaderPig;
	if (!loaderPig.LoadFromFile(AquaPigObjects[iteration]))
	{
		std::cout << AquaPigObjects[iteration] << " did not load" << std::endl;
	}

	for (const Helpers::Mesh& mesh : loaderPig.GetMeshVector())
	{
		Model newModel;

		newModel.m_translation = AquaPigTranslation[iteration];
		newModel.m_rotation = AquaPigRotation[iteration];

		GLuint verticesVBO;
		glGenBuffers(1, &verticesVBO);
		glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint normalsVBO;
		glGenBuffers(1, &normalsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh.normals.size(), mesh.normals.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint elemEBO;
		glGenBuffers(1, &elemEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh.elements.size(), mesh.elements.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


		GLuint texCoordsVBO;
		glGenBuffers(1, &texCoordsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * mesh.uvCoords.size(), mesh.uvCoords.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		newModel.m_numElements = mesh.elements.size();

		glGenVertexArrays(1, &newModel.m_VAO);
		glBindVertexArray(newModel.m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0, //attribute
			3, //num of componants
			GL_FLOAT, //type
			GL_FALSE, // ignore this
			0, // stride
			(void*)0 // array buffer offset
		);

		glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1, //attribute
			3, //num of componants
			GL_FLOAT, //type
			GL_FALSE, // ignore this
			0, // stride
			(void*)0 // array buffer offset
		);

		glBindBuffer(GL_ARRAY_BUFFER, texCoordsVBO);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2, //attribute
			2, //num of componants
			GL_FLOAT, //type
			GL_FALSE, // ignore this
			0, // stride
			(void*)0 // array buffer offset
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemEBO);

		glBindVertexArray(0);

		Helpers::ImageLoader AquaPig1K;

		if (AquaPig1K.Load("Data\\Models\\AquaPig\\aqua_pig_1K.png"))
		{
			glGenTextures(1, &newModel.m_tex);
			glBindTexture(GL_TEXTURE_2D, newModel.m_tex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, AquaPig1K.Width(), AquaPig1K.Height(), 0,
				GL_RGBA, GL_UNSIGNED_BYTE, AquaPig1K.GetData());
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		return newModel;
	}
};


