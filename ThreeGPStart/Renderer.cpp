#include "Renderer.h"
#include "Camera.h"
#include "ImageLoader.h"
#include "Skybox.h"
#include "AquaPig.h"

Renderer::Renderer()
{

}

// On exit must clean up any OpenGL resources e.g. the program, the buffers
Renderer::~Renderer()
{
	// TODO: clean up any memory used including OpenGL objects via glDelete* calls
	glDeleteProgram(m_program);
	glDeleteProgram(m_programSkybox);
	//glDeleteBuffers(1, &m_VAO);
	/// ^ probably important to fix
}

// Use IMGUI for a simple on screen GUI
void Renderer::DefineGUI()
{
	// Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGui::Begin("3GP");						// Create a window called "3GP" and append into it.

	ImGui::Text("Visibility.");					// Display some text (you can use a format strings too)	

	ImGui::Checkbox("Wireframe", &m_wireframe);	// A checkbox linked to a member variable

	ImGui::Checkbox("Cull Face", &m_cullFace);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}

// Load, compile and link the shaders and create a program object to host them
bool Renderer::CreateProgram()
{
	if (m_program)
		glDeleteProgram(m_program);

	// Create a new program (returns a unqiue id)
	m_program = glCreateProgram();

	// Load and create vertex and fragment shaders
	GLuint vertex_shader{ Helpers::LoadAndCompileShader(GL_VERTEX_SHADER, "Data/Shaders/vertex_shader.vert") };
	GLuint fragment_shader{ Helpers::LoadAndCompileShader(GL_FRAGMENT_SHADER, "Data/Shaders/fragment_shader.frag") };
	if (vertex_shader == 0 || fragment_shader == 0)
		return false;

	// Attach the vertex shader to this program (copies it)
	glAttachShader(m_program, vertex_shader);

	// The attibute location 0 maps to the input stream "vertex_position" in the vertex shader
	// Not needed if you use (location=0) in the vertex shader itself
	//glBindAttribLocation(m_program, 0, "vertex_position");

	// Attach the fragment shader (copies it)
	glAttachShader(m_program, fragment_shader);

	// Done with the originals of these as we have made copies
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	// Link the shaders, checking for errors
	if (!Helpers::LinkProgramShaders(m_program))
		return false;

	return true;
}

bool Renderer::CreateProgramSkybox()
{
	if (m_programSkybox)
		glDeleteProgram(m_programSkybox);

	// Create a new program (returns a unqiue id)
	m_programSkybox = glCreateProgram();

	// Load and create vertex and fragment shaders
	GLuint vertex_shader_skybox{ Helpers::LoadAndCompileShader(GL_VERTEX_SHADER, "Data/Shaders/vertex_shader_skybox.vert") };
	GLuint fragment_shader_skybox{ Helpers::LoadAndCompileShader(GL_FRAGMENT_SHADER, "Data/Shaders/fragment_shader_skybox.frag") };
	if (vertex_shader_skybox == 0 || fragment_shader_skybox == 0)
		return false;

	// Attach the vertex shader to this program (copies it)
	glAttachShader(m_programSkybox, vertex_shader_skybox);

	// The attibute location 0 maps to the input stream "vertex_position" in the vertex shader
	// Not needed if you use (location=0) in the vertex shader itself
	//glBindAttribLocation(m_programSkybox, 0, "vertex_position");

	// Attach the fragment shader (copies it)
	glAttachShader(m_programSkybox, fragment_shader_skybox);

	// Done with the originals of these as we have made copies
	glDeleteShader(vertex_shader_skybox);
	glDeleteShader(fragment_shader_skybox);

	// Link the shaders, checking for errors
	if (!Helpers::LinkProgramShaders(m_programSkybox))
		return false;

	return true;
}

