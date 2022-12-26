#include "Skybox.h"

Model Skybox::MakeSkybox()
{
	glGenTextures(1, &skyBox.m_tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyBox.m_tex);

	GLuint positionsVBO;
	glGenBuffers(1, &positionsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * skyboxVertices.size(), skyboxVertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint elemEBO;
	glGenBuffers(1, &elemEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * skyboxElements.size(), skyboxElements.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	skyBox.m_numElements = skyboxElements.size();

	glGenVertexArrays(1, &skyBox.m_VAO);
	glBindVertexArray(skyBox.m_VAO);
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemEBO);

	glBindVertexArray(0);

	Helpers::ImageLoader sky;

	for (int i = 0; i < skyboxFacesPaths.size(); i++)
	{
		if (!sky.Load(skyboxFacesPaths[i]))
		{
		MessageBox(NULL, L"Can't Load Skybox", L"ERROR",
			MB_OK | MB_ICONEXCLAMATION);
		}
		else
		{
			glTexImage2D
			(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGBA,
				sky.Width(),
				sky.Height(),
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				sky.GetData());
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glGenerateMipmap(GL_TEXTURE_2D);

	return skyBox;
}