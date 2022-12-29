#version 330
layout (location = 0) in vec3 boxPos;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform mat4 combinedSkyTransform;

out vec3 texCoords;

void main()
{
    texCoords = boxPos;
    gl_Position = combinedSkyTransform * model * vec4(boxPos, 1.0);
}
