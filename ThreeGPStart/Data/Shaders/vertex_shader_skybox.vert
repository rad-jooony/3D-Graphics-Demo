#version 330
layout (location = 0) in vec3 boxPos;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 combinedSkyTransform;


out vec3 texCoords;

void main()
{
    texCoords = boxPos;
    gl_Position = combinedSkyTransform * vec4(boxPos, 1.0);
    //gl_Position = projection * view * vec4(boxPos, 1.0);
}  