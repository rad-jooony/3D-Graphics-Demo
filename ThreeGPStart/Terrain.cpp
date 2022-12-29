#include "Terrain.h"

Model Terrain::makeTerrain(int X, int Z)
{
	for (int i = 0; i < Z; i++)
	{
		for (int j = 0; j < X; j++)
		{
			verts.push_back(glm::vec3(i * 10, 0, j * 10));
			colours.push_back({ 0,1,0 });
			{
				float texX = 0;
				float texY = 0;
				if (i != 0)
				{
					texX = i / (X - 1.f);
					//int a;
				}
				if (j != 0)
				{
					texY = j / (Z - 1.f);
					//int a;
				}
				texCoords.push_back(glm::vec2(texX, texY));
			}
		}
	}

	bool diamondPatt = true;

	for (int cellZ = 0; cellZ < (Z - 1); cellZ++)
	{
		for (int cellX = 0; cellX < (X - 1); cellX++)
		{
			int startVert = (cellZ * X) + cellX;
			if (diamondPatt)
			{
				elements.push_back(startVert);
				elements.push_back(startVert + 1);
				elements.push_back(startVert + X);

				elements.push_back(startVert + 1);
				elements.push_back(startVert + X + 1);
				elements.push_back(startVert + X);

				diamondPatt = false;
			}
			else
			{
				elements.push_back(startVert);
				elements.push_back(startVert + 1);
				elements.push_back(startVert + 1 + X);

				elements.push_back(startVert);
				elements.push_back(startVert + X + 1);
				elements.push_back(startVert + X);
				diamondPatt = true;
			}
		}
	}

	vertsMovedUp = verts;

	for (int i = 0; i < vertsMovedUp.size(); i++)
	{
		vertsMovedUp[i].y = vertsMovedUp[i].y + 10;
	}

	Model terrain;

	//Helpers::ImageLoader terrainmap;
	//if (terrainmap.Load("Data\\Textures\\dirt.dds"))
	//{
	//	float vertXtoImage = (float)terrainmap.Width() / X;
	//	float vertZtoImage = (float)terrainmap.Width() / Z;
	//	BYTE* data = terrainmap.GetData();
	//	for (int i = 0; i < Z; i++)
	//	{
	//		for (int j = 0; j < X; j++)
	//		{
	//			int index = ((i * X) + j);
	//			int imageX = vertXtoImage * X;
	//			int imageZ = vertZtoImage * Z;

	//			size_t offset = (((size_t)imageX + (size_t)imageZ) * terrainmap.Width()) * 4; //the colour in colour channel (red)

	//			BYTE heightData = data[offset];

	//			float heightVal = (float)heightData;
	//			verts[index].y = heightVal;
	//		}
	//	}
	//}



	//SetVar below to add noise
	//step 1 - make rand number
	//step 2 - use number to move Y

	bool amplify = false; //make noise prominant

	if (noiseOn)
	{
		int index = 0;
		for (int i = 0; i < Z; i++)
		{
			for (int j = 0; j < X; j++)
			{
				float noise = rand() % 1000;
				noise /= 500;
				glm::vec3 myVec = verts[index];

				myVec.y = myVec.y + noise;

				verts[index].y =+ myVec.y;
				index++;
			}
		}
	}




	terrain.m_numElements = (GLuint)elements.size();

	GLuint verticesVBO;
	glGenBuffers(1, &verticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * verts.size(), verts.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint elemEBO;
	glGenBuffers(1, &elemEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * elements.size(), elements.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLuint coloursVBO;
	glGenBuffers(1, &coloursVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, coloursVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::vec3) * colours.size(), colours.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	GLuint texCoordsVBO;
	glGenBuffers(1, &texCoordsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * texCoords.size(), texCoords.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	terrain.m_numElements = elements.size();

	glGenVertexArrays(1, &terrain.m_VAO);
	glBindVertexArray(terrain.m_VAO);
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

	glBindBuffer(GL_ARRAY_BUFFER, coloursVBO);
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

	//{
	//	GLuint vertices2VBO;
	//	glGenBuffers(1, &vertices2VBO);
	//	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertsMovedUp.size(), vertsMovedUp.data(), GL_STATIC_DRAW);
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//	GLuint elem2EBO;
	//	glGenBuffers(1, &elem2EBO);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemEBO);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * elements.size(), elements.data(), GL_STATIC_DRAW);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//	GLuint colours2VBO;
	//	glGenBuffers(1, &colours2VBO);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, colours2VBO);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::vec3) * colours.size(), colours.data(), GL_STATIC_DRAW);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//	GLuint texCoords2VBO;
	//	glGenBuffers(1, &texCoords2VBO);
	//	glBindBuffer(GL_ARRAY_BUFFER, texCoords2VBO);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * texCoords.size(), texCoords.data(), GL_STATIC_DRAW);
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//	terrain.m_numElements = elements.size();

	//	glGenVertexArrays(1, &terrain.m_VAO2);
	//	glBindVertexArray(terrain.m_VAO2);
	//	glBindBuffer(GL_ARRAY_BUFFER, vertices2VBO);
	//	glEnableVertexAttribArray(0);
	//	glVertexAttribPointer(
	//		0, //attribute
	//		3, //num of componants
	//		GL_FLOAT, //type
	//		GL_FALSE, // ignore this
	//		0, // stride
	//		(void*)0 // array buffer offset
	//	);

	//	glBindBuffer(GL_ARRAY_BUFFER, texCoords2VBO);
	//	glEnableVertexAttribArray(1);
	//	glVertexAttribPointer(
	//		1, //attribute
	//		2, //num of componants
	//		GL_FLOAT, //type
	//		GL_FALSE, // ignore this
	//		0, // stride
	//		(void*)0 // array buffer offset


	//	);
	//	glBindBuffer(GL_ARRAY_BUFFER, colours2VBO);
	//	glEnableVertexAttribArray(2);
	//	glVertexAttribPointer(
	//		2, //attribute
	//		3, //num of componants
	//		GL_FLOAT, //type
	//		GL_FALSE, // ignore this
	//		0, // stride
	//		(void*)0 // array buffer offset
	//	);

	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elem2EBO);

	//	glBindVertexArray(0);
	//}

	Helpers::ImageLoader image;
	if (image.Load("Data\\Textures\\dirt.dds"))
	{
		glGenTextures(1, &terrain.m_tex);
		glBindTexture(GL_TEXTURE_2D, terrain.m_tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.Width(), image.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	return terrain;
}
