#version 330

/*
	The vertex shader runs once for every vertex in the primitive
	Its main job is to convert the vertex position to a screen position by writing to gl_Position

	Note: I set the extension to .vert to avoid a clash with NSight but still allow the highlighting
	plugin to work (GLSL Langauage integration - highly recommended).
*/

uniform mat4 combined_xform;
uniform mat4 model_xform;


layout (location=0) in vec3 vertex_position;
layout (location=1) in vec3 vertex_normal;
layout (location=2) in vec2 vertex_texcoord;

out vec3 varying_normal;
out vec2 varying_texcoord;

void main(void)
{	
	
	varying_normal = vertex_normal;
	varying_texcoord = vertex_texcoord;
	gl_Position = combined_xform * model_xform * vec4(vertex_position, 1.0);
}