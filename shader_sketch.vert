#version 150

in vec4 vertex;
uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vertex;
}
