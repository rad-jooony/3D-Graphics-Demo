#version 330
layout (location = 0) in vec3 boxPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = boxPos;
    gl_Position = projection * view * vec4(boxPos, 1.0);
}  