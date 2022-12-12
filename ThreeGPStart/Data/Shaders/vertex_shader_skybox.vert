#version 330
uniform mat4 projection;
uniform mat4 view;
uniform mat4 combinedProjView;


layout (location = 0) in vec3 boxPos;

out vec3 TexCoords;

void main()
{
    TexCoords = boxPos;
    gl_Position = combinedProjView * vec4(boxPos, 1.0);
    //gl_Position = projection * view * vec4(boxPos, 1.0);
}  