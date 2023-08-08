#version 450 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform vec2 u_resolution;

void main()
{
    TexCoord = aTexCoord;
    gl_Position = vec4(aPos / u_resolution * 30, 0, 1.0);
}