///https://learnopengl.com/Advanced-OpenGL/Cubemaps
// Load / create geometry into OpenGL buffers	
bool Renderer::InitialiseGeometry()
{
	if (!CreateProgramSkybox())
		return false;
	Skybox skybox;
	skyBoxModel = skybox.MakeSkybox();

	// Load and compile shaders into m_program
	if (!CreateProgram())
		return false;
	Helpers::ModelLoader loaderJeep;
	if (!loaderJeep.LoadFromFile("Data\\Models\\Jeep\\jeep.obj"))
		return false;
	// Now we can loop through all the mesh in the loaded model:
	/*
	for (const Helpers::Mesh& mesh : loaderJeep.GetMeshVector())
	{
		// We can extract from the mesh via:
		//mesh.vertices  - a vector of glm::vec3 (3 floats) giving the position of each vertex
		//mesh.elements - a vector of unsigned ints defining which vertices make up each triangle


		// create VBO for the vertices and a EBO for the elements
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

		// create a VBA to wrap everything and specify locations in the shaders

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
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

		m_numElements = mesh.elements.size();

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
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
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemEBO);

		glBindVertexArray(0);
	}
	*/

	AquaPig aquaPig;
	for (int i = 0; i < aquaPig.AquaPigObjects.size(); i++)
		modelVector.push_back(aquaPig.makeAquaPig(i));

	return true;
}

// Render the scene. Passed the delta time since last called.
void Renderer::Render(const Helpers::Camera& camera, float deltaTime)
{
	// Configure pipeline settings
	glEnable(GL_DEPTH_TEST);

	if (m_cullFace)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// Wireframe mode controlled by ImGui
	if (m_wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Clear buffers from previous frame
	glClearColor(0.0f, 0.0f, 0.0f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Compute viewport and projection matrix
	GLint viewportSize[4];
	glGetIntegerv(GL_VIEWPORT, viewportSize);
	const float aspect_ratio = viewportSize[2] / (float)viewportSize[3];
	glm::mat4 projection_xform = glm::perspective(glm::radians(45.0f), aspect_ratio, 1.0f, 2000.0f);

	// Compute camera view matrix and combine with projection matrix for passing to shader
	glm::mat4 view_xform = glm::lookAt(camera.GetPosition(), camera.GetPosition() + camera.GetLookVector(), camera.GetUpVector());
	glm::mat4 combined_xform = projection_xform * view_xform;


	//This is the skybox section of the render function

	glDepthMask(GL_FALSE);
	glUseProgram(m_programSkybox);

	glm::mat4 skyboxView = glm::mat4(glm::mat3(view_xform));// Translate the skybox to the camera position
	glm::mat4 combinedSkyTransform = projection_xform * skyboxView;
	glUniformMatrix4fv(glGetUniformLocation(m_programSkybox, "combinedSkyTransform"), 1, GL_FALSE, glm::value_ptr(combinedSkyTransform));

	glm::mat4 skyBoxTransform = glm::mat4(1); //c
	glUniformMatrix4fv(glGetUniformLocation(m_programSkybox, "boxPos"), 1, GL_FALSE, glm::value_ptr(skyBoxTransform));



	glBindVertexArray(skyBoxModel.m_VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxModel.m_tex);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glDepthMask(GL_TRUE);


	// this is the model loading section of the render function

	glUseProgram(m_program);

	// Send the combined matrix to the shader in a uniform
	GLuint combined_xform_id = glGetUniformLocation(m_program, "combined_xform");
	glUniformMatrix4fv(combined_xform_id, 1, GL_FALSE, glm::value_ptr(combined_xform));

	//Render the AquaPig
	for (int i = 0; i < modelVector.size(); i++)
	{
		glm::mat4 model_xform = glm::mat4(1);
		model_xform = glm::translate(model_xform, modelVector[i].m_translation);
		model_xform = glm::rotate(model_xform, modelVector[i].m_rotation.x, { 1 , 0 , 0 });
		static float angle = 0; angle += 0.0001f;
		if (i == 5)
		{
			model_xform = glm::rotate(model_xform, angle, { 0 , 1 , 0 });
		}

		GLuint model_xform_id = glGetUniformLocation(m_program, "model_xform");
		glUniformMatrix4fv(model_xform_id, 1, GL_FALSE, glm::value_ptr(model_xform));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, modelVector[i].m_tex);
		glUniform1i(glGetUniformLocation(m_program, "model_tex"), 0);

		glBindVertexArray(modelVector[i].m_VAO);
		glDrawElements(GL_TRIANGLES, modelVector[i].m_numElements, GL_UNSIGNED_INT, (void*)0);
	}


}

